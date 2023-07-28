#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Delivery.h"

void displayHeader() {
    printf("=================\n");
    printf("Seneca Deliveries\n");
    printf("=================\n");
}

void displayDeliveryMenu() {
    struct Map map = populateMap();
    struct Route blueRoute = getBlueRoute();
    map = addRoute(&map, &blueRoute);
    struct Route yellowRoute = getYellowRoute();
    map = addRoute(&map, &yellowRoute);
    struct Route greenRoute = getGreenRoute();
    map = addRoute(&map, &greenRoute);

    printMap(&map, 1, 1);
    printf("\n");


    // Assuming there is an array of trucks defined as "struct Truck truckArr[NUM_TRUCKS];"

    struct Shipment shipment;
    struct Truck truckArr[3] = { {"BLUE", 1000.0, 36.0, 0, 0, blueRoute}, {"YELLOW", 1000.0, 36.0, 0, 0, yellowRoute}, {"GREEN", 1000.0, 36.0, 0, 0, greenRoute} };
    int TruckIndex;
    int flag = 0;

    while (!flag) {
        displayHeader();
        shipment = getUserInput();

        if (shipment.weight == 0 && shipment.volume == 0) {
            flag = 1;
        }
        else {
            TruckIndex = selectTruck(&map, truckArr, 3, shipment);
            if (TruckIndex == -1) {
                printf("No truck is able to take the shipment.\n");
            }
            else {
                printf("Ship on %s LINE, ", truckArr[TruckIndex].routeColor);
                if (truckArr[TruckIndex].divertRoute == 0) {
                    printf("came inside");
                    struct DivertedRoute divertedRoute = getDivertedRoute(&map, truckArr[TruckIndex], shipment.destination);
                    printf("came outie");
                    printf("divert: ");
                    int i = 0;
                    int totalDivPoints = sizeof(divertedRoute.divRoute) / sizeof(divertedRoute.divRoute[0]);
                    for (i; i < totalDivPoints; i++) {
                        printf("%d%c ", divertedRoute.divRoute[i].row, divertedRoute.divRoute[i].col);
                        if (i < totalDivPoints - 1) {
                            printf(', ');
                        }
                    }
                    /*while (!isPointEqual(divertedRoute.divRoute[i], map.INVALID)) {
                        printf("%c%d", divertedRoute.divRoute[i].col + 'A', divertedRoute.divRoute[i].row);
                        if (!isPointEqual(divertedRoute.divRoute[i + 1], map.INVALID))
                            printf(", ");
                        i++;
                    }*/
                }
                else {
                    printf("no diversion");
                }
                printf("\n");
            }
        }
    }

    printf("Thanks for shipping with Seneca!\n");
}

int checkWeight(double weight) {
    int check = 0;
    if (weight > 0 && weight <= MAX_WEIGHT) {
        check = 1;
    }
    return check;
}

int checkBox(double boxSize) {

    // The Box sizes available for shipping
    const double boxVolume[3] = { 1.0, 0.5, 0.25 };
    int check = 0, i;
    for (i = 0; i < 3; i++) {
        if (boxSize == boxVolume[i]) {
            check = 1;
        }
    }
    return check;
}

int checkDestination(int row, char col) {
    int check = 0;
    struct Map buildingMap = populateMap();
    if (buildingMap.squares[row - 1][(int)col - 65] == 1) {
        check = 1;
    }
    return check;
}

