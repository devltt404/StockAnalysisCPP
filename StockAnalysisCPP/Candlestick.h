#pragma once
using namespace System;

public ref class Candlestick
{
public:
	// Property to store the date of the candlestick
	property DateTime date;			
	// Property to store the opening price of the stock on the day
	property double open;
	// Property to store the closing price of the stock on the day
	property double close;
	// Property to store the highest price of the stock on the day
	property double high;				
	// Property to store the lowest price of the stock on the day
	property double low;				
	// Property to store the number of shares traded on the day
	property unsigned long long volume;

	/// <summary>
	/// Constructor to create a Candlestick object from a row of stock data values
	/// </summary>
	Candlestick(String^ rowOfData);
};

