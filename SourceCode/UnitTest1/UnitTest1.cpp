#include "pch.h"
#include "CppUnitTest.h"
#include "delivery_r.h"
#include<iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FunctinsTest
{
	TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		Logger::WriteMessage("In Module Initialize");
	}

	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		Logger::WriteMessage("In Module Cleanup");
	}

	TEST_CLASS(checkWeightFunc)
	{
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In Class Initialize");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In Class Cleanup");
		}
	public:

		// Test1 to check if checkWeight returns true for valid input
		TEST_METHOD(WeightTest1)
		{
			double test = 20;
			bool x = checkWeight(test);
			Assert::IsTrue(x);
		}

		// Test2 to check if checkWeight returns false for > 1000 invalid input
		TEST_METHOD(WeightTest2)
		{
			double test = 1005;
			bool x = checkWeight(test);
			Assert::IsFalse(x);
		}

		// Test3 to check if checkWeight returns false for < 0 invalid input
		TEST_METHOD(WeightTest3)
		{
			double test = 0;
			bool x = checkWeight(test);
			Assert::IsFalse(x);
		}

		// Test 4 to check negative value
		TEST_METHOD(WeightTest4)
		{
			double test = -5;
			bool x = checkWeight(test);
			Assert::IsFalse(x);
		}

	};
	TEST_CLASS(checkBoxFunc)
	{
	public:

		// Test1 to check if checkBox returns true for valid input
		TEST_METHOD(VolumeTest1)
		{
			double test = .5;
			bool x = checkBox(test);
			Assert::IsTrue(x);
		}

		// Test2 to check if checkBox returns false invalid input
		TEST_METHOD(VolumeTest2)
		{
			double test = 2;
			bool x = checkBox(test);
			Assert::IsFalse(x);
		}

		// Test3 to check if checkBox returns false for 0 input
		TEST_METHOD(VolumeTest3)
		{
			double test = 0;
			bool x = checkBox(test);
			Assert::IsFalse(x);
		}

		// Test 4 to check negative values
		TEST_METHOD(VolumeTest4)
		{
			double test = -0.5;
			bool x = checkBox(test);
			Assert::IsFalse(x);
		}
	};
	TEST_CLASS(checkDestinationFunc)
	{
	public:

		// Test1 to check if checkDestination returns true for valid input
		TEST_METHOD(DestinationTest1)
		{
			int testInt = 12;
			char testChar = 'L';
			bool x = checkDestination(testInt, testChar);
			Assert::IsTrue(x);
		}

		// Test2 to check if checkDestination returns false for invalid input
		TEST_METHOD(DestinationTest2)
		{
			int testInt = 28;
			char testChar = 'x';
			bool x = checkDestination(testInt, testChar);
			Assert::IsFalse(x);
		}

		// Test3 to check if checkDestination returns false for 0 input
		TEST_METHOD(DestinationTest3)
		{
			int testInt = 0;
			char testChar = 'Z';
			bool x = checkDestination(testInt, testChar);
			Assert::IsFalse(x);
		}

		// Test4 to check empty corners
		TEST_METHOD(DestinationTest4)
		{
			int testInt = 1;
			char testChar = 'Y';
			bool x = checkDestination(testInt, testChar);
			Assert::IsFalse(x);
		}

		// Test5 to check edge destination
		TEST_METHOD(DestinationTest5)
		{
			int testInt = 24;
			char testChar = 'Y';
			bool x = checkDestination(testInt, testChar);
			Assert::IsTrue(x);
		}

		// Test6 to check mid map
		TEST_METHOD(DestinationTest6)
		{
			int testInt = 13;
			char testChar = 'L';
			bool x = checkDestination(testInt, testChar);
			Assert::IsTrue(x);
		}

		// Test7 to check empty points
		TEST_METHOD(DestinationTest7)
		{
			int testInt = 5;
			char testChar = 'N';
			bool x = checkDestination(testInt, testChar);
			Assert::IsFalse(x);
		}
	};

	TEST_CLASS(IntegrationTests)
	{
	public:

		// Test 1 for all valid values
		TEST_METHOD(IntegrationTest1)
		{
			double weight = 20, volume = 0.5;
			int testInt = 12;
			char testChar = 'L';
			
			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) { 
				x = true;
			}
			Assert::IsTrue(x);
		}

		// Test 2 for 1 invalid value
		TEST_METHOD(IntegrationTest2)
		{
			double weight = 20, volume = 3;
			int testInt = 12;
			char testChar = 'L';

			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) {
				x = true;
			}
			Assert::IsFalse(x);
		}

		// Test 3 for 2 invalid values
		TEST_METHOD(IntegrationTest3)
		{
			double weight = 10000, volume = 3;
			int testInt = 12;
			char testChar = 'L';

			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) {
				x = true;
			}
			Assert::IsFalse(x);
		}

		// Test 4 for all invalid values
		TEST_METHOD(IntegrationTest4)
		{
			double weight = 10000, volume = 3;
			int testInt = 0;
			char testChar = 'Z';

			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) {
				x = true;
			}
			Assert::IsFalse(x);
		}


		// Test 5 with negative values
		TEST_METHOD(IntegrationTest5)
		{
			double weight = -5, volume = 0.5;
			int testInt = 6;
			char testChar = 'G';

			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) {
				x = true;
			}
			Assert::IsFalse(x);
		}
	};

	TEST_CLASS(FinalizedIntegrationTests)
	{
	public:

		// Test 1 to check for Blue Line no Diversion
		TEST_METHOD(FinalIntegrationTest1)
		{
			double weight = 20, volume = 0.5;
			int testInt = 12;
			char testChar = 'L';


			struct Map map = populateMap();
			struct Route blueRoute = getBlueRoute();
			map = addRoute(&map, &blueRoute);
			struct Route yellowRoute = getYellowRoute();
			map = addRoute(&map, &yellowRoute);
			struct Route greenRoute = getGreenRoute();
			map = addRoute(&map, &greenRoute);

			int TruckIndex = -1;

			struct Truck truckArr[3] = { {"BLUE", 1000.0, 36.0, 0, 0, blueRoute}, {"YELLOW", 1000.0, 36.0, 0, 0, yellowRoute}, {"GREEN", 1000.0, 36.0, 0, 0, greenRoute} };

			struct Shipment testShip = { weight, volume, {testInt, (testChar - 65)}};

			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) {
				x = true;
			}

			if (x) {
				TruckIndex = selectTruck(&map, truckArr, 3, testShip);
			}

			Assert::IsTrue(x);
			Assert::AreEqual(TruckIndex, 0);
		}

		// Test 2 to check for Green Line no Diversion
		TEST_METHOD(FinalIntegrationTest2)
		{
			double weight = 200, volume = 1.0;
			int testInt = 9;
			char testChar = 'Y';


			struct Map map = populateMap();
			struct Route blueRoute = getBlueRoute();
			map = addRoute(&map, &blueRoute);
			struct Route yellowRoute = getYellowRoute();
			map = addRoute(&map, &yellowRoute);
			struct Route greenRoute = getGreenRoute();
			map = addRoute(&map, &greenRoute);

			int TruckIndex = -1;

			struct Truck truckArr[3] = { {"BLUE", 1000.0, 36.0, 0, 0, blueRoute}, {"YELLOW", 1000.0, 36.0, 0, 0, yellowRoute}, {"GREEN", 1000.0, 36.0, 0, 0, greenRoute} };

			struct Shipment testShip = { weight, volume, {testInt, (testChar - 65)} };

			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) {
				x = true;
			}

			if (x) {
				TruckIndex = selectTruck(&map, truckArr, 3, testShip);
			}

			Assert::IsTrue(x);
			Assert::AreEqual(TruckIndex, 2);
		}

		// Test 3 to check for Yellow Line no Diversion
		TEST_METHOD(FinalIntegrationTest3)
		{
			double weight = 500, volume = 1.0;
			int testInt = 19;
			char testChar = 'Y';


			struct Map map = populateMap();
			struct Route blueRoute = getBlueRoute();
			map = addRoute(&map, &blueRoute);
			struct Route yellowRoute = getYellowRoute();
			map = addRoute(&map, &yellowRoute);
			struct Route greenRoute = getGreenRoute();
			map = addRoute(&map, &greenRoute);

			int TruckIndex = -1;

			struct Truck truckArr[3] = { {"BLUE", 1000.0, 36.0, 0, 0, blueRoute}, {"YELLOW", 1000.0, 36.0, 0, 0, yellowRoute}, {"GREEN", 1000.0, 36.0, 0, 0, greenRoute} };

			struct Shipment testShip = { weight, volume, {testInt, (testChar - 65)} };

			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) {
				x = true;
			}

			if (x) {
				TruckIndex = selectTruck(&map, truckArr, 3, testShip);
			}

			Assert::IsTrue(x);
			Assert::AreEqual(TruckIndex, 1);
		}

		// Test 4 to check for another point on yellow route
		TEST_METHOD(FinalIntegrationTest4)
		{
			double weight = 500, volume = 1.0;
			int testInt = 12;
			char testChar = 'C';


			struct Map map = populateMap();
			struct Route blueRoute = getBlueRoute();
			map = addRoute(&map, &blueRoute);
			struct Route yellowRoute = getYellowRoute();
			map = addRoute(&map, &yellowRoute);
			struct Route greenRoute = getGreenRoute();
			map = addRoute(&map, &greenRoute);

			int TruckIndex = -1;

			struct Truck truckArr[3] = { {"BLUE", 1000.0, 36.0, 0, 0, blueRoute}, {"YELLOW", 1000.0, 36.0, 0, 0, yellowRoute}, {"GREEN", 1000.0, 36.0, 0, 0, greenRoute} };

			struct Shipment testShip = { weight, volume, {testInt, (testChar - 65)} };

			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) {
				x = true;
			}

			if (x) {
				TruckIndex = selectTruck(&map, truckArr, 3, testShip);
			}

			Assert::IsTrue(x);
			Assert::AreEqual(1, TruckIndex);
		}

		// Test 5 to check for another point on green route
		TEST_METHOD(FinalIntegrationTest5)
		{
			double weight = 500, volume = 1.0;
			int testInt = 3;
			char testChar = 'M';


			struct Map map = populateMap();
			struct Route blueRoute = getBlueRoute();
			map = addRoute(&map, &blueRoute);
			struct Route yellowRoute = getYellowRoute();
			map = addRoute(&map, &yellowRoute);
			struct Route greenRoute = getGreenRoute();
			map = addRoute(&map, &greenRoute);

			int TruckIndex = -1;

			struct Truck truckArr[3] = { {"BLUE", 1000.0, 36.0, 0, 0, blueRoute}, {"YELLOW", 1000.0, 36.0, 0, 0, yellowRoute}, {"GREEN", 1000.0, 36.0, 0, 0, greenRoute} };

			struct Shipment testShip = { weight, volume, {testInt, (testChar - 65)} };

			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) {
				x = true;
			}

			if (x) {
				TruckIndex = selectTruck(&map, truckArr, 3, testShip);
			}

			Assert::IsTrue(x);
			Assert::AreEqual(2, TruckIndex);
		}

		// Test 6 to check for another point on blue route
		TEST_METHOD(FinalIntegrationTest6)
		{
			double weight = 500, volume = 1.0;
			int testInt = 13;
			char testChar = 'J';


			struct Map map = populateMap();
			struct Route blueRoute = getBlueRoute();
			map = addRoute(&map, &blueRoute);
			struct Route yellowRoute = getYellowRoute();
			map = addRoute(&map, &yellowRoute);
			struct Route greenRoute = getGreenRoute();
			map = addRoute(&map, &greenRoute);

			int TruckIndex = -1;

			struct Truck truckArr[3] = { {"BLUE", 1000.0, 36.0, 0, 0, blueRoute}, {"YELLOW", 1000.0, 36.0, 0, 0, yellowRoute}, {"GREEN", 1000.0, 36.0, 0, 0, greenRoute} };

			struct Shipment testShip = { weight, volume, {testInt, (testChar - 65)} };

			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) {
				x = true;
			}

			if (x) {
				TruckIndex = selectTruck(&map, truckArr, 3, testShip);
			}

			Assert::IsTrue(x);
			Assert::AreEqual(0, TruckIndex);
		}

		// Test 7 to check for a point on the blue route
		TEST_METHOD(FinalIntegrationTest7)
		{
			double weight = 500, volume = 1.0;
			int testInt = 5;
			char testChar = 'J';


			struct Map map = populateMap();
			struct Route blueRoute = getBlueRoute();
			map = addRoute(&map, &blueRoute);
			struct Route yellowRoute = getYellowRoute();
			map = addRoute(&map, &yellowRoute);
			struct Route greenRoute = getGreenRoute();
			map = addRoute(&map, &greenRoute);

			int TruckIndex = -1;

			struct Truck truckArr[3] = { {"BLUE", 1000.0, 36.0, 0, 0, blueRoute}, {"YELLOW", 1000.0, 36.0, 0, 0, yellowRoute}, {"GREEN", 1000.0, 36.0, 0, 0, greenRoute} };

			struct Shipment testShip = { weight, volume, {testInt, (testChar - 65)} };

			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) {
				x = true;
			}

			if (x) {
				TruckIndex = selectTruck(&map, truckArr, 3, testShip);
			}

			Assert::IsFalse(x);
			Assert::AreEqual(-1, TruckIndex);
		}

		// Test 8 to check for another point on green route
		TEST_METHOD(FinalIntegrationTest8)
		{
			double weight = 500, volume = 1.0;
			int testInt = 1;
			char testChar = 'S';


			struct Map map = populateMap();
			struct Route blueRoute = getBlueRoute();
			map = addRoute(&map, &blueRoute);
			struct Route yellowRoute = getYellowRoute();
			map = addRoute(&map, &yellowRoute);
			struct Route greenRoute = getGreenRoute();
			map = addRoute(&map, &greenRoute);

			int TruckIndex = -1;

			struct Truck truckArr[3] = { {"BLUE", 1000.0, 36.0, 0, 0, blueRoute}, {"YELLOW", 1000.0, 36.0, 0, 0, yellowRoute}, {"GREEN", 1000.0, 36.0, 0, 0, greenRoute} };

			struct Shipment testShip = { weight, volume, {testInt, (testChar - 65)} };

			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) {
				x = true;
			}

			if (x) {
				TruckIndex = selectTruck(&map, truckArr, 3, testShip);
			}

			Assert::IsFalse(x);
			Assert::AreEqual(-1, TruckIndex);
		}

		// Test 9 to check for another point on yellow route
		TEST_METHOD(FinalIntegrationTest9)
		{
			double weight = 500, volume = 1.0;
			int testInt = 20;
			char testChar = 'W';


			struct Map map = populateMap();
			struct Route blueRoute = getBlueRoute();
			map = addRoute(&map, &blueRoute);
			struct Route yellowRoute = getYellowRoute();
			map = addRoute(&map, &yellowRoute);
			struct Route greenRoute = getGreenRoute();
			map = addRoute(&map, &greenRoute);

			int TruckIndex = -1;

			struct Truck truckArr[3] = { {"BLUE", 1000.0, 36.0, 0, 0, blueRoute}, {"YELLOW", 1000.0, 36.0, 0, 0, yellowRoute}, {"GREEN", 1000.0, 36.0, 0, 0, greenRoute} };

			struct Shipment testShip = { weight, volume, {testInt, (testChar - 65)} };

			bool wght = checkWeight(weight);
			bool vol = checkBox(volume);
			bool dest = checkDestination(testInt, testChar);

			bool x = false;

			if (wght && vol && dest) {
				x = true;
			}

			if (x) {
				TruckIndex = selectTruck(&map, truckArr, 3, testShip);
			}

			Assert::IsFalse(x);
			Assert::AreEqual(-1, TruckIndex);
		}
	};
}