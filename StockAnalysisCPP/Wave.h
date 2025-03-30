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
	// Property to store the index of the start of the wave in the list of data points
	property int startIndex;
	// Property to store the index of the end of the wave in the list of data points
	property int endIndex;

	/// <summary>
	/// Constructor to initialize the wave object
	/// </summary>
	/// <param name="startDate">Wave's start date</param>
	/// <param name="endDate">Wave's end date</param>
	/// <param name="startPrice">Wave's start price</param>
	/// <param name="endPrice">Wave's end price</param>
	/// <param name="startIndex">Wave's start index</param>
	/// <param name="endIndex">Wave's end index</param>
	Wave(DateTime startDate, DateTime endDate, double startPrice, double endPrice, int startIndex, int endIndex)
	{
		// Assign start date to the wave object
		this->startDate = startDate;
		// Assign end date to the wave object
		this->endDate = endDate;
		// Assign start price to the wave object
		this->startPrice = startPrice;
		// Assign end price to the wave object
		this->endPrice = endPrice;
		// Assign start index to the wave object
		this->startIndex = startIndex;
		// Assign end index to the wave object
		this->endIndex = endIndex;
	}
};

