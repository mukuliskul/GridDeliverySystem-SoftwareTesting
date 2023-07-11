#pragma once
#ifndef DELIVERY_H
#define DELIVERY_H

#include"mapping.h"

#define MAX_WEIGHT 1000
#define MAX_VOLUME 36

/*
* The Box sizes available for shipping
*/
const double boxVolume[3] = {1.0, 0.5, 0.25};



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
	double volumeReamining;
	int limitingFactor;
};

/*
* A collection of points that constitute the diverted path from the route of the 
* truck to the destination
*/
struct DiverterdRoute {
	struct Point divRoute[MAX_ROUTE];
};

#endif // DELIVERY_H