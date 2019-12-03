// cuber_test_suites.cpp  INCOMPLETE
// Glenn G. Chappell
// 2019-11-22
//
// For CS 311 Fall 2019
// Tests for class Cuber: test suites
// For Project 8, Exercise B
// Uses the "Catch" unit-testing framework, version 2
// Requires cuber_test_main.cpp, catch.hpp, cuber.h

// Includes for code to be tested
#include "cuber.h"         // For class Cuber
#include "cuber.h"         // Double inclusion test

#define CATCH_CONFIG_FAST_COMPILE
                           // Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework

// Additional includes for this test program


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE("Cubber: Input types")
{
	Cuber cc;
	SECTION("Testing various const & non-const types") 
	{
		const int n_int = 1;
		cc(n_int);
		const double n_doub = -5.5;
		cc(n_doub);
		const char c = 'b';
		cc(c);

		int cn_int = -1;
		cc(cn_int);
		double cn_doub = 0.9;
		cc(cn_doub);
		char c_char = 'b';
		cc(c_char);
		{
		INFO("Program failed to compile")
			REQUIRE(0 == 0);
		}
   }

}

TEST_CASE("Cuber: Calculating Answers")
{
	Cuber cc;
	SECTION("positive numbers")
	{
		INFO("Answers for both small and large positive numbers should be correct")
		{
			int arg = -5;
			int result = pow(arg,3);
			INFO(arg << " cubed is " << result);
			REQUIRE(cc(arg) == result);
		}
		{
			INFO("1.1 cubed is 1.331");
			REQUIRE(cc(1.1) == Approx(1.331));
		}
			REQUIRE(cc(2) == pow(2, 3));
	}
	SECTION("negative numbers")
	{

	}
	SECTION("special cases (0, 1, -1)")
	{

	}
}
