#pragma once
#include "Candlestick.h"
#include "Wave.h"
#include "Extreme.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	/// <summary>
	/// Summary for Form_AnalyzeStock
	/// </summary>
	public ref class Form_AnalyzeStock : public System::Windows::Forms::Form
	{
	public:
		Form_AnalyzeStock(void)
		{
			// Initialize the form components and data members
			intializeForm();
		}

	/// <summary>  
	/// Constructor to create a new instance of the Form_AnalyzeStock class  
	/// with specified ticker file name, start date, end date, and margin
	/// </summary>  
	/// <param name="tickerFileName">The ticker filename</param>  
	/// <param name="start">The start date for candlesticks filtering</param>  
	/// <param name="end">The end date for candlesticks filtering</param>  
	/// <param name="margin">The margin for peak and valley detection</param>
	public: Form_AnalyzeStock(String^ tickerFileName, DateTime start, DateTime end, int margin) {
		// Initialize the form components and data members  
		intializeForm();

		// Set the start date picker value to the specified start date  
		dateTimePicker_startDate->Value = start;
		// Set the end date picker value to the specified end date  
		dateTimePicker_endDate->Value = end;
		// Set the trackBar_peakValleyMargin value to the specified margin
		trackBar_peakValleyMargin->Value = margin;

		// Read the candlestick data from the selected file  
		readCandlesticksFromFile(tickerFileName);
		// Display the stock data based on the user-selected date range  
		displayStockData();
	}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form_AnalyzeStock()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button_loadTicker;
	protected:
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog_loadTicker;
	private: System::Windows::Forms::Label^ label_endDate;
	private: System::Windows::Forms::Label^ label_startDate;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_endDate;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_startDate;
	private: System::Windows::Forms::ComboBox^ comboBox_downWave;
	private: System::Windows::Forms::Label^ label_downWave;
	private: System::Windows::Forms::Label^ label_upWave;
	private: System::Windows::Forms::ComboBox^ comboBox_upWave;
	private: System::Windows::Forms::Button^ button_refresh;
	private: System::Windows::Forms::Label^ label_peakValleyMargin;
	private: System::Windows::Forms::TrackBar^ trackBar_peakValleyMargin;

	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart_stockData;
	private: System::ComponentModel::IContainer^ components;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Developer Code
	// Declare a list to store Candlestick objects
	private:List<Candlestick^>^ candlesticks;
	// Declare a list to store filtered candlestick objects
	private:List<Candlestick^>^ filteredCandlesticks;
	// Declare a list to store the extreme values (peaks and valleys)
	private: List<Extreme^>^ extremes;
	// Declare a list to store the up waves
	private: List<Wave^>^ upWaves;
	private: System::Windows::Forms::Label^ label_confirmationsCount;
	// Declare a list to store the down waves
	private: List<Wave^>^ downWaves;

	// Declare a variable to store the index of the starting point of the rubber banding operation
	private: int startPointIdx;
	// Declare a variable to store the index of the ending point of the rubber banding operation
	private: int endPointIdx;
	// Declare a variable to store the starting point of the rubber banding operation
	private: Point startPoint;
	// Declare a variable to store the current point of the mouse in the chart area
	private: Point currentPoint;
	// Declare a variable to indicate if the user is currently dragging the mouse in the chart area
	private: bool isDragging = false;
	// Declare a variable to indicate if the user has selected a valid wave
	private: bool isValidWaveSelected = false;
	// Declare a variable to store the confirmation annotations
	private: List<EllipseAnnotation^>^ confirmationAnnotations = nullptr;
	// Declare a variable to check if the selected wave is up
	private: bool isSelectUpWave = false;
	// Declare an array of Fibonacci levels
	private: array<double>^ fibonnaciLevels;

	// Declare a variable to store boolean value indicating if the simulation is running
	private: bool isSimulating = false;
	// Declare a variable to store the step size for the simulation
	private: double stepSize;
	// Declare a variable to store the current step count for the simulation
	private: int currentStep = 0;
private: System::Windows::Forms::Button^ button_minus;
private: System::Windows::Forms::Button^ button_plus;
private: System::Windows::Forms::Button^ button_simulate;
private: System::Windows::Forms::Timer^ timer_simulate;
private: System::Windows::Forms::Label^ label_steps;
private: System::Windows::Forms::TrackBar^ trackBar_steps;
private: System::Windows::Forms::Label^ label_range;
private: System::Windows::Forms::TrackBar^ trackBar_range;
	   // Declare a variable to store the number of steps for the simulation
	private: int numberOfSteps = 30;



	/// <summary>
	/// Function to initialize the form components and data members
	/// </summary>
	private: System::Void intializeForm();

	/// <summary>
	/// Function to handle the click event of the button_loadTicker
	/// </summary>
	/// <param name="sender">The control that triggered the event</param>
	/// <param name="e">Event data</param>
	private: System::Void button_loadTicker_Click(System::Object^ sender, System::EventArgs^ e);

	/// <summary>
	/// Function to handle the event after user selects a ticker file in the OpenFileDialog
	/// </summary>
	/// <param name="sender">The control that triggered the event</param>
	/// <param name="e">Event data</param>
	private: System::Void openFileDialog_loadTicker_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);

	/// <summary>  
	/// Function to read candlestick data from the selected file and store it in a list  
	/// </summary>  
	/// <param name="fileName">The filename of selected file</param>  
	private: void readCandlesticksFromFile(String^ fileName);

	/// <summary>
	/// Function to filter the candlestick data based on user-selected date range
	/// </summary>
	private: System::Void filterCandlesticks();

	/// <summary>
	/// Function to normalize the y-axis of the chart 
	/// to fit the candlesticks data for better visualization
	/// </summary>
	private: System::Void normalizeChart();

	/// <summary>
	/// Function to display the OHLCV stock data in the chart
	/// </summary>
	private: System::Void displayChart();

	/// <summary>
	/// Calls functions to filter candlesticks, reset, and update the chart
	/// </summary>
	private: System::Void displayStockData();

	/// <summary>  
	/// Function to add an arrow annotation for a peak or valley in the chart  
	/// </summary>  
	/// <param name="i">The index of the candlestick in the filtered candlesticks list that is peak or valley</param>  
	/// <param name="isPeak">The boolean value indicating if the candlestick is a peak or valley</param>  
	private: void addPeakValleyAnnotation(int i, bool isPeak);

	/// <summary>
	/// Function to detect peaks and valleys in the candlestick data
	/// </summary>
	private: void detectPeakAndValley();

	/// <summary>  
	/// Function to handle the event when the user changes the value of trackBar_peakValleyMargin  
	/// </summary>  
	/// <param name="sender">The control that triggered the event</param>  
	/// <param name="e">Event data</param>  
	private: void trackBar_peakValleyMargin_ValueChanged(System::Object^ sender, System::EventArgs^ e);

	/// <summary>  
	/// Function to handle the click event of the button_refresh  
	/// </summary>  
	/// <param name="sender">The control that triggered the event</param>  
	/// <param name="e">Event data</param>  
	private: void button_refresh_Click(System::Object^ sender, System::EventArgs^ e);

	/// <summary>  
	/// Function to detect waves in the candlestick data  
	/// </summary>  
	private: void detectWaves();

	/// <summary>  
	/// Function to handle the event when the user selects an up wave from the comboBox_upWave  
	/// </summary>  
	/// <param name="sender">The control that triggered the event</param>  
	/// <param name="e">Event data</param>  
	private: void comboBox_upWave_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);

	/// <summary>  
	/// Function to handle the event when the user selects a down wave from the comboBox_downWave  
	/// </summary>  
	/// <param name="sender">The control that triggered the event</param>  
	/// <param name="e">Event data</param>  
	private: void comboBox_downWave_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);

	/// <summary>
	/// Function to handle the event when the user selects a wave from the comboBox_downWave
	/// </summary>
	/// <param name="selectedWave">The selected wave</param>
	private: void handleSelectWave(Wave^ selectedWave);

	/// <summary>
	/// Function to annotate the confirmations in the chart
	/// </summary>
	private: void annotateConfirmations();

	/// <summary>
	/// Function to check if the selected wave of the rubber banding operation is valid
	/// </summary>
	/// <returns>Boolean value indicating if the selected wave is valid</returns>
	private: bool isValidWave();

	/// <summary>
	/// Function to handle the mouse down event on the chart
	/// </summary>
	/// <param name="sender">The control that triggered the event</param>
	/// <param name="e">Event data</param>
	private: System::Void chart_stockData_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	/// <summary>
	/// Function to handle the mouse move event on the chart
	/// </summary>
	/// <param name="sender">The control that triggered the event</param>
	/// <param name="e">Event data</param>
	private: System::Void chart_stockData_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	/// <summary>
	/// Function to handle the mouse up event on the chart
	/// </summary>
	/// <param name="sender">The control that triggered the event</param>
	/// <param name="e">Event data</param>
	private: System::Void chart_stockData_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	/// <summary>
	/// Function to handle the paint event of the chart
	/// </summary>
	/// <param name="sender">The control that triggered the event</param>
	/// <param name="e">Event data</param>
	private: System::Void chart_stockData_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);


	/// <summary>
	/// Function to handle the click event of the button_simulate
	/// </summary>
	/// <param name="sender">The control that triggered the event</param>
	/// <param name="e">Event data</param>
	private: System::Void button_simulate_Click(Object^ sender, EventArgs^ e);

	/// <summary>
	/// Function to handle the click event of the button_plus
	/// </summary>
	/// <param name="sender">The control that triggered the event</param>
	/// <param name="e">Event data</param>
	private: System::Void button_plus_Click(Object^ sender, EventArgs^ e);

	/// <summary>
	/// Function to handle the click event of the button_minus
	/// </summary>
	/// <param name="sender">The control that triggered the event</param>
	/// <param name="e">Event data</param>
	private: System::Void button_minus_Click(Object^ sender, EventArgs^ e);

	/// <summary>
	/// Function to handle the tick event of the timer_simulate
	/// </summary>
	/// <param name="sender">The control that triggered the event</param>
	/// <param name="e">Event data</param>
	private: System::Void timer_simulate_Tick(Object^ sender, EventArgs^ e);

	/// <summary>
	/// Function to stop the simulation
	/// </summary>
	private: System::Void stopSimulation();

	/// <summary>
	/// Function to handle the scroll event of the trackBar_range
	/// </summary>
	/// <param name="sender">The control that triggered the event</param>
	/// <param name="e">Event data</param>
	private: System::Void trackBar_range_Scroll(System::Object^ sender, System::EventArgs^ e);

	/// <summary>
	/// Function to handle the scroll event of the trackBar_steps
	/// </summary>
	/// <param name="sender">The control that triggered the event</param>
	/// <param name="e">Event data</param>
	private: System::Void trackBar_steps_Scroll(System::Object^ sender, System::EventArgs^ e);
