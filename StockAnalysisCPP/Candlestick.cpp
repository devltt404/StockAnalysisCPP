#include "pch.h"
#include "Candlestick.h"

using namespace System::Globalization;

/// <summary>
/// Constructor to create a Candlestick object from a row of stock data values
/// </summary>
/// <param name="rowOfData">
/// A string representing a row of stock data in the format:
/// "Date,Open,High,Low,Close,Volume"
/// Example: "2024-08-15",9.9,10.1,9.9,10.1,32307255
/// </param>
Candlestick::Candlestick(String^ rowOfData)
{
	// Define the separators used to split the row of data
	array<wchar_t>^ separators = { L',', L'"' };

	// Split the row of data into an array of string tokens using the separators and removing empty tokens
	array<String^>^ tokens = rowOfData->Split(separators, StringSplitOptions::RemoveEmptyEntries);

	// Check if the number of tokens is not equal to 6
	if (tokens->Length != 6)
	{
		// Throw an exception indicating that the data format is invalid
		throw gcnew System::ArgumentException("Invalid data format.");
	}

	// Parse the date property
	date = DateTime::ParseExact(tokens[0], "yyyy-MM-dd", CultureInfo::InvariantCulture);
	// Parse the open price property
	open = Math::Round(Double::Parse(tokens[1]), 2);
	// Parse the high price property
	high = Math::Round(Double::Parse(tokens[2]), 2);
	// Parse the low price property
	low = Math::Round(Double::Parse(tokens[3]), 2);
	// Parse the close price property
	close = Math::Round(Double::Parse(tokens[4]), 2);
	// Parse the volume property
	volume = UInt64::Parse(tokens[5]);
}
