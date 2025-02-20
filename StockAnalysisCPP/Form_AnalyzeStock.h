#pragma once
#include "Candlestick.h"

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
			// Initialize the form components
			InitializeComponent();
			// Initialize the candlesticks list
			candlesticks = gcnew List<Candlestick^>();
			// Initialize the filteredCandlesticks list
			filteredCandlesticks = gcnew List<Candlestick^>();
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
	private: System::Windows::Forms::DataGridView^ dataGridView_stockData;
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

	/// <summary>
	/// Function to handle the click event of the button_loadTicker
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="e"></param>
	private: System::Void button_loadTicker_Click(System::Object^ sender, System::EventArgs^ e);

	/// <summary>
	/// Function to handle the event after user selects a ticker file in the OpenFileDialog
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="e"></param>
	private: System::Void openFileDialog_loadTicker_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);

	/// <summary>
	/// Function to read candlestick data from the selected file and store it in a list
	/// </summary>
	private: System::Void readCandlesticksFromFile();

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
	/// Function to display the stock data (OHLCV) in a DataGridView
	/// </summary>
	private: System::Void displayDataGridView();

	/// <summary>
	/// Function to handle the event when the user selects a date in the start date picker
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="e"></param>
	private: System::Void dateTimePicker_startDate_ValueChanged(System::Object^ sender, System::EventArgs^ e);

	/// <summary>
	/// Function to handle the event when the user selects a date in the end date picker
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="e"></param>
	private: System::Void dateTimePicker_endDate_ValueChanged(System::Object^ sender, System::EventArgs^ e);
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
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->button_loadTicker = (gcnew System::Windows::Forms::Button());
			this->openFileDialog_loadTicker = (gcnew System::Windows::Forms::OpenFileDialog());
			this->label_endDate = (gcnew System::Windows::Forms::Label());
			this->label_startDate = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker_endDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePicker_startDate = (gcnew System::Windows::Forms::DateTimePicker());
			this->dataGridView_stockData = (gcnew System::Windows::Forms::DataGridView());
			this->chart_stockData = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_stockData))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_stockData))->BeginInit();
			this->SuspendLayout();
			// 
			// button_loadTicker
			// 
			this->button_loadTicker->BackColor = System::Drawing::Color::MediumBlue;
			this->button_loadTicker->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_loadTicker->ForeColor = System::Drawing::Color::White;
			this->button_loadTicker->Location = System::Drawing::Point(34, 14);
			this->button_loadTicker->Margin = System::Windows::Forms::Padding(2);
			this->button_loadTicker->Name = L"button_loadTicker";
			this->button_loadTicker->Size = System::Drawing::Size(135, 45);
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
			this->openFileDialog_loadTicker->ShowReadOnly = true;
			this->openFileDialog_loadTicker->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form_AnalyzeStock::openFileDialog_loadTicker_FileOk);
			// 
			// label_endDate
			// 
			this->label_endDate->AutoSize = true;
			this->label_endDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_endDate->ForeColor = System::Drawing::Color::Black;
			this->label_endDate->Location = System::Drawing::Point(31, 111);
			this->label_endDate->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
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
			this->label_startDate->Location = System::Drawing::Point(31, 79);
			this->label_startDate->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_startDate->Name = L"label_startDate";
			this->label_startDate->Size = System::Drawing::Size(61, 15);
			this->label_startDate->TabIndex = 7;
			this->label_startDate->Text = L"Start Date";
			// 
			// dateTimePicker_endDate
			// 
			this->dateTimePicker_endDate->Location = System::Drawing::Point(96, 110);
			this->dateTimePicker_endDate->Margin = System::Windows::Forms::Padding(2);
			this->dateTimePicker_endDate->Name = L"dateTimePicker_endDate";
			this->dateTimePicker_endDate->Size = System::Drawing::Size(183, 20);
			this->dateTimePicker_endDate->TabIndex = 6;
			this->dateTimePicker_endDate->ValueChanged += gcnew System::EventHandler(this, &Form_AnalyzeStock::dateTimePicker_endDate_ValueChanged);
			// 
			// dateTimePicker_startDate
			// 
			this->dateTimePicker_startDate->Location = System::Drawing::Point(96, 77);
			this->dateTimePicker_startDate->Margin = System::Windows::Forms::Padding(2);
			this->dateTimePicker_startDate->Name = L"dateTimePicker_startDate";
			this->dateTimePicker_startDate->Size = System::Drawing::Size(183, 20);
			this->dateTimePicker_startDate->TabIndex = 5;
			this->dateTimePicker_startDate->Value = System::DateTime(2024, 1, 1, 0, 0, 0, 0);
			this->dateTimePicker_startDate->ValueChanged += gcnew System::EventHandler(this, &Form_AnalyzeStock::dateTimePicker_startDate_ValueChanged);
			// 
			// dataGridView_stockData
			// 
			this->dataGridView_stockData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView_stockData->Location = System::Drawing::Point(343, 14);
			this->dataGridView_stockData->Margin = System::Windows::Forms::Padding(2);
			this->dataGridView_stockData->Name = L"dataGridView_stockData";
			this->dataGridView_stockData->RowHeadersWidth = 62;
			this->dataGridView_stockData->RowTemplate->Height = 28;
			this->dataGridView_stockData->Size = System::Drawing::Size(675, 150);
			this->dataGridView_stockData->TabIndex = 9;
			// 
			// chart_stockData
			// 
			chartArea3->Name = L"ChartArea_OHLC";
			chartArea4->Name = L"ChartArea_Volume";
			this->chart_stockData->ChartAreas->Add(chartArea3);
			this->chart_stockData->ChartAreas->Add(chartArea4);
			legend2->Name = L"Legend1";
			this->chart_stockData->Legends->Add(legend2);
			this->chart_stockData->Location = System::Drawing::Point(29, 190);
			this->chart_stockData->Name = L"chart_stockData";
			series3->ChartArea = L"ChartArea_OHLC";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Candlestick;
			series3->CustomProperties = L"PriceDownColor=Red, PriceUpColor=Green";
			series3->Legend = L"Legend1";
			series3->Name = L"Series_OHLC";
			series3->XValueMember = L"Date";
			series3->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Date;
			series3->YValueMembers = L"High,Low,Open,Close";
			series3->YValuesPerPoint = 4;
			series3->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			series4->ChartArea = L"ChartArea_Volume";
			series4->Legend = L"Legend1";
			series4->Name = L"Series_Volume";
			series4->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Date;
			series4->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::UInt64;
			this->chart_stockData->Series->Add(series3);
			this->chart_stockData->Series->Add(series4);
			this->chart_stockData->Size = System::Drawing::Size(988, 260);
			this->chart_stockData->TabIndex = 10;
			this->chart_stockData->Text = L"chart1";
			// 
			// Form_AnalyzeStock
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1029, 475);
			this->Controls->Add(this->chart_stockData);
			this->Controls->Add(this->dataGridView_stockData);
			this->Controls->Add(this->label_endDate);
			this->Controls->Add(this->label_startDate);
			this->Controls->Add(this->dateTimePicker_endDate);
			this->Controls->Add(this->dateTimePicker_startDate);
			this->Controls->Add(this->button_loadTicker);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"Form_AnalyzeStock";
			this->Text = L"Form_AnalyzeStock";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_stockData))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_stockData))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

};
}