int selectTruck(struct Map* map, struct Truck truckArr[], int numOfTrucks, struct Shipment shipment) {

    struct DivertedRoute dr;
    int onRouteTrucks[3] = { 0 }, proximityApprovedTrucks[3] = { 0 };

   /* for (int i = 0; i < 3; i++) {
        printf("%d\n", onRouteTrucks[i]);
    }*/

    // gets lenth of array : proximityApprovedTrucks
    int lengthProximityTrucks;

    int truckIndex = -1, minDivDist = 100, onRouteCounter = 0, proximityApprovedCounter = 0;

    for (int i = 0; i < numOfTrucks; i++) {
        //check for if the remaining weight/volume fits
        if (shipment.weight <= truckArr[i].weightRemaining && shipment.volume <= truckArr[i].volumeRemaining) {
            // good to go
            truckArr[i].limitingFactor = 1;
        }
        else {
            // problem with weight/volume
            truckArr[i].limitingFactor = 0;
        }
    }

    for (int i = 0; i < numOfTrucks && !truckArr[i].divertRoute; i++) {
        for (int j = 0; j < MAX_ROUTE; j++) {
            if (distance(&truckArr[i].truckRoute.points[j], &shipment.destination) == 66) {
                //no diverted path is needed
                if (truckArr[i].limitingFactor) {
                    onRouteTrucks[onRouteCounter] = i + 1;
                    onRouteCounter++;
                    truckArr[i].divertRoute = 1;
                }
            }
            else {
                // divert route = 0 means it is needed
                truckArr[i].divertRoute = 0;
            }
        }
        //diverted path is needed
        if (!truckArr[i].divertRoute && truckArr[i].limitingFactor) {
            proximityApprovedTrucks[proximityApprovedCounter] = i + 1;
            proximityApprovedCounter++;
        }
    }

    if (onRouteTrucks[0] != 0) {
        truckIndex = onRouteTrucks[0] - 1;
    }
    else if (proximityApprovedTrucks[0] != 0) {
        lengthProximityTrucks = getArrLength(proximityApprovedTrucks);
        for (int i = 0; i < lengthProximityTrucks; i++) {
            dr = getDivertedRoute(map, truckArr[proximityApprovedTrucks[i] - 1], shipment.destination);
            if (dr.divNumPoints < minDivDist) {
                minDivDist = dr.divNumPoints;
                truckIndex = proximityApprovedTrucks[i] - 1;
                truckArr[proximityApprovedTrucks[i] - 1].divertRoute = 0;
            }
        }
    }

    if (truckIndex != -1) {
        truckArr[truckIndex].weightRemaining = truckArr[truckIndex].weightRemaining - shipment.weight;
        truckArr[truckIndex].volumeRemaining = truckArr[truckIndex].volumeRemaining - shipment.volume;
    }

    //if no truck then value is -1 by default
    return truckIndex;
}

struct Shipment getUserInput() {
    struct Shipment shipment;
    double weight, boxSize;
    char destinationInput[4];
    int row; 
    char col;
    int validInput = 0;

    while (!validInput) {
        printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
        scanf("%lf %lf %s", &weight, &boxSize, &destinationInput);
        if (weight == 0 && boxSize == 0 && destinationInput[0] == 'x') {
            shipment.weight = 0;
            shipment.volume = 0;
            validInput = 1;
        }
        else {
            row = atoi(destinationInput);
            col = destinationInput[strlen(destinationInput) - 1];
            if (checkWeight(weight) && checkBox(boxSize) && checkDestination(row, col)) {
                shipment.weight = weight;
                shipment.volume = boxSize;
                shipment.destination.row = row;
                shipment.destination.col = col;
                validInput = 1;
            }
            else {
                if (!checkWeight(weight)) {
                    printf("Invalid weight (must be 1-1000 Kg.)\n");
                }
                if (!checkBox(boxSize)) {
                    printf("Invalid size\n");
                }
                if (!checkDestination(row, col)) {
                    printf("Invalid destination\n");
                }
            }
        }
    }

    return shipment;
}


struct DivertedRoute getDivertedRoute(struct Map* map, struct Truck truck,const struct Point destination) {
    struct DivertedRoute divertedRoute;
    struct Point diversionPoint;
    double dist, mindist = 100.0;
    int index = -1;
    int i = 0, routeComplete = 0;
    struct Route r;
    for ( i = 0; i < MAX_ROUTE && !routeComplete; i++) {
        dist = distance(&truck.truckRoute.points[i], &destination);
        if (dist < mindist) {
            mindist = dist;
            index = i;
        }
        if (i == truck.truckRoute.numPoints) {
            routeComplete = 1;
        }
    }
    
    r = shortestPath(map, truck.truckRoute.points[index], destination);
    for (int i = 0; i < MAX_ROUTE; i++) {
        divertedRoute.divRoute[i] = r.points[i];
    }


    return divertedRoute;
}

int getArrLength(int arr[]) {
    int length = sizeof(arr) / sizeof(arr[0]);
    int count = 0;

    for (int i = 0; i < length; i++) {
        if (arr[i] != 0) {
            count++;
        }
    }
    return count;
}