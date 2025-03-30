#pragma once
using namespace System;

// Class to store the extreme data (peak or valley)
public ref class Extreme
{
public:
	// Property to store the date of the extreme
	property DateTime date;
	// Property to store the price of the extreme
	property double price;
	// Property to store the type of the extreme (peak or valley)
	property bool isPeak;
	/// <summary>
	/// Constructor to initialize the extreme object
	/// </summary>
	/// <param name="date">The date of the extreme</param>
	/// <param name="price">The price of the extreme</param>
	/// <param name="isPeak">Boolean value to check if extreme is peak or valley</param>
	Extreme(DateTime date, double price, bool isPeak)
	{
		// Assign date to the extreme object
		this->date = date;
		// Assign price to the extreme object
		this->price = price;
		// Assign isPeak to the extreme object
		this->isPeak = isPeak;
	}
};

