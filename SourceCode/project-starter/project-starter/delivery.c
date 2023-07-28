#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Delivery.h"


/**
* Checks if the weight input is valid or not
* @param recieves a weight value
* @returns 1 if the value is valid and 0 if it is not
*/
int checkWeight(double weight) {
    int check = 0;
    if (weight > 0 && weight <= MAX_WEIGHT) {
        check = 1;
    }
    return check;
}


/**
* Checks if the box volume input is valid or not
* @param recieves a volume value
* @returns 1 if the value is valid and 0 if it is not
*/
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

/**
* Checks if the destination input is valid or not
* @param recieves the int row and char column for the destination value
* @returns 1 if the value is valid and 0 if it is not
*/
int checkDestination(int row, char col) {
    int check = 0;
    struct Map buildingMap = populateMap();
    if (buildingMap.squares[row - 1][(int)col - 65] == 1) {
        check = 1;
    }
    return check;
}

/**
* Gets input about the shipment details validates the input and displays error prompts for incorrect input
* stores the correct input in a shipment data structure and returns the data structure
* @returns the shipment structure with details about the shipment
*/
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

