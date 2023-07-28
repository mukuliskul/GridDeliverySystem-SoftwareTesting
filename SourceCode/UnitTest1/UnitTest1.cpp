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
	};
}