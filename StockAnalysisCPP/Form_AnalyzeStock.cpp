#include "pch.h"
#include "Form_AnalyzeStock.h"
using namespace System::Windows::Forms::DataVisualization::Charting;

using namespace System;
using namespace System::IO;
using namespace CppCLRWinFormsProject;
using namespace System::Windows::Forms;
using namespace System::Drawing;


/// <summary>
/// Function to initialize the form components and data members
/// </summary>
Void Form_AnalyzeStock::intializeForm() {
	// Initialize the form components  
	InitializeComponent();
	// Initialize the candlesticks list  
	candlesticks = gcnew List<Candlestick^>();
	// Initialize the filtered candlesticks list  
	filteredCandlesticks = gcnew List<Candlestick^>();
	// Initialize the extremes list  
	extremes = gcnew List<Extreme^>();
	// Initialize the up waves list  
	upWaves = gcnew List<Wave^>();
	// Initialize the down waves list  
	downWaves = gcnew List<Wave^>();
	// Initialize the confirmation annotations list
	confirmationAnnotations = gcnew List<EllipseAnnotation^>();
}

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
Void Form_AnalyzeStock::openFileDialog_loadTicker_FileOk(System::Object^ sender, CancelEventArgs^ e) {
	// Get the number of files selected in the OpenFileDialog  
	int numFiles = openFileDialog_loadTicker->FileNames->Length;
	// Get the start date selected by the user  
	DateTime startDate = dateTimePicker_startDate->Value;
	// Get the end date selected by the user  
	DateTime endDate = dateTimePicker_endDate->Value;

	// Loop through the selected files  
	for (int i = 0; i < numFiles; i++) {
		// Get the file name  
		String^ fileName = openFileDialog_loadTicker->FileNames[i];
		// Get the name of ticker from the current file name  
		String^ tickerName = Path::GetFileNameWithoutExtension(fileName);
		// Declare a form to display and analyze stock data  
		Form_AnalyzeStock^ analyzeStockForm;

		// Check if the current file is the first file selected  
		if (i == 0) {
			// Use the current form to display and analyze stock data of the first file  
			analyzeStockForm = this;
			// Set the selected downwave to empty
			comboBox_downWave->Text = "";
			// Set the selected upwave to empty
			comboBox_upWave->Text = "";
			// Read the candlestick data from the selected file  
			readCandlesticksFromFile(fileName);
			// Display the stock data based on the user-selected date range  
			displayStockData();
		}
		else {
			// Create a new form to display and analyze stock data of the subsequent files
			analyzeStockForm = gcnew Form_AnalyzeStock(fileName, startDate, endDate, trackBar_peakValleyMargin->Value);
		}

		// Set the title of the form to the ticker name  
		analyzeStockForm->Text = tickerName;
		// Show the form  
		analyzeStockForm->Show();
	}
}

/// <summary>
/// Function to compare two candlesticks by date
/// </summary>
/// <param name="a">First candlestick</param>
/// <param name="b">Second candlestick</param>
/// <returns>Returns an integer value indicating the comparison result</returns>
int compareCandlesticks(Candlestick^ a, Candlestick^ b) {
	// Compare the dates of the candlesticks
	return a->date.CompareTo(b->date);
}