#pragma endregion

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->button_loadTicker = (gcnew System::Windows::Forms::Button());
			this->openFileDialog_loadTicker = (gcnew System::Windows::Forms::OpenFileDialog());
			this->label_endDate = (gcnew System::Windows::Forms::Label());
			this->label_startDate = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker_endDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePicker_startDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->chart_stockData = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->comboBox_downWave = (gcnew System::Windows::Forms::ComboBox());
			this->label_downWave = (gcnew System::Windows::Forms::Label());
			this->label_upWave = (gcnew System::Windows::Forms::Label());
			this->comboBox_upWave = (gcnew System::Windows::Forms::ComboBox());
			this->button_refresh = (gcnew System::Windows::Forms::Button());
			this->label_peakValleyMargin = (gcnew System::Windows::Forms::Label());
			this->trackBar_peakValleyMargin = (gcnew System::Windows::Forms::TrackBar());
			this->label_confirmationsCount = (gcnew System::Windows::Forms::Label());
			this->button_minus = (gcnew System::Windows::Forms::Button());
			this->button_plus = (gcnew System::Windows::Forms::Button());
			this->button_simulate = (gcnew System::Windows::Forms::Button());
			this->timer_simulate = (gcnew System::Windows::Forms::Timer(this->components));
			this->label_steps = (gcnew System::Windows::Forms::Label());
			this->trackBar_steps = (gcnew System::Windows::Forms::TrackBar());
			this->label_range = (gcnew System::Windows::Forms::Label());
			this->trackBar_range = (gcnew System::Windows::Forms::TrackBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_stockData))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_peakValleyMargin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_steps))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_range))->BeginInit();
			this->SuspendLayout();
			// 
			// button_loadTicker
			// 
			this->button_loadTicker->BackColor = System::Drawing::Color::MediumBlue;
			this->button_loadTicker->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_loadTicker->ForeColor = System::Drawing::Color::White;
			this->button_loadTicker->Location = System::Drawing::Point(51, 22);
			this->button_loadTicker->Name = L"button_loadTicker";
			this->button_loadTicker->Size = System::Drawing::Size(202, 69);
			this->button_loadTicker->TabIndex = 0;
			this->button_loadTicker->Text = L"Load Ticker";
			this->button_loadTicker->UseVisualStyleBackColor = false;
			this->button_loadTicker->Click += gcnew System::EventHandler(this, &Form_AnalyzeStock::button_loadTicker_Click);
			// 
			// openFileDialog_loadTicker
			// 
			this->openFileDialog_loadTicker->FileName = L"ABBV-Day";
			this->openFileDialog_loadTicker->Filter = L"All Files|*.csv|Monthly|*-Month.csv|Daily|*-Day.csv|Weekly|*-Week.csv";
			this->openFileDialog_loadTicker->InitialDirectory = L"D:\\@DEVLTT404\\USF\\@@@Spring2025\\CIS4930_OOP\\StockAnalysisCPP\\Stock Data";
			this->openFileDialog_loadTicker->Multiselect = true;
			this->openFileDialog_loadTicker->ShowReadOnly = true;
			this->openFileDialog_loadTicker->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form_AnalyzeStock::openFileDialog_loadTicker_FileOk);
			// 
			// label_endDate
			// 
			this->label_endDate->AutoSize = true;
			this->label_endDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_endDate->ForeColor = System::Drawing::Color::Black;
			this->label_endDate->Location = System::Drawing::Point(46, 171);
			this->label_endDate->Name = L"label_endDate";
			this->label_endDate->Size = System::Drawing::Size(85, 22);
			this->label_endDate->TabIndex = 8;
			this->label_endDate->Text = L"End Date";
			// 
			// label_startDate
			// 
			this->label_startDate->AutoSize = true;
			this->label_startDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_startDate->ForeColor = System::Drawing::Color::Black;
			this->label_startDate->Location = System::Drawing::Point(46, 122);
			this->label_startDate->Name = L"label_startDate";
			this->label_startDate->Size = System::Drawing::Size(91, 22);
			this->label_startDate->TabIndex = 7;
			this->label_startDate->Text = L"Start Date";
			// 
			// dateTimePicker_endDate
			// 
			this->dateTimePicker_endDate->Location = System::Drawing::Point(144, 169);
			this->dateTimePicker_endDate->Name = L"dateTimePicker_endDate";
			this->dateTimePicker_endDate->Size = System::Drawing::Size(272, 26);
			this->dateTimePicker_endDate->TabIndex = 6;
			this->dateTimePicker_endDate->Value = System::DateTime(2021, 2, 28, 0, 0, 0, 0);
			// 
			// dateTimePicker_startDate
			// 
			this->dateTimePicker_startDate->Location = System::Drawing::Point(144, 118);
			this->dateTimePicker_startDate->Name = L"dateTimePicker_startDate";
			this->dateTimePicker_startDate->Size = System::Drawing::Size(272, 26);
			this->dateTimePicker_startDate->TabIndex = 5;
			this->dateTimePicker_startDate->Value = System::DateTime(2021, 2, 1, 0, 0, 0, 0);
			// 
			// chart_stockData
			// 
			chartArea1->AlignWithChartArea = L"ChartArea_Volume";
			chartArea1->Name = L"ChartArea_OHLC";
			chartArea2->Name = L"ChartArea_Volume";
			this->chart_stockData->ChartAreas->Add(chartArea1);
			this->chart_stockData->ChartAreas->Add(chartArea2);
			this->chart_stockData->Location = System::Drawing::Point(44, 218);
			this->chart_stockData->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->chart_stockData->Name = L"chart_stockData";
			series1->ChartArea = L"ChartArea_OHLC";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Candlestick;
			series1->CustomProperties = L"PriceDownColor=Red, PriceUpColor=Green";
			series1->IsXValueIndexed = true;
			series1->Name = L"Series_OHLC";
			series1->XValueMember = L"Date";
			series1->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Date;
			series1->YValueMembers = L"high,low,open,close";
			series1->YValuesPerPoint = 4;
			series2->ChartArea = L"ChartArea_Volume";
			series2->IsXValueIndexed = true;
			series2->Name = L"Series_Volume";
			series2->XValueMember = L"Date";
			series2->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Date;
			series2->YValueMembers = L"Volume";
			series2->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::UInt64;
			this->chart_stockData->Series->Add(series1);
			this->chart_stockData->Series->Add(series2);
			this->chart_stockData->Size = System::Drawing::Size(1526, 748);
			this->chart_stockData->TabIndex = 10;
			this->chart_stockData->Text = L"chart1";
			this->chart_stockData->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form_AnalyzeStock::chart_stockData_Paint);
			this->chart_stockData->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form_AnalyzeStock::chart_stockData_MouseDown);
			this->chart_stockData->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form_AnalyzeStock::chart_stockData_MouseMove);
			this->chart_stockData->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form_AnalyzeStock::chart_stockData_MouseUp);
			// 
			// comboBox_downWave
			// 
			this->comboBox_downWave->FormattingEnabled = true;
			this->comboBox_downWave->Location = System::Drawing::Point(710, 142);
			this->comboBox_downWave->Name = L"comboBox_downWave";
			this->comboBox_downWave->Size = System::Drawing::Size(240, 28);
			this->comboBox_downWave->TabIndex = 19;
			this->comboBox_downWave->SelectedIndexChanged += gcnew System::EventHandler(this, &Form_AnalyzeStock::comboBox_downWave_SelectedIndexChanged);
			// 
			// label_downWave
			// 
			this->label_downWave->AutoSize = true;
			this->label_downWave->Location = System::Drawing::Point(706, 106);
			this->label_downWave->Name = L"label_downWave";
			this->label_downWave->Size = System::Drawing::Size(103, 20);
			this->label_downWave->TabIndex = 18;
			this->label_downWave->Text = L"DOWN Wave";
			// 
			// label_upWave
			// 
			this->label_upWave->AutoSize = true;
			this->label_upWave->Location = System::Drawing::Point(706, 26);
			this->label_upWave->Name = L"label_upWave";
			this->label_upWave->Size = System::Drawing::Size(75, 20);
			this->label_upWave->TabIndex = 17;
			this->label_upWave->Text = L"UP Wave";
			// 
			// comboBox_upWave
			// 
			this->comboBox_upWave->FormattingEnabled = true;
			this->comboBox_upWave->Location = System::Drawing::Point(710, 58);
			this->comboBox_upWave->Name = L"comboBox_upWave";
			this->comboBox_upWave->Size = System::Drawing::Size(240, 28);
			this->comboBox_upWave->TabIndex = 16;
			this->comboBox_upWave->SelectedIndexChanged += gcnew System::EventHandler(this, &Form_AnalyzeStock::comboBox_upWave_SelectedIndexChanged);
			// 
			// button_refresh
			// 
			this->button_refresh->BackColor = System::Drawing::SystemColors::Highlight;
			this->button_refresh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_refresh->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->button_refresh->Location = System::Drawing::Point(444, 26);
			this->button_refresh->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button_refresh->Name = L"button_refresh";
			this->button_refresh->Size = System::Drawing::Size(140, 60);
			this->button_refresh->TabIndex = 15;
			this->button_refresh->Text = L"Refresh";
			this->button_refresh->UseVisualStyleBackColor = false;
			this->button_refresh->Click += gcnew System::EventHandler(this, &Form_AnalyzeStock::button_refresh_Click);
			// 
			// label_peakValleyMargin
			// 
			this->label_peakValleyMargin->AutoSize = true;
			this->label_peakValleyMargin->Location = System::Drawing::Point(452, 106);
			this->label_peakValleyMargin->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label_peakValleyMargin->Name = L"label_peakValleyMargin";
			this->label_peakValleyMargin->Size = System::Drawing::Size(160, 20);
			this->label_peakValleyMargin->TabIndex = 14;
			this->label_peakValleyMargin->Text = L"Peak/Valley Margin: 1";
			// 
			// trackBar_peakValleyMargin
			// 
			this->trackBar_peakValleyMargin->Location = System::Drawing::Point(444, 142);
			this->trackBar_peakValleyMargin->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->trackBar_peakValleyMargin->Maximum = 4;
			this->trackBar_peakValleyMargin->Minimum = 1;
			this->trackBar_peakValleyMargin->Name = L"trackBar_peakValleyMargin";
			this->trackBar_peakValleyMargin->Size = System::Drawing::Size(212, 69);
			this->trackBar_peakValleyMargin->TabIndex = 13;
			this->trackBar_peakValleyMargin->Value = 1;
			this->trackBar_peakValleyMargin->ValueChanged += gcnew System::EventHandler(this, &Form_AnalyzeStock::trackBar_peakValleyMargin_ValueChanged);
			// 
			// label_confirmationsCount
			// 
			this->label_confirmationsCount->AutoSize = true;
			this->label_confirmationsCount->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label_confirmationsCount->Location = System::Drawing::Point(1284, 169);
			this->label_confirmationsCount->Name = L"label_confirmationsCount";
			this->label_confirmationsCount->Size = System::Drawing::Size(270, 25);
			this->label_confirmationsCount->TabIndex = 20;
			this->label_confirmationsCount->Text = L"Number of confirmations: 0";
			// 
			// button_minus
			// 
			this->button_minus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->button_minus->Location = System::Drawing::Point(1516, 89);
			this->button_minus->Name = L"button_minus";
			this->button_minus->Size = System::Drawing::Size(51, 52);
			this->button_minus->TabIndex = 23;
			this->button_minus->Text = L"-";
			this->button_minus->UseVisualStyleBackColor = true;
			this->button_minus->Click += gcnew System::EventHandler(this, &Form_AnalyzeStock::button_minus_Click);
			// 
			// button_plus
			// 
			this->button_plus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->button_plus->Location = System::Drawing::Point(1308, 89);
			this->button_plus->Name = L"button_plus";
			this->button_plus->Size = System::Drawing::Size(51, 52);
			this->button_plus->TabIndex = 22;
			this->button_plus->Text = L"+";
			this->button_plus->UseVisualStyleBackColor = true;
			this->button_plus->Click += gcnew System::EventHandler(this, &Form_AnalyzeStock::button_plus_Click);
			// 
			// button_simulate
			// 
			this->button_simulate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->button_simulate->Location = System::Drawing::Point(1377, 89);
			this->button_simulate->Name = L"button_simulate";
			this->button_simulate->Size = System::Drawing::Size(120, 52);
			this->button_simulate->TabIndex = 21;
			this->button_simulate->Text = L"Start";
			this->button_simulate->UseVisualStyleBackColor = true;
			this->button_simulate->Click += gcnew System::EventHandler(this, &Form_AnalyzeStock::button_simulate_Click);
			// 
			// timer_simulate
			// 
			this->timer_simulate->Interval = 1000;
			this->timer_simulate->Tick += gcnew System::EventHandler(this, &Form_AnalyzeStock::timer_simulate_Tick);
			// 
			// label_steps
			// 
			this->label_steps->AutoSize = true;
			this->label_steps->Location = System::Drawing::Point(1002, 99);
			this->label_steps->Name = L"label_steps";
			this->label_steps->Size = System::Drawing::Size(155, 20);
			this->label_steps->TabIndex = 27;
			this->label_steps->Text = L"Number of Steps: 30";
			// 
			// trackBar_steps
			// 
			this->trackBar_steps->Location = System::Drawing::Point(990, 128);
			this->trackBar_steps->Maximum = 100;
			this->trackBar_steps->Minimum = 2;
			this->trackBar_steps->Name = L"trackBar_steps";
			this->trackBar_steps->Size = System::Drawing::Size(242, 69);
			this->trackBar_steps->TabIndex = 26;
			this->trackBar_steps->TickFrequency = 2;
			this->trackBar_steps->Value = 30;
			this->trackBar_steps->Scroll += gcnew System::EventHandler(this, &Form_AnalyzeStock::trackBar_steps_Scroll);
			// 
			// label_range
			// 
			this->label_range->AutoSize = true;
			this->label_range->Location = System::Drawing::Point(998, 12);
			this->label_range->Name = L"label_range";
			this->label_range->Size = System::Drawing::Size(160, 20);
			this->label_range->TabIndex = 25;
			this->label_range->Text = L"Percent of Range: 20";
			// 
			// trackBar_range
			// 
			this->trackBar_range->Location = System::Drawing::Point(990, 43);
			this->trackBar_range->Maximum = 100;
			this->trackBar_range->Minimum = 1;
			this->trackBar_range->Name = L"trackBar_range";
			this->trackBar_range->Size = System::Drawing::Size(242, 69);
			this->trackBar_range->TabIndex = 24;
			this->trackBar_range->Value = 20;
			this->trackBar_range->Scroll += gcnew System::EventHandler(this, &Form_AnalyzeStock::trackBar_range_Scroll);
			// 
			// Form_AnalyzeStock
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1606, 986);
			this->Controls->Add(this->label_steps);
			this->Controls->Add(this->trackBar_steps);
			this->Controls->Add(this->label_range);
			this->Controls->Add(this->trackBar_range);
			this->Controls->Add(this->button_minus);
			this->Controls->Add(this->button_plus);
			this->Controls->Add(this->button_simulate);
			this->Controls->Add(this->label_confirmationsCount);
			this->Controls->Add(this->comboBox_downWave);
			this->Controls->Add(this->label_downWave);
			this->Controls->Add(this->label_upWave);
			this->Controls->Add(this->comboBox_upWave);
			this->Controls->Add(this->button_refresh);
			this->Controls->Add(this->label_peakValleyMargin);
			this->Controls->Add(this->trackBar_peakValleyMargin);
			this->Controls->Add(this->chart_stockData);
			this->Controls->Add(this->label_endDate);
			this->Controls->Add(this->label_startDate);
			this->Controls->Add(this->dateTimePicker_endDate);
			this->Controls->Add(this->dateTimePicker_startDate);
			this->Controls->Add(this->button_loadTicker);
			this->Name = L"Form_AnalyzeStock";
			this->StartPosition = System::Windows::Forms::FormStartPosition::WindowsDefaultBounds;
			this->Text = L"Form_AnalyzeStock";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_stockData))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_peakValleyMargin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_steps))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_range))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
};
}
