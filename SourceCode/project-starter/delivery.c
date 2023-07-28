#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
    struct Truck truckArr[3] = { {"BLUE", 1000.0, 36.0, 0, blueRoute}, {"YELLOW", 1000.0, 36.0, 0, yellowRoute}, {"GREEN", 1000.0, 36.0, 0, greenRoute} };
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
                printf("Ship on %s, ", truckArr[TruckIndex].routeColor);
                if (truckArr[TruckIndex].limitingFactor > 0) {
                    struct DivertedRoute divertedRoute = getDivertedRoute(&map, truckArr[TruckIndex], shipment.destination);
                    printf("divert ");
                    int i = 0;
                    while (!isPointEqual(divertedRoute.divRoute[i], map.INVALID)) {
                        printf("%c%d", divertedRoute.divRoute[i].col + 'A', divertedRoute.divRoute[i].row);
                        if (!isPointEqual(divertedRoute.divRoute[i + 1], map.INVALID))
                            printf(", ");
                        i++;
                    }
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
    char onRouteTrucks[3], proximityApprovedTrucks[3];
  
    // gets lenth of array : proximityApprovedTrucks
    int lengthProximityTrucks;
  
    int truckIndex = -1, minDivDist = 100, onRouteCounter = 0, proximityApprovedCounter = 0;

    for(int i = 0; i < numOfTrucks; i++){
      //check for if the remaining weight/volume fits
      if(shipment.weight <= truckArr[i].weightRemaining && shipment.volume <= truckArr[i].volumeRemaining){
        // good to go
        truckArr[i].limitingFactor = 1;
      }else{
        // problem with weight/volume
        truckArr[i].limitingFactor = 0;
      }
    }

    for (int i = 0; i < numOfTrucks; i++) {
        for (int j = 0; j < MAX_ROUTE; j++) {
            if (distance(&truckArr[i].truckRoute.points[j], &shipment.destination) == 1) {
              //no diverted path is needed
              if(truckArr[i].limitingFactor){
                onRouteTrucks[onRouteCounter] = i + 1;
                onRouteCounter++;  
              }
            }
            else {
              //diverted path is needed
              if(truckArr[i].limitingFactor){
                proximityApprovedTrucks[proximityApprovedCounter] = i + 1;
                proximityApprovedCounter++;  
              }
            }
        }
    }

    if(onRouteTrucks[0] != 0){
      truckIndex = onRouteTrucks[0] - 1;
    }else if(proximityApprovedTrucks[0] != 0){
      lengthProximityTrucks = sizeof(proximityApprovedTrucks) / sizeof(proximityApprovedTrucks[0]);
      for(int i; i < lengthProximityTrucks; i++){
        dr = getDivertedRoute(map, truckArr[proximityApprovedTrucks[i] - 1], shipment.destination);
        if(dr.divNumPoints < minDivDist){
          minDivDist = dr.divNumPoints;
          truckIndex = proximityApprovedTrucks[i] - 1;
        }
      }
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
    }
    
    r = shortestPath(map, truck.truckRoute.points[index], destination);
    for (int i = 0; i < MAX_ROUTE; i++) {
        divertedRoute.divRoute[i] = r.points[i];
    }
    divertedRoute.divNumPoints = r.numPoints;

    return divertedRoute;
         
    
    //// Implementation to get the shortest possible diverted route.
    //struct DivertedRoute divertedRoute;

    //// Assuming the starting point of the truck is its current location.
    //struct Point currentLocation = truck.truckRoute.points[0];

    //// Calculate the diverted route from the current location to the shipment destination.
    //struct Point destination = destination;
    //divertedRoute.divRoute[0] = currentLocation;
    //int dx = (destination.col > currentLocation.col) ? 1 : ((destination.col < currentLocation.col) ? -1 : 0);
    //int dy = (destination.row > currentLocation.row) ? 1 : ((destination.row < currentLocation.row) ? -1 : 0);

    //int i = 1;
    //while (currentLocation.row != destination.row || currentLocation.col != destination.col) {
    //    currentLocation.row += dy;
    //    currentLocation.col += dx;
    //    divertedRoute.divRoute[i++] = currentLocation;
    //}

    //divertedRoute.divRoute[i] = map->INVALID; // Mark the end of the route with the invalid point.
    //return divertedRoute;
}