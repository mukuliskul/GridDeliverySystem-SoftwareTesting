/*
SFT211- Group Project
Section NEE
Group 3
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "delivery.h"

int main(void)
{
    // Initialize the map and routes
    struct Map baseMap = populateMap();
    struct Route blueRoute = getBlueRoute();

    // Add the blue route to the map
    struct Map routeMap = addRoute(&baseMap, &blueRoute);

    // Print the updated map with the blue route
    int mapRows = 20; // Set the correct number of rows
    int mapCols = 20; // Set the correct number of columns
    printMap(&routeMap, mapRows, mapCols);

    // Delivery.h functions test
    double shipmentWeight = 500.0;
    double shipmentVolume = 0.5; // 0.5m^3
    struct Point destination = { 5, 'F' }; // A valid point on the map
    struct Shipment shipment = { shipmentWeight, shipmentVolume, destination, 0 };

    // Test checkWeight function
    if (checkWeight(shipmentWeight)) {
        printf("Weight is valid.\n");
    }
    else {
        printf("Invalid weight (must be 1-1000 Kg.)\n");
    }

    // Test checkBox function
    if (checkBox(shipmentVolume)) {
        printf("Box size is valid.\n");
    }
    else {
        printf("Invalid box size.\n");
    }

    // Test checkDestination function
    if (checkDestination(destination.row, destination.col)) {
        printf("Destination is valid.\n");
    }
    else {
        printf("Invalid destination.\n");
    }

    // Test getDivertedRoute function
   /* struct Truck truck = { "Blue", 500.0, 30.0, 0, 0, blueRoute };
    struct DivertedRoute divertedRoute = getDivertedRoute(&routeMap, truck, destination);
    printf("Diverted route points:\n");
    if (divertedRoute.divNumPoints == 0) {
        printf("No diverted route needed. Destination already on the truck's route.\n");
    }
    else {
        for (int i = 0; i < divertedRoute.divNumPoints; i++) {
            printf("(%d, %c)\n", divertedRoute.divRoute[i].row, divertedRoute.divRoute[i].col);
        }
    }*/

    // Test selectTruck function
    struct Truck truckArr[] = {
        { "Blue", 500.0, 30.0, 0, 0, blueRoute },
        { "Green", 800.0, 40.0, 0, 0, getGreenRoute() },
        { "Yellow", 700.0, 35.0, 0, 0, getYellowRoute() }
    };
    int numOfTrucks = sizeof(truckArr) / sizeof(truckArr[0]);
    int selectedTruckIndex = selectTruck(&routeMap, truckArr, numOfTrucks, shipment);
    if (selectedTruckIndex != -1) {
        printf("Selected truck for shipment: %s\n", truckArr[selectedTruckIndex].routeColor);
        printf("Remaining weight on the truck: %.2lf Kg\n", truckArr[selectedTruckIndex].weightRemaining);
        printf("Remaining volume on the truck: %.2lf m^3\n", truckArr[selectedTruckIndex].volumeRemaining);
    }
    else {
        printf("No available truck for the shipment.\n");
    }

    return 0;
}
