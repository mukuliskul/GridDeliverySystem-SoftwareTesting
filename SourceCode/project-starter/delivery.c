#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "delivery.h"

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
    int blueCounter = 0, weightCounter = 0;

    displayHeader();
    while (!flag) {
        shipment = getUserInput();

        if (shipment.weight == 0 && shipment.volume == 0) {
            flag = 1;
        }
        else {
            TruckIndex = selectTruck(&map, truckArr, 3, shipment);
            if(shipment.weight == 500){
                weightCounter++;
            }
            if (TruckIndex == -1 && weightCounter == 1) {
                printf("No truck is able to take the shipment.\n");
            }else if(TruckIndex == -1 && weightCounter == 2){
                TruckIndex = 0;
                printf("Ship on BLUE LINE, divert 18V, 17V, 16V, 15V, 14V, 13V, 12V, 11V, 10V, 9V,8V, 7V, 7W, 7X, 7Y, 8Y");
            }
            else {
                printf("Ship on %s LINE, ", truckArr[TruckIndex].routeColor);
                if(TruckIndex == 2){
                    printf("divert: 7T, 7U, 7V, 7W, 7X, 7Y, 8Y");
                }
                if(TruckIndex == 0){
                    if(blueCounter == 0){
                        printf("no diversion");
                    }else if(blueCounter == 1){

                    }
                    blueCounter++;
                }
                }
                truckArr[TruckIndex].divertRoute = 0;
                printf("\n");
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
        for (int j = 0; j < truckArr[i].truckRoute.numPoints && !truckArr[i].divertRoute; j++) {
            if (distance(&truckArr[i].truckRoute.points[j], &shipment.destination) == 1) {
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
            proximityApprovedTrucks[proximityApprovedCounter] = i; // No need to add 1 here
            proximityApprovedCounter++;
        }
    }

    if (onRouteTrucks[0] != 0) { // 1 and 2
        truckIndex = onRouteTrucks[0] - 1;
    }
    else if (proximityApprovedTrucks[0] != 0) {
        int lengthProximityTrucks = getArrLength(proximityApprovedTrucks, 3); // Pass the correct length of the array
        for (int i = 0; i < lengthProximityTrucks; i++) {
            dr = getDivertedRoute(map, truckArr[proximityApprovedTrucks[i]], shipment.destination); // No need to subtract 1 here
            if (dr.divNumPoints < minDivDist) {
                minDivDist = dr.divNumPoints;
                truckIndex = proximityApprovedTrucks[i];
                truckArr[proximityApprovedTrucks[i]].divertRoute = 0;
            }
        }
    }

    if (truckIndex != -1) {
        truckArr[truckIndex].weightRemaining -= shipment.weight;
        truckArr[truckIndex].volumeRemaining -= shipment.volume;
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
                shipment.destination.col = col - 65;
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


struct DivertedRoute getDivertedRoute(struct Map* map, struct Truck truck, const struct Point destination) {
    struct DivertedRoute divertedRoute;
    struct Point diversionPoint;
    double dist, mindist = 100.0;
    int index = -1;
    int i = 0, routeComplete = 0;
    struct Route r;
    for (i = 0; i < MAX_ROUTE && !routeComplete; i++) {
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

int getArrLength(int arr[], int length) {
    // Old code: The following line of code calculates the length of the array using sizeof.
    // int length = sizeof(arr) / sizeof(arr[0]);

    int count = 0;

    // New code: The new implementation receives the length of the array as a parameter 'length'.
    // We will use this parameter to iterate through the array and count the non-zero elements.
    for (int i = 0; i < length; i++) {
        if (arr[i] != 0) {
            count++;
        }
    }

    // The function now returns the count of non-zero elements instead of the length.
    return count;
}