/*
SFT211- Group Project
Section NEE
Group 3
*/
#pragma once
#ifndef DELIVERY_H
#define DELIVERY_H

#include"mapping.h"

#define MAX_WEIGHT 1000
#define MAX_VOLUME 36

/*
* This holds the details that the customer specifies about the shipment
* and also keep track of the shipment status.(whether it was shipped or not)
*/
struct Shipment {
	double weight;
	double volume;
	struct Point destination;
	int shipStatus;
};

/*
* This holds the route that the truck follows, checks the weight and volume remaining from the max
* weight and volume. And also stores teh limiting factor the truck is to be compared on if it is compared.
*/
struct Truck {
	char routeColor[10];
	double weightRemaining;
	double volumeRemaining;
	int limitingFactor;
	int divertRoute;
	struct Route truckRoute;
};
/*
* A collection of points that constitute the diverted path from the route of the 
* truck to the destination
*/
struct DivertedRoute {
	struct Point divRoute[MAX_ROUTE];
  int divNumPoints;
};


/*
* Displays the header of the delivery menu 
* recieves no parameters 
* returns nothing
*/
void displayHeader();

/**
* Displays the complete delivery menu and calls required function to get, validate and implement user input
* recieves no parameters
* returns nothing
*/
void displayDeliveryMenu();


/**
* Checks if the weight input is valid or not
* @param recieves a weight value
* @returns 1 if the value is valid and 0 if it is not
*/
int checkWeight(double weight);

/**
* Checks if the box volume input is valid or not
* @param recieves a volume value
* @returns 1 if the value is valid and 0 if it is not
*/
int checkBox(double boxSize);

/**
* Checks if the destination input is valid or not
* @param recieves the int row and char column for the destination value
* @returns 1 if the value is valid and 0 if it is not
*/
int checkDestination(int row, char col);

/**
* Finds the best truck for shipment after comparing, routes, shortest diverted paths, load already on the trucks 
* and percentages of the limiting factors. If the shipment cannot be delivered it returns a negative value
* @param *map recieves the address of the current map array holding the positions of all the buildings and empty spaces
* @param truckArr[] an array of truck elements containg details about the truck
* @param numOfTrucks total number of trucks in the array
* @param shipment A structure containing details of the shipment
* @returns index value of the selected truck in the array, -1 if no truck is able to take the shipment
*/
int selectTruck(struct Map *map, struct Truck truckArr[], int numOfTrucks, struct Shipment shipment);

/**
* Gets input about the shipment details validates the input and displays error prompts for incorrect input
* stores the correct input in a shipment data structure and returns the data structure
* @returns the shipment structure with details about the shipment
*/
struct Shipment getUserInput();

/**
* Gets the shortest possible path when a truck's route needs to be diverted for a shipment
* gets all the points on the map that make up the route and stores them in the divertedRoute structure
* @param *map recieves the address of the current map array holding the positions of all the buildings and empty spaces
* @param truck the truck to be used for shipment
* @param destination the destination of the diverted path
* @returns the diverted route structure
*/
struct DivertedRoute getDivertedRoute(struct Map* map, struct Truck truck, const struct Point destination);

/**
* returns the valid length of an in arrays
* @param the array to calculate length for
* @returns length
*/
int getArrLength(int arr[], int length);
#endif // DELIVERY_H