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
	/// with specified ticker file name, start date, and end date  
	/// </summary>  
	/// <param name="tickerFileName">The ticker filename</param>  
	/// <param name="start">The start date for candlesticks filtering</param>  
	/// <param name="end">The end date for candlesticks filtering</param>  
	public: Form_AnalyzeStock(String^ tickerFileName, DateTime start, DateTime end) {
		// Initialize the form components and data members  
		intializeForm();

		// Set the start date picker value to the specified start date  
		dateTimePicker_startDate->Value = start;
		// Set the end date picker value to the specified end date  
		dateTimePicker_endDate->Value = end;

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


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Developer Code
	// Declare a list to store Candlestick objects
	private:List<Candlestick^>^ candlesticks;
	// Declare a list to store filtered candlestick objects
	private:List<Candlestick^>^ filteredCandlesticks;
	// Declare a list to store the extreme values (peaks and valleys)
	private: List<Extreme^>^ extremes;
	// Declare a list to store the up waves
	private: List<Wave^>^ upWaves;
	// Declare a list to store the down waves
	private: List<Wave^>^ downWaves;

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
	/// Function to add wave annotation to the chart  
	/// </summary>  
	/// <param name="wave">The selected wave object</param>  
	/// <param name="isUp">Boolean value indicating if the wave is an up wave</param>  
	private: void addWaveAnnotation(Wave^ wave, bool isUp);
#pragma endregion

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_stockData))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_peakValleyMargin))->BeginInit();
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
			this->openFileDialog_loadTicker->FileName = L"AAL-Day";
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
			this->label_endDate->Size = System::Drawing::Size(58, 15);
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
			this->label_startDate->Size = System::Drawing::Size(61, 15);
			this->label_startDate->TabIndex = 7;
			this->label_startDate->Text = L"Start Date";
			// 
			// dateTimePicker_endDate
			// 
			this->dateTimePicker_endDate->Location = System::Drawing::Point(144, 169);
			this->dateTimePicker_endDate->Name = L"dateTimePicker_endDate";
			this->dateTimePicker_endDate->Size = System::Drawing::Size(272, 26);
			this->dateTimePicker_endDate->TabIndex = 6;
			// 
			// dateTimePicker_startDate
			// 
			this->dateTimePicker_startDate->Location = System::Drawing::Point(144, 118);
			this->dateTimePicker_startDate->Name = L"dateTimePicker_startDate";
			this->dateTimePicker_startDate->Size = System::Drawing::Size(272, 26);
			this->dateTimePicker_startDate->TabIndex = 5;
			this->dateTimePicker_startDate->Value = System::DateTime(2023, 1, 1, 0, 0, 0, 0);
			// 
			// chart_stockData
			// 
			chartArea3->AlignWithChartArea = L"ChartArea_Volume";
			chartArea3->Name = L"ChartArea_OHLC";
			chartArea4->Name = L"ChartArea_Volume";
			this->chart_stockData->ChartAreas->Add(chartArea3);
			this->chart_stockData->ChartAreas->Add(chartArea4);
			this->chart_stockData->Location = System::Drawing::Point(44, 292);
			this->chart_stockData->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->chart_stockData->Name = L"chart_stockData";
			series3->ChartArea = L"ChartArea_OHLC";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Candlestick;
			series3->CustomProperties = L"PriceDownColor=Red, PriceUpColor=Green";
			series3->IsXValueIndexed = true;
			series3->Name = L"Series_OHLC";
			series3->XValueMember = L"Date";
			series3->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Date;
			series3->YValueMembers = L"high,low,open,close";
			series3->YValuesPerPoint = 4;
			series4->ChartArea = L"ChartArea_Volume";
			series4->IsXValueIndexed = true;
			series4->Name = L"Series_Volume";
			series4->XValueMember = L"Date";
			series4->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Date;
			series4->YValueMembers = L"Volume";
			series4->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::UInt64;
			this->chart_stockData->Series->Add(series3);
			this->chart_stockData->Series->Add(series4);
			this->chart_stockData->Size = System::Drawing::Size(1482, 400);
			this->chart_stockData->TabIndex = 10;
			this->chart_stockData->Text = L"chart1";
			// 
			// comboBox_downWave
			// 
			this->comboBox_downWave->FormattingEnabled = true;
			this->comboBox_downWave->Location = System::Drawing::Point(864, 142);
			this->comboBox_downWave->Name = L"comboBox_downWave";
			this->comboBox_downWave->Size = System::Drawing::Size(239, 28);
			this->comboBox_downWave->TabIndex = 19;
			this->comboBox_downWave->SelectedIndexChanged += gcnew System::EventHandler(this, &Form_AnalyzeStock::comboBox_downWave_SelectedIndexChanged);
			// 
			// label_downWave
			// 
			this->label_downWave->AutoSize = true;
			this->label_downWave->Location = System::Drawing::Point(860, 106);
			this->label_downWave->Name = L"label_downWave";
			this->label_downWave->Size = System::Drawing::Size(103, 20);
			this->label_downWave->TabIndex = 18;
			this->label_downWave->Text = L"DOWN Wave";
			// 
			// label_upWave
			// 
			this->label_upWave->AutoSize = true;
			this->label_upWave->Location = System::Drawing::Point(860, 26);
			this->label_upWave->Name = L"label_upWave";
			this->label_upWave->Size = System::Drawing::Size(75, 20);
			this->label_upWave->TabIndex = 17;
			this->label_upWave->Text = L"UP Wave";
			// 
			// comboBox_upWave
			// 
			this->comboBox_upWave->FormattingEnabled = true;
			this->comboBox_upWave->Location = System::Drawing::Point(864, 58);
			this->comboBox_upWave->Name = L"comboBox_upWave";
			this->comboBox_upWave->Size = System::Drawing::Size(239, 28);
			this->comboBox_upWave->TabIndex = 16;
			this->comboBox_upWave->SelectedIndexChanged += gcnew System::EventHandler(this, &Form_AnalyzeStock::comboBox_upWave_SelectedIndexChanged);
			// 
			// button_refresh
			// 
			this->button_refresh->BackColor = System::Drawing::SystemColors::Highlight;
			this->button_refresh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_refresh->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->button_refresh->Location = System::Drawing::Point(598, 26);
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
			this->label_peakValleyMargin->Location = System::Drawing::Point(606, 106);
			this->label_peakValleyMargin->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label_peakValleyMargin->Name = L"label_peakValleyMargin";
			this->label_peakValleyMargin->Size = System::Drawing::Size(160, 20);
			this->label_peakValleyMargin->TabIndex = 14;
			this->label_peakValleyMargin->Text = L"Peak/Valley Margin: 4";
			// 
			// trackBar_peakValleyMargin
			// 
			this->trackBar_peakValleyMargin->Location = System::Drawing::Point(598, 142);
			this->trackBar_peakValleyMargin->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->trackBar_peakValleyMargin->Maximum = 4;
			this->trackBar_peakValleyMargin->Minimum = 1;
			this->trackBar_peakValleyMargin->Name = L"trackBar_peakValleyMargin";
			this->trackBar_peakValleyMargin->Size = System::Drawing::Size(212, 45);
			this->trackBar_peakValleyMargin->TabIndex = 13;
			this->trackBar_peakValleyMargin->Value = 4;
			this->trackBar_peakValleyMargin->ValueChanged += gcnew System::EventHandler(this, &Form_AnalyzeStock::trackBar_peakValleyMargin_ValueChanged);
			// 
			// Form_AnalyzeStock
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1544, 731);
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
			this->Text = L"Form_AnalyzeStock";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_stockData))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_peakValleyMargin))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
};
}
