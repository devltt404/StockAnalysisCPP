#include "pch.h"
#include "Form_AnalyzeStock.h"

using namespace System;
using namespace System::IO;
using namespace CppCLRWinFormsProject;
using namespace System::Windows::Forms;

/// <summary>
/// Function to handle the click event of the button_loadTicker
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
Void Form_AnalyzeStock::button_loadTicker_Click(System::Object^ sender, System::EventArgs^ e) {
	// Display the OpenFileDialog to allow the user to select a ticker file
	openFileDialog_loadTicker->ShowDialog();
}

/// <summary>
/// Function to handle the event after user selects a ticker file in the OpenFileDialog
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
Void Form_AnalyzeStock::openFileDialog_loadTicker_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
	// Set the title of the form to the name of the selected file
	Text = Path::GetFileNameWithoutExtension(openFileDialog_loadTicker->FileName);

    // Read the candlestick data from the selected file
    readCandlesticksFromFile();
    // Filter the candlesticks based on the user-selected date range
    filterCandlesticks();
    // Normalize the y-axis of the chart to fit the candlesticks data
    normalizeChart();
    // Display the candlestick data in the chart
    displayChart();
    // Display the candlestick data in the DataGridView
    displayDataGridView();
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
        if (c->date >= startDate && c->date <= endDate)
        {
            filteredCandlesticks->Add(c);
        }
    }
}

/// <summary>
/// Function to normalize the y-axis of the chart 
/// to fit the candlesticks data for better visualization
/// </summary>
Void Form_AnalyzeStock::normalizeChart()
{
    // Check if there are no candlesticks within the date range to display
    if (filteredCandlesticks->Count == 0)
    {
        // Exit function
        return;
    }

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
    // Clear existing data in the chart
    chart_stockData->Series["Series_OHLC"]->Points->Clear();
    chart_stockData->Series["Series_Volume"]->Points->Clear();

    // Loop through each candlestick in the filtered list
    for each(Candlestick ^ candle in filteredCandlesticks)
    {
        // Add a data point to the "Series_OHLC" series (X: date, Y: high, low, open, close)
        int pointIdx = chart_stockData->Series["Series_OHLC"]->Points->AddXY(
            candle->date, candle->high, candle->low, candle->open, candle->close);

        // Add a data point to the "Series_Volume" series (X: date, Y: volume)
        chart_stockData->Series["Series_Volume"]->Points->AddXY(candle->date, candle->volume);
    }
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
/// <param name="sender"></param>
/// <param name="e"></param>
Void Form_AnalyzeStock::dateTimePicker_startDate_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    // Filter the candlesticks based on the user-selected date range
    filterCandlesticks();
    // Normalize the y-axis of the chart to fit the candlesticks data
    normalizeChart();
    // Display the candlestick data in the chart
    displayChart();
    // Display the candlestick data in the DataGridView
    displayDataGridView();
}

/// <summary>
/// Function to handle the event when the user selects a date in the end date picker
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
Void Form_AnalyzeStock::dateTimePicker_endDate_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    // Filter the candlesticks based on the user-selected date range
    filterCandlesticks();
    // Normalize the y-axis of the chart to fit the candlesticks data
    normalizeChart();
    // Display the candlestick data in the chart
    displayChart();
    // Display the candlestick data in the DataGridView
    displayDataGridView();
}
