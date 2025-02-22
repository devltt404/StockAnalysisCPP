#include "pch.h"
#include "Form_AnalyzeStock.h"

using namespace System;
using namespace System::IO;
using namespace CppCLRWinFormsProject;
using namespace System::Windows::Forms;

/// <summary>
/// Function to handle the click event of the button_loadTicker
/// </summary>
/// <param name="sender">The control that triggered the event</param>
/// <param name="e">Event data</param>
Void Form_AnalyzeStock::button_loadTicker_Click(System::Object^ sender, System::EventArgs^ e) {
	// Display the OpenFileDialog to allow the user to select a ticker file
	openFileDialog_loadTicker->ShowDialog();
}

/// <summary>
/// Function to handle the event after user selects a ticker file in the OpenFileDialog
/// </summary>
/// <param name="sender">The control that triggered the event</param>
/// <param name="e">Event data</param>
Void Form_AnalyzeStock::openFileDialog_loadTicker_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	// Set the title of the form to the name of the selected file
	Text = Path::GetFileNameWithoutExtension(openFileDialog_loadTicker->FileName);

    // Read the candlestick data from the selected file
    readCandlesticksFromFile();

    // Display stock data based on the user-selected date range
    displayStockData();
}

/// <summary>
/// Function to read candlestick data from the selected file and store it in a list
/// </summary>
Void Form_AnalyzeStock::readCandlesticksFromFile()
{
    // Get the file name selected in the OpenFileDialog
    String^ fileName = openFileDialog_loadTicker->FileName;

    // Declare the expected header row (first line) of the CSV file
    const String^ expectedHeader = "\"Date\",\"Open\",\"High\",\"Low\",\"Close\",\"Volume\"";

    // Open the file to read its contents
    try
    {
        StreamReader^ sr = gcnew StreamReader(fileName);

        // Read the first line of the file
        String^ line = sr->ReadLine();

        // Clear the existing elements in the candlesticks list
        candlesticks->Clear();

        // Read the file until reaching the end
        while (!sr->EndOfStream)
        {
            // Read a line from the file
            line = sr->ReadLine();
            // Create a new Candlestick object from the line
            Candlestick^ candlestick = gcnew Candlestick(line);
            // Add the Candlestick object to the list
            candlesticks->Add(candlestick);
        }

        // Close the StreamReader
        sr->Close();
    }
    catch (Exception^ ex)
    {
        // Show an error message if an exception occurs
        MessageBox::Show("Error reading file: " + ex->Message);
    }
}

/// <summary>
/// Function to filter the candlestick data based on user-selected date range
/// </summary>
Void Form_AnalyzeStock::filterCandlesticks()
{
    // Get the user-selected start date
    DateTime startDate = dateTimePicker_startDate->Value;
    // Get the user-selected end date
    DateTime endDate = dateTimePicker_endDate->Value;

    // Clear the existing filteredCandlesticks list
    filteredCandlesticks->Clear();

    // Iterate through candlesticks and filter based on the date range
    for each(Candlestick ^ c in candlesticks)
    {
		// Check if the candlestick date is within the user-selected date range
        if (c->date >= startDate && c->date <= endDate)
        {
			// Add the candlestick to the filtered list
            filteredCandlesticks->Add(c);
        }
    }

	// Check if the first candlestick date is greater than the second candlestick date
    if (filteredCandlesticks[0]->date > filteredCandlesticks[1]->date) {
		// Reverse the order of the filtered candlesticks
		filteredCandlesticks->Reverse();
    }
}

/// <summary>
/// Function to normalize the y-axis of the chart 
/// to fit the candlesticks data for better visualization
/// </summary>
Void Form_AnalyzeStock::normalizeChart()
{
    // Find the minimum low price in the filtered candlesticks
    double minLow = Double::MaxValue;
    // Find the maximum high price in the filtered candlesticks
    double maxHigh = Double::MinValue;

    // Iterate through filtered candlesticks to determine min and max values
    for each(Candlestick ^ c in filteredCandlesticks)
    {
        if (c->low < minLow)
            minLow = c->low;
        if (c->high > maxHigh)
            maxHigh = c->high;
    }

    // Calculate the 2% margin
    double margin = (maxHigh - minLow) * 0.02;

    // Set the minimum value of the y-axis for the OHLC chart area
    // to the minimum low price minus the margin
    chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisY->Minimum = minLow - margin;
    // Set the maximum value of the y-axis for the OHLC chart area
    // to the maximum high price plus the margin
    chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisY->Maximum = maxHigh + margin;
}

/// <summary>
/// Function to display the OHLCV stock data in the chart
/// </summary>
Void Form_AnalyzeStock::displayChart()
{
    // Set the data source of the chart to the filtered candlesticks list
    chart_stockData->DataSource = filteredCandlesticks;
    // Bind the data to the chart
    chart_stockData->DataBind();
}

/// <summary>
/// Function to display the stock data (OHLCV) in a DataGridView
/// </summary>
Void Form_AnalyzeStock::displayDataGridView()
{
    // Set the data source of the DataGridView to the filtered candlesticks list
    dataGridView_stockData->DataSource = filteredCandlesticks;
}

/// <summary>
/// Function to handle the event when the user selects a date in the start date picker
/// </summary>
/// <param name="sender">The control that triggered the event</param>
/// <param name="e">Event data</param>
Void Form_AnalyzeStock::dateTimePicker_startDate_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    // Display stock data based on the user-selected date range
    displayStockData();
}

/// <summary>
/// Function to handle the event when the user selects a date in the end date picker
/// </summary>
/// <param name="sender">The control that triggered the event</param>
/// <param name="e">Event data</param>
Void Form_AnalyzeStock::dateTimePicker_endDate_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    // Display stock data based on the user-selected date range
    displayStockData();
}

/// <summary>
/// Calls functions to filter candlesticks, reset, and update the chart and DataGridView
/// </summary>
Void Form_AnalyzeStock::displayStockData() {
    // Filter the candlesticks based on the user-selected date range
    filterCandlesticks();

    // Clear existing OHLC data in the chart
    chart_stockData->Series["Series_OHLC"]->Points->Clear();
    // Clear existing Volume data in the chart
    chart_stockData->Series["Series_Volume"]->Points->Clear();

    // Reset DataGridView data source
    dataGridView_stockData->DataSource = nullptr;

    // Check if there are candlesticks within the date range to display
    if (filteredCandlesticks->Count > 0)
    {
        // Normalize the y-axis of the chart to fit the candlesticks data
        normalizeChart();
        // Display the candlestick data in the chart
        displayChart();
        // Display the candlestick data in the DataGridView
        displayDataGridView();
    }
}