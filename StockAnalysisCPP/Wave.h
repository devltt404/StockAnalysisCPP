#pragma once
using namespace System;

// Class to store the stock wave data
public ref class Wave
{
public:
    // Property to store the start date of the wave
	property DateTime startDate;
	// Property to store the end date of the wave
	property DateTime endDate;
	// Property to store the start price of the wave
	property double startPrice;
	// Property to store the end price of the wave
	property double endPrice;

	/// <summary>
	/// Constructor to initialize the wave object
	/// </summary>
	/// <param name="startDate">Wave's start date</param>
	/// <param name="endDate">Wave's end date</param>
	/// <param name="startPrice">Wave's start price</param>
	/// <param name="endPrice">Wave's end price</param>
	Wave(DateTime startDate, DateTime endDate, double startPrice, double endPrice)
	{
		this->startDate = startDate;
		this->endDate = endDate;
		this->startPrice = startPrice;
		this->endPrice = endPrice;
	}
};