/// <summary>  
/// Function to read candlestick data from the selected file and store it in a list  
/// </summary>  
/// <param name="fileName">The filename of selected file</param>  
Void Form_AnalyzeStock::readCandlesticksFromFile(String^ fileName)
{
	// Declare the expected header row (first line) of the CSV file
	const String^ expectedHeader = "\"Date\",\"Open\",\"High\",\"Low\",\"Close\",\"Volume\"";

	// Open the file to read its contents
	try
	{
		// Create a new StreamReader to read the file
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

		// Sort the candlesticks list by date in ascending order
		candlesticks->Sort(gcnew Comparison<Candlestick^>(compareCandlesticks));
	}
	// Catch any exceptions that occur when reading the file
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
	for each (Candlestick ^ c in candlesticks)
	{
		// Check if the candlestick date is within the user-selected date range
		if (c->date >= startDate && c->date <= endDate)
		{
			// Add the candlestick to the filtered list
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
	// Find the minimum low price in the filtered candlesticks
	double minLow = Double::MaxValue;
	// Find the maximum high price in the filtered candlesticks
	double maxHigh = Double::MinValue;

	// Iterate through filtered candlesticks to determine min and max values
	for each (Candlestick ^ c in filteredCandlesticks)
	{
		// If the low price of the candlestick is less than the current minimum low price
		if (c->low < minLow)
			// Set the minimum low price to the low price of the candlestick
			minLow = c->low;
		// If the high price of the candlestick is greater than the current maximum high price
		if (c->high > maxHigh)
			// Set the maximum high price to the high price of the candlestick
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
/// Calls functions to filter candlesticks, reset, and update the chart
/// </summary>
Void Form_AnalyzeStock::displayStockData() {
	// Filter the candlesticks based on the user-selected date range
	filterCandlesticks();

	// Clear existing OHLC data in the chart
	chart_stockData->Series["Series_OHLC"]->Points->Clear();
	// Clear existing Volume data in the chart
	chart_stockData->Series["Series_Volume"]->Points->Clear();
	// Clear existing annotations in the chart
	chart_stockData->Annotations->Clear();

	// Check if there are candlesticks within the date range to display
	if (filteredCandlesticks->Count > 0)
	{
		// Normalize the y-axis of the chart to fit the candlesticks data
		normalizeChart();
		// Display the candlestick data in the chart
		displayChart();
		// Detect peaks and valleys in the candlestick data
		detectPeakAndValley();
		// Detect waves in the candlestick data
		detectWaves();
	}
}

/// <summary>  
/// Function to add an arrow annotation for a peak or valley in the chart  
/// </summary>  
/// <param name="i">The index of the candlestick in the filtered candlesticks list that is peak or valley</param>  
/// <param name="isPeak">The boolean value indicating if the candlestick is a peak or valley</param>  
Void Form_AnalyzeStock::addPeakValleyAnnotation(int i, bool isPeak) {
	// Get the data point at the specified index in the OHLC series  
	DataPoint^ dataPoint = chart_stockData->Series["Series_OHLC"]->Points[i];
	// Create a new ArrowAnnotation instance  
	ArrowAnnotation^ arrow = gcnew ArrowAnnotation();
	// Set the annotation's X axis to the chart's X axis  
	arrow->AxisX = chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisX;
	// Set the annotation's Y axis to the chart's Y axis  
	arrow->AxisY = chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisY;
	// Set the annotation's arrow color to red for peak and green for valley  
	arrow->BackColor = isPeak ? Color::Red : Color::Green;
	// Set the annotation's arrow width to 0 (vertical)  
	arrow->Width = 0;
	// Set the annotation's arrow height to -10 (down) for peak and 10 (up) for valley  
	arrow->Height = isPeak ? -10 : 10;
	// Anchor the arrow to the specified DataPoint  
	arrow->SetAnchor(dataPoint);

	// If the candlestick is a valley  
	if (!isPeak) {
		// Adjust the arrow Y position to the low price of the candlestick  
		arrow->Y = (double)filteredCandlesticks[i]->low;
	}
	// Add the arrow annotation to the chart  
	chart_stockData->Annotations->Add(arrow);
}

/// <summary>
/// Function to detect peaks and valleys in the candlestick data
/// </summary>
Void Form_AnalyzeStock::detectPeakAndValley() {
	// Get the peak/valley margin value set by the user  
	int margin = trackBar_peakValleyMargin->Value;
	// Clear existing annotations in the chart  
	chart_stockData->Annotations->Clear();
	// Clear existing extremes list  
	extremes->Clear();

	// Loop through the filtered candlesticks list with a margin  
	for (int i = margin; i < filteredCandlesticks->Count - margin; i++) {
		// Declare a variable to store the current candlestick  
		Candlestick^ currentCandlestick = filteredCandlesticks[i];
		// Declare a variable to check if the current candlestick is a peak  
		bool isPeak = true;
		// Declare a variable to check if the current candlestick is a valley  
		bool isValley = true;

		// Check the previous and next candlesticks within the margin  
		for (int j = 1; j <= margin; j++) {
			// Declare a variable to store the previous candlestick  
			Candlestick^ prevCandlestick = filteredCandlesticks[i - j];
			// Declare a variable to store the next candlestick  
			Candlestick^ nextCandlestick = filteredCandlesticks[i + j];

			// If the current candlestick high is less than or equal to the previous or next candlestick high  
			if (currentCandlestick->high <= prevCandlestick->high || currentCandlestick->high <= nextCandlestick->high) {
				// The current candlestick is not a peak  
				isPeak = false;
			}

			// If the current candlestick low is greater than or equal to the previous or next candlestick low  
			if (currentCandlestick->low >= prevCandlestick->low || currentCandlestick->low >= nextCandlestick->low) {
				// The current candlestick is not a valley  
				isValley = false;
			}
		}

		// If the current candlestick is a peak  
		if (isPeak) {
			// Add the peak to the extremes list  
			extremes->Add(gcnew Extreme(currentCandlestick->date, currentCandlestick->high, true, i));
			// Add an arrow annotation to the chart indicating a peak  
			addPeakValleyAnnotation(i, true);
		}
		// If the current candlestick is a valley  
		if (isValley) {
			// Add the valley to the extremes list  
			extremes->Add(gcnew Extreme(currentCandlestick->date, currentCandlestick->low, false, i));
			// Add an arrow annotation to the chart indicating a valley  
			addPeakValleyAnnotation(i, false);
		}
	}
}

/// <summary>  
/// Function to handle the event when the user changes the value of trackBar_peakValleyMargin  
/// </summary>  
/// <param name="sender">The control that triggered the event</param>  
/// <param name="e">Event data</param>  
Void Form_AnalyzeStock::trackBar_peakValleyMargin_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	// Set the label_peakValleyMargin text to display the current value of the margin  
	// set by the user in the trackBar_peakValleyMargin  
	label_peakValleyMargin->Text = "Peak/Valley Margin: " + trackBar_peakValleyMargin->Value;
}

/// <summary>  
/// Function to handle the click event of the button_refresh  
/// </summary>  
/// <param name="sender">The control that triggered the event</param>  
/// <param name="e">Event data</param>  
Void Form_AnalyzeStock::button_refresh_Click(System::Object^ sender, System::EventArgs^ e) {
	// Reset the isValidWaveSelected flag to false
	isValidWaveSelected = false;
	// Display stock data based on the user-selected date range  
	displayStockData();
	// Clear the selected wave in the comboBox_downWave  
	comboBox_downWave->Text = "";
	// Clear the selected wave in the comboBox_upWave  
	comboBox_upWave->Text = "";
}

/// <summary>  
/// Function to detect waves in the candlestick data  
/// </summary>  
Void Form_AnalyzeStock::detectWaves() {
	// Clear existing waves in the upWaves list  
	upWaves->Clear();
	// Clear existing waves in the downWaves list  
	downWaves->Clear();
	// Clear existing items in the comboBox_downWave  
	comboBox_downWave->Items->Clear();
	// Clear existing items in the comboBox_upWave  
	comboBox_upWave->Items->Clear();
	// Loop through the extremes list to find waves  
	for (int i = 0; i < extremes->Count - 1; i++) {
		// Loop through the extremes list starting from the next index  
		for (int j = i + 1; j < extremes->Count; j++) {
			// Get the previous extreme value  
			auto prevExtreme = extremes[i];
			// Get the next extreme value  
			auto nextExtreme = extremes[j];
			// Create a new Wave object with the start and end dates and prices  
			Wave^ tempWave = gcnew Wave(prevExtreme->date, nextExtreme->date, prevExtreme->price, nextExtreme->price, prevExtreme->index, nextExtreme->index);
			// Create a label for the wave  
			String^ waveLabel = tempWave->startDate.ToString("MM/dd/yyyy") + " - " + tempWave->endDate.ToString("MM/dd/yyyy");

			// Check if 2 extremes have same date, then skip to next iteration
			if (prevExtreme->date == nextExtreme->date) continue;

			// Check if the wave is a down wave  
			if (prevExtreme->isPeak && !nextExtreme->isPeak && prevExtreme->price > nextExtreme->price) {
				// Add the wave to the downWaves list  
				downWaves->Add(tempWave);
				// Add the wave label to the comboBox_downWave  
				comboBox_downWave->Items->Add(waveLabel);
			}
			// Check if the wave is an up wave  
			else if (!prevExtreme->isPeak && nextExtreme->isPeak && prevExtreme->price < nextExtreme->price) {
				// Add the wave to the upWaves list  
				upWaves->Add(tempWave);
				// Add the wave label to the comboBox_upWave  
				comboBox_upWave->Items->Add(waveLabel);
			}
		}
	}
}

/// <summary>  
/// Function to handle the event when the user selects an up wave from the comboBox_upWave  
/// </summary>  
/// <param name="sender">The control that triggered the event</param>  
/// <param name="e">Event data</param>  
Void Form_AnalyzeStock::comboBox_upWave_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	// Check if the selected index is valid
	if (comboBox_upWave->SelectedIndex >= 0 && comboBox_upWave->SelectedIndex < upWaves->Count) {
		// Get the selected up wave  
		Wave^ selectedWave = upWaves[comboBox_upWave->SelectedIndex];

		// Draw the up wave  
		addWaveAnnotation(selectedWave, true);
	}
}

/// <summary>  
/// Function to handle the event when the user selects a down wave from the comboBox_downWave  
/// </summary>  
/// <param name="sender">The control that triggered the event</param>  
/// <param name="e">Event data</param>  
Void Form_AnalyzeStock::comboBox_downWave_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	// Check if the selected index is valid
	if (comboBox_downWave->SelectedIndex >= 0 && comboBox_downWave->SelectedIndex < downWaves->Count) {
		// Get the selected down wave  
		Wave^ selectedWave = downWaves[comboBox_downWave->SelectedIndex];

		// Draw the down wave  
		addWaveAnnotation(selectedWave, false);
	}
}

/// <summary>  
/// Function to add wave annotation to the chart  
/// </summary>  
/// <param name="wave">The selected wave object</param>  
/// <param name="isUp">Boolean value indicating if the wave is an up wave</param>  
Void Form_AnalyzeStock::addWaveAnnotation(Wave^ wave, bool isUp)
{
	// Get the existing annotations in the chart
	auto annotations = gcnew List<Annotation^>(chart_stockData->Annotations);
	// Clear existing wave annotations in the chart  
	for each (Annotation ^ annotation in annotations)
	{
		// Check if wave is up  
		if (isUp)
		{
			/// Check if the annotation is an up wave rectangle or line  
			if (annotation->Name == "Up_Wave_Rectangle" || annotation->Name == "Up_Wave_Line")
			{
				// Remove the annotation from the chart  
				chart_stockData->Annotations->Remove(annotation);
			}
		}
		// Check if wave is down  
		else
		{
			/// Check if the annotation is a down wave rectangle or line  
			if (annotation->Name == "Down_Wave_Rectangle" || annotation->Name == "Down_Wave_Line")
			{
				// Remove the annotation from the chart  
				chart_stockData->Annotations->Remove(annotation);
			}
		}
	}

	// Set the color of up wave to green and down wave to red  
	Color color = isUp ? Color::Green : Color::Red;

	// Get the x axis of the chart
	Axis^ axisX = chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisX;
	// Get the y axis of the chart
	Axis^ axisY = chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisY;
	// Get the x position of the wave annotation
	int x = wave->startIndex + 1;
	// Get the width of the wave annotation
	double width = axisX->ValueToPosition(wave->endIndex) - axisX->ValueToPosition(wave->startIndex);
	// Get the height of the wave annotation
	double height = axisY->ValueToPosition(wave->endPrice) - axisY->ValueToPosition(wave->startPrice);
	// Get the y position of the wave annotation
	double y = wave->startPrice;


	// Create rectangle annotation for the wave  
	RectangleAnnotation^ rect = gcnew RectangleAnnotation();
	// Set the name of the rectangle annotation  
	rect->Name = isUp ? "Up_Wave_Rectangle" : "Down_Wave_Rectangle";
	// Set the X axis of the rectangle annotation to the chart's X axis  
	rect->AxisX = chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisX;
	// Set the Y axis of the rectangle annotation to the chart's Y axis  
	rect->AxisY = chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisY;
	// Set the color of the rectangle annotation  
	rect->LineColor = color;
	// Set the width of the rectangle annotation  
	rect->LineWidth = 2;
	// Set the background color of the rectangle annotation  
	rect->BackColor = Color::FromArgb(35, color);
	// Enable annotation to overlap with other annotations  
	rect->SmartLabelStyle->Enabled = false;

	// Set the X position of the rectangle annotation
	rect->X = x;
	// Set the width of the rectangle annotation
	rect->Width = width;
	// Set the height of the rectangle annotation
	rect->Height = height;
	// Set the Y position of the rectangle annotation
	rect->Y = y;

	// Create diagonal line annotation  
	LineAnnotation^ line = gcnew LineAnnotation();
	// Set line name  
	line->Name = isUp ? "Up_Wave_Line" : "Down_Wave_Line";
	// Set line X axis to chart X axis  
	line->AxisX = chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisX;
	// Set line Y axis to chart Y axis  
	line->AxisY = chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisY;
	// Set line color  
	line->LineColor = color;
	// Set line width  
	line->LineWidth = 2;
	// Enable annotation to overlap with other annotations  
	line->SmartLabelStyle->Enabled = false;

	// Set the line x position
	line->X = x;
	// Set the line width
	line->Width = width;
	// Set the line height
	line->Height = height;
	// Set the line y position
	line->Y = y;

	// Add rectangle annotation to the chart  
	chart_stockData->Annotations->Add(rect);
	// Add line annotation to the chart  
	chart_stockData->Annotations->Add(line);

	// Refresh the chart  
	chart_stockData->Invalidate();
}

/// <summary>
/// Function to check if the selected wave of the rubber banding operation is valid
/// </summary>
/// <returns>Boolean value indicating if the selected wave is valid</returns>
bool Form_AnalyzeStock::isValidWave()
{
	// Get the start candlestick index of the wave
	int startCandlestickIdx = Math::Min(startPointIdx, endPointIdx);
	// Get the end candlestick index of the wave
	int endCandlestickIdx = Math::Max(startPointIdx, endPointIdx);

	// Check if the start and end index of the candlesticks are invalid
	if (startCandlestickIdx < 0 || endCandlestickIdx < 0 || startCandlestickIdx >= filteredCandlesticks->Count
		|| endCandlestickIdx >= filteredCandlesticks->Count)
	{
		// Return false if the indices are invalid
		return false;
	}
	else
	{
		// Loop through the upWaves list to check if the wave exists
		for each (Wave ^ wave in upWaves)
		{
			// Check if the start and end index of the wave matches the selected candlestick indices
			if (wave->startIndex == startCandlestickIdx && wave->endIndex == endCandlestickIdx)
			{
				// Return true if the wave exists
				return true;
			}
		}

		// Loop through the downWaves list to check if the wave exists
		for each (Wave ^ wave in downWaves)
		{
			// Check if the start and end index of the wave matches the selected candlestick indices
			if (wave->startIndex == startCandlestickIdx && wave->endIndex == endCandlestickIdx)
			{
				// Return true if the wave exists
				return true;
			}
		}

		// Return false if the wave does not exist
		return false;
	}
}

/// <summary>
/// Function to handle the mouse down event on the chart
/// </summary>
/// <param name="sender">The control that triggered the event</param>
/// <param name="e">Event data</param>
Void Form_AnalyzeStock::chart_stockData_MouseDown(Object^ sender, MouseEventArgs^ e)
{
	// Declare a variable to store the hit test result of the mouse event
	HitTestResult^ hit = chart_stockData->HitTest(e->X, e->Y);

	// Set the index of the start point of the rubber banding operation
	startPointIdx = hit->PointIndex;
	// Set the start point of the rubber banding operation
	startPoint = e->Location;
	// Set the isDragging to true
	isDragging = true;
	// Reset the boolean value to indicate if a valid wave is selected
	isValidWaveSelected = false;
}

/// <summary>
/// Function to handle the mouse up event on the chart
/// </summary>
/// <param name="sender">The control that triggered the event</param>
/// <param name="e">Event data</param>
Void Form_AnalyzeStock::chart_stockData_MouseUp(Object^ sender, MouseEventArgs^ e)
{
	// Set the isDragging to false
	isDragging = false;

	// Check if the selected wave is valid
	isValidWaveSelected = isValidWave();
}

/// <summary>
/// Function to handle the mouse move event on the chart
/// </summary>
/// <param name="sender">The control that triggered the event</param>
/// <param name="e">Event data</param>
Void Form_AnalyzeStock::chart_stockData_MouseMove(Object^ sender, MouseEventArgs^ e)
{
	// Declare a variable to store the hit test result of the mouse event
	HitTestResult^ hit = chart_stockData->HitTest(e->X, e->Y);

	// Check if the mouse is being dragged and mouse is moved in the ohlc chart area
	if (isDragging && hit->ChartArea != nullptr && hit->ChartArea->Name == "ChartArea_OHLC")
	{
		// Set the current point of the mouse in the chart area
		currentPoint = e->Location;
		// Set the end point index of the rubber banding operation
		endPointIdx = hit->PointIndex;
		// Invalidate the chart to refresh the display
		chart_stockData->Invalidate();
	}
}

/// <summary>
/// Function to handle the paint event of the chart
/// </summary>
/// <param name="sender">The control that triggered the event</param>
/// <param name="e">Event data</param>
Void Form_AnalyzeStock::chart_stockData_Paint(Object^ sender, PaintEventArgs^ e)
{
	// Check if the user is dragging the mouse or a valid wave is selected
	if (isDragging || isValidWaveSelected)
	{
		// Loop through the confirmation annotations list
		for each (EllipseAnnotation ^ annotation in confirmationAnnotations)
		{
			// Remove the existing confirmation annotations from the chart
			chart_stockData->Annotations->Remove(annotation);
		}
		// Clear the confirmation annotations list
		confirmationAnnotations->Clear();

		// Get the graphics object from the event
		Graphics^ g = e->Graphics;

		// Get the x of the rectangle
		int x = startPoint.X;
		// Get the y of the rectangle
		int y = Math::Min(startPoint.Y, currentPoint.Y);
		// Get the width of the rectangle
		int width = Math::Abs(currentPoint.X - startPoint.X);
		// Get the height of the rectangle
		int height = Math::Abs(currentPoint.Y - startPoint.Y);

		// Check if the enclosing rectangle is valid wave
		bool isRectangleValidWave = isValidWave();

		// Declare pen to draw the rectangle
		Pen^ pen = gcnew Pen(Color::Red, 2);
		// Draw the enclosing rectangle
		g->DrawRectangle(pen, x, y, width, height);
		delete pen;

		// Declare pen to draw the diagonal line
		pen = gcnew Pen(Color::Red, 2);
		// Check if mouse is moving up
		if (currentPoint.Y < startPoint.Y)
		{
			// Draw the diagonal line
			g->DrawLine(pen, x, startPoint.Y, x + width, startPoint.Y - height);
		}
		// Check if mouse is moving down
		else
		{
			// Draw the diagonal line
			g->DrawLine(pen, x, y, x + width, y + height);
		}
		delete pen;

		// Declare brush to fill the rectangle
		SolidBrush^ fillBrush = gcnew SolidBrush(Color::FromArgb(35, isRectangleValidWave ? Color::Green : Color::Red));
		// Fill the rectangle on the chart
		g->FillRectangle(fillBrush, x, y, width, height);
		delete fillBrush;

		// Check if the selected rectangle is a valid wave
		if (isRectangleValidWave)
		{
			// Check if the selected wave is a down wave
			bool isDownWave = filteredCandlesticks[startPointIdx]->high > filteredCandlesticks[endPointIdx]->high;
			// Declare an array of Fibonacci levels
			array<double>^ fibonacciLevels = { 0.0, 0.236, 0.382, 0.5, 0.618, 0.764, 1.0 };
			// Declare a list to store the Fibonacci prices
			List<double>^ fibonacciPrices = gcnew List<double>();

			// Loop through the Fibonacci levels
			for each (double level in fibonacciLevels)
			{
				// Calculate the y position of the Fibonacci level
				int levelY = y + (int)(level * height);

				// Declare a pen to draw the Fibonacci level line
				Pen^ levelPen = gcnew Pen(Color::Blue, 2);
				// Draw the Fibonacci level line
				g->DrawLine(levelPen, x, levelY, x + width, levelY);
				delete levelPen;

				// Declare a font to draw the Fibonacci level text
                System::Drawing::Font^ levelFont = gcnew System::Drawing::Font("Arial", 10, System::Drawing::FontStyle::Bold);
				// Add the Fibonacci level price to the list
				double price = chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisY->PixelPositionToValue(levelY);
				fibonacciPrices->Add(price);
				// Format the Fibonacci level label
				double labelLevel = isDownWave ? (1 - level) : level;
				String^ label = String::Format("{0:0.0}% ({1:0.000})", labelLevel * 100, price);
				// Draw the Fibonacci level text
				g->DrawString(label, levelFont, Brushes::Black, x + width + 5, levelY - 10);
				delete levelFont;
			}

			// Calculate the margin for the confirmations
			double margin = Math::Abs(
				chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisY->PixelPositionToValue(currentPoint.Y) -
				chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisY->PixelPositionToValue(startPoint.Y)
			) * 0.015;

			// Loop through the candlesticks in the selected wave
			for (int i = startPointIdx; i <= endPointIdx; i++)
			{
				// Get the candlestick at the current index
				auto candlestick = filteredCandlesticks[i];
				// Declare a list to store the OHLC values
				array<double>^ ohlc = gcnew array<double> { candlestick->open, candlestick->high, candlestick->low, candlestick->close };

				// Loop through the OHLC values
				for each (double price in ohlc)
				{
					// Loop through the Fibonacci prices
					for each (double fibonacciPrice in fibonacciPrices)
					{
						// Check if the price is within the margin of the Fibonacci price
						if (price >= fibonacciPrice - margin && price <= fibonacciPrice + margin)
						{
							// Create a new EllipseAnnotation for the confirmation
							EllipseAnnotation^ confirmationAnnotation = gcnew EllipseAnnotation();
							// Set the axisX
							confirmationAnnotation->AxisX = chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisX;
							// Set the axisY
							confirmationAnnotation->AxisY = chart_stockData->ChartAreas["ChartArea_OHLC"]->AxisY;
							// Set the anchor data point
							confirmationAnnotation->AnchorDataPoint = chart_stockData->Series["Series_OHLC"]->Points[i];
							// Set the Y position
							confirmationAnnotation->Y = price;
							// Set the width
							confirmationAnnotation->Width = 0.6;
							// Set the height
							confirmationAnnotation->Height = 1.2;
							// Set the background color
							confirmationAnnotation->BackColor = Color::Yellow;
							// Set the anchor alignment
							confirmationAnnotation->AnchorAlignment = ContentAlignment::MiddleCenter;
							// Add the confirmation annotation to the list
							confirmationAnnotations->Add(confirmationAnnotation);
							// Add the confirmation annotation to the chart
							chart_stockData->Annotations->Add(confirmationAnnotation);
						}
					}
				}
			}
		}
	}
	// Set the label_confirmationsCount text to display the number of confirmations
	label_confirmationsCount->Text = String::Format("Number of confirmations: {0}", confirmationAnnotations->Count);
}
