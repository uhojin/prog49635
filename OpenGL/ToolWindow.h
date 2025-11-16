#pragma once

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:
		// Render modes
		static int CurrentMode = 0; // 0 = Move Light, 1 = Color By Position, 2 = Move Cubes To Sphere

		// Specular controls
		static int SpecularStrength = 4; // 1-128
		static int SpecularColorR = 100; // 0-300
		static int SpecularColorG = 100; // 0-300
		static int SpecularColorB = 100; // 0-300

		// Flags for button presses
		static bool ResetLightPosition = false;
		static bool ResetTeapotPosition = false;

		ToolWindow(void)
		{
			InitializeComponent();
			CurrentMode = 0; // Move Light by default
			SpecularStrength = 4;
			SpecularColorR = 100;
			SpecularColorG = 100;
			SpecularColorB = 100;
			ResetLightPosition = false;
			ResetTeapotPosition = false;

			// Set default radio button
			radioButtonMoveLight->Checked = true;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		// Radio Buttons
		System::Windows::Forms::RadioButton^ radioButtonMoveLight;
		System::Windows::Forms::RadioButton^ radioButtonColorByPosition;
		System::Windows::Forms::RadioButton^ radioButtonMoveCubes;

		// Buttons
		System::Windows::Forms::Button^ buttonResetLight;
		System::Windows::Forms::Button^ buttonResetTeapot;

		// Trackbars
		System::Windows::Forms::TrackBar^ trackBarSpecularStrength;
		System::Windows::Forms::TrackBar^ trackBarSpecularR;
		System::Windows::Forms::TrackBar^ trackBarSpecularG;
		System::Windows::Forms::TrackBar^ trackBarSpecularB;

		// Labels
		System::Windows::Forms::Label^ labelSpecularStrength;
		System::Windows::Forms::Label^ labelSpecularStrengthValue;
		System::Windows::Forms::Label^ labelSpecularR;
		System::Windows::Forms::Label^ labelSpecularG;
		System::Windows::Forms::Label^ labelSpecularB;
		System::Windows::Forms::Label^ labelSpecularRValue;
		System::Windows::Forms::Label^ labelSpecularGValue;
		System::Windows::Forms::Label^ labelSpecularBValue;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->radioButtonMoveLight = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonColorByPosition = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonMoveCubes = (gcnew System::Windows::Forms::RadioButton());
			this->buttonResetLight = (gcnew System::Windows::Forms::Button());
			this->buttonResetTeapot = (gcnew System::Windows::Forms::Button());
			this->trackBarSpecularStrength = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarSpecularR = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarSpecularG = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarSpecularB = (gcnew System::Windows::Forms::TrackBar());
			this->labelSpecularStrength = (gcnew System::Windows::Forms::Label());
			this->labelSpecularStrengthValue = (gcnew System::Windows::Forms::Label());
			this->labelSpecularR = (gcnew System::Windows::Forms::Label());
			this->labelSpecularG = (gcnew System::Windows::Forms::Label());
			this->labelSpecularB = (gcnew System::Windows::Forms::Label());
			this->labelSpecularRValue = (gcnew System::Windows::Forms::Label());
			this->labelSpecularGValue = (gcnew System::Windows::Forms::Label());
			this->labelSpecularBValue = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularG))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularB))->BeginInit();
			this->SuspendLayout();
			// 
			// radioButtonMoveLight
			// 
			this->radioButtonMoveLight->AutoSize = true;
			this->radioButtonMoveLight->Checked = true;
			this->radioButtonMoveLight->Location = System::Drawing::Point(13, 13);
			this->radioButtonMoveLight->Name = L"radioButtonMoveLight";
			this->radioButtonMoveLight->Size = System::Drawing::Size(78, 17);
			this->radioButtonMoveLight->TabIndex = 0;
			this->radioButtonMoveLight->TabStop = true;
			this->radioButtonMoveLight->Text = L"Move Light";
			this->radioButtonMoveLight->UseVisualStyleBackColor = true;
			this->radioButtonMoveLight->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButtonMoveLight_CheckedChanged);
			// 
			// radioButtonColorByPosition
			// 
			this->radioButtonColorByPosition->AutoSize = true;
			this->radioButtonColorByPosition->Location = System::Drawing::Point(12, 257);
			this->radioButtonColorByPosition->Name = L"radioButtonColorByPosition";
			this->radioButtonColorByPosition->Size = System::Drawing::Size(104, 17);
			this->radioButtonColorByPosition->TabIndex = 1;
			this->radioButtonColorByPosition->Text = L"Color By Position";
			this->radioButtonColorByPosition->UseVisualStyleBackColor = true;
			this->radioButtonColorByPosition->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButtonColorByPosition_CheckedChanged);
			// 
			// radioButtonMoveCubes
			// 
			this->radioButtonMoveCubes->AutoSize = true;
			this->radioButtonMoveCubes->Location = System::Drawing::Point(12, 309);
			this->radioButtonMoveCubes->Name = L"radioButtonMoveCubes";
			this->radioButtonMoveCubes->Size = System::Drawing::Size(138, 17);
			this->radioButtonMoveCubes->TabIndex = 2;
			this->radioButtonMoveCubes->Text = L"Move Cubes To Sphere";
			this->radioButtonMoveCubes->UseVisualStyleBackColor = true;
			this->radioButtonMoveCubes->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButtonMoveCubes_CheckedChanged);
			// 
			// buttonResetLight
			// 
			this->buttonResetLight->Location = System::Drawing::Point(32, 36);
			this->buttonResetLight->Name = L"buttonResetLight";
			this->buttonResetLight->Size = System::Drawing::Size(120, 23);
			this->buttonResetLight->TabIndex = 3;
			this->buttonResetLight->Text = L"Reset Light Position";
			this->buttonResetLight->UseVisualStyleBackColor = true;
			this->buttonResetLight->Click += gcnew System::EventHandler(this, &ToolWindow::buttonResetLight_Click);
			// 
			// buttonResetTeapot
			// 
			this->buttonResetTeapot->Location = System::Drawing::Point(30, 280);
			this->buttonResetTeapot->Name = L"buttonResetTeapot";
			this->buttonResetTeapot->Size = System::Drawing::Size(130, 23);
			this->buttonResetTeapot->TabIndex = 4;
			this->buttonResetTeapot->Text = L"Reset Teapot Position";
			this->buttonResetTeapot->UseVisualStyleBackColor = true;
			this->buttonResetTeapot->Click += gcnew System::EventHandler(this, &ToolWindow::buttonResetTeapot_Click);
			// 
			// trackBarSpecularStrength
			// 
			this->trackBarSpecularStrength->Location = System::Drawing::Point(140, 65);
			this->trackBarSpecularStrength->Maximum = 128;
			this->trackBarSpecularStrength->Minimum = 1;
			this->trackBarSpecularStrength->Name = L"trackBarSpecularStrength";
			this->trackBarSpecularStrength->Size = System::Drawing::Size(200, 45);
			this->trackBarSpecularStrength->TabIndex = 6;
			this->trackBarSpecularStrength->Value = 4;
			this->trackBarSpecularStrength->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarSpecularStrength_Scroll);
			// 
			// trackBarSpecularR
			// 
			this->trackBarSpecularR->Location = System::Drawing::Point(140, 100);
			this->trackBarSpecularR->Maximum = 300;
			this->trackBarSpecularR->Name = L"trackBarSpecularR";
			this->trackBarSpecularR->Size = System::Drawing::Size(150, 45);
			this->trackBarSpecularR->TabIndex = 8;
			this->trackBarSpecularR->Value = 100;
			this->trackBarSpecularR->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarSpecular_Scroll);
			// 
			// trackBarSpecularG
			// 
			this->trackBarSpecularG->Location = System::Drawing::Point(140, 149);
			this->trackBarSpecularG->Maximum = 300;
			this->trackBarSpecularG->Name = L"trackBarSpecularG";
			this->trackBarSpecularG->Size = System::Drawing::Size(150, 45);
			this->trackBarSpecularG->TabIndex = 11;
			this->trackBarSpecularG->Value = 100;
			this->trackBarSpecularG->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarSpecular_Scroll);
			// 
			// trackBarSpecularB
			// 
			this->trackBarSpecularB->Location = System::Drawing::Point(140, 200);
			this->trackBarSpecularB->Maximum = 300;
			this->trackBarSpecularB->Name = L"trackBarSpecularB";
			this->trackBarSpecularB->Size = System::Drawing::Size(150, 45);
			this->trackBarSpecularB->TabIndex = 14;
			this->trackBarSpecularB->Value = 100;
			this->trackBarSpecularB->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarSpecular_Scroll);
			// 
			// labelSpecularStrength
			// 
			this->labelSpecularStrength->AutoSize = true;
			this->labelSpecularStrength->Location = System::Drawing::Point(29, 65);
			this->labelSpecularStrength->Name = L"labelSpecularStrength";
			this->labelSpecularStrength->Size = System::Drawing::Size(92, 13);
			this->labelSpecularStrength->TabIndex = 5;
			this->labelSpecularStrength->Text = L"Specular Strength";
			// 
			// labelSpecularStrengthValue
			// 
			this->labelSpecularStrengthValue->AutoSize = true;
			this->labelSpecularStrengthValue->Location = System::Drawing::Point(346, 65);
			this->labelSpecularStrengthValue->Name = L"labelSpecularStrengthValue";
			this->labelSpecularStrengthValue->Size = System::Drawing::Size(13, 13);
			this->labelSpecularStrengthValue->TabIndex = 16;
			this->labelSpecularStrengthValue->Text = L"4";
			// 
			// labelSpecularR
			// 
			this->labelSpecularR->AutoSize = true;
			this->labelSpecularR->Location = System::Drawing::Point(29, 100);
			this->labelSpecularR->Name = L"labelSpecularR";
			this->labelSpecularR->Size = System::Drawing::Size(87, 13);
			this->labelSpecularR->TabIndex = 7;
			this->labelSpecularR->Text = L"Specular Color R";
			// 
			// labelSpecularG
			// 
			this->labelSpecularG->AutoSize = true;
			this->labelSpecularG->Location = System::Drawing::Point(101, 149);
			this->labelSpecularG->Name = L"labelSpecularG";
			this->labelSpecularG->Size = System::Drawing::Size(15, 13);
			this->labelSpecularG->TabIndex = 10;
			this->labelSpecularG->Text = L"G";
			// 
			// labelSpecularB
			// 
			this->labelSpecularB->AutoSize = true;
			this->labelSpecularB->Location = System::Drawing::Point(101, 200);
			this->labelSpecularB->Name = L"labelSpecularB";
			this->labelSpecularB->Size = System::Drawing::Size(14, 13);
			this->labelSpecularB->TabIndex = 13;
			this->labelSpecularB->Text = L"B";
			// 
			// labelSpecularRValue
			// 
			this->labelSpecularRValue->AutoSize = true;
			this->labelSpecularRValue->Location = System::Drawing::Point(295, 100);
			this->labelSpecularRValue->Name = L"labelSpecularRValue";
			this->labelSpecularRValue->Size = System::Drawing::Size(28, 13);
			this->labelSpecularRValue->TabIndex = 9;
			this->labelSpecularRValue->Text = L"1.00";
			// 
			// labelSpecularGValue
			// 
			this->labelSpecularGValue->AutoSize = true;
			this->labelSpecularGValue->Location = System::Drawing::Point(295, 149);
			this->labelSpecularGValue->Name = L"labelSpecularGValue";
			this->labelSpecularGValue->Size = System::Drawing::Size(28, 13);
			this->labelSpecularGValue->TabIndex = 12;
			this->labelSpecularGValue->Text = L"1.00";
			this->labelSpecularGValue->Click += gcnew System::EventHandler(this, &ToolWindow::labelSpecularGValue_Click);
			// 
			// labelSpecularBValue
			// 
			this->labelSpecularBValue->AutoSize = true;
			this->labelSpecularBValue->Location = System::Drawing::Point(295, 200);
			this->labelSpecularBValue->Name = L"labelSpecularBValue";
			this->labelSpecularBValue->Size = System::Drawing::Size(28, 13);
			this->labelSpecularBValue->TabIndex = 15;
			this->labelSpecularBValue->Text = L"1.00";
			this->labelSpecularBValue->Click += gcnew System::EventHandler(this, &ToolWindow::labelSpecularBValue_Click);
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(380, 338);
			this->Controls->Add(this->labelSpecularBValue);
			this->Controls->Add(this->trackBarSpecularB);
			this->Controls->Add(this->labelSpecularB);
			this->Controls->Add(this->labelSpecularGValue);
			this->Controls->Add(this->trackBarSpecularG);
			this->Controls->Add(this->labelSpecularG);
			this->Controls->Add(this->labelSpecularRValue);
			this->Controls->Add(this->trackBarSpecularR);
			this->Controls->Add(this->labelSpecularR);
			this->Controls->Add(this->labelSpecularStrengthValue);
			this->Controls->Add(this->trackBarSpecularStrength);
			this->Controls->Add(this->labelSpecularStrength);
			this->Controls->Add(this->buttonResetTeapot);
			this->Controls->Add(this->buttonResetLight);
			this->Controls->Add(this->radioButtonMoveCubes);
			this->Controls->Add(this->radioButtonColorByPosition);
			this->Controls->Add(this->radioButtonMoveLight);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularStrength))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularG))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularB))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void radioButtonMoveLight_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (radioButtonMoveLight->Checked) {
			CurrentMode = 0;
		}
	}

	private: System::Void radioButtonColorByPosition_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (radioButtonColorByPosition->Checked) {
			CurrentMode = 1;
		}
	}

	private: System::Void radioButtonMoveCubes_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (radioButtonMoveCubes->Checked) {
			CurrentMode = 2;
		}
	}

	private: System::Void buttonResetLight_Click(System::Object^ sender, System::EventArgs^ e) {
		ResetLightPosition = true;
	}

	private: System::Void buttonResetTeapot_Click(System::Object^ sender, System::EventArgs^ e) {
		ResetTeapotPosition = true;
	}

	private: System::Void trackBarSpecularStrength_Scroll(System::Object^ sender, System::EventArgs^ e) {
		SpecularStrength = trackBarSpecularStrength->Value;
		labelSpecularStrengthValue->Text = SpecularStrength.ToString();
	}

	private: System::Void trackBarSpecular_Scroll(System::Object^ sender, System::EventArgs^ e) {
		SpecularColorR = trackBarSpecularR->Value;
		SpecularColorG = trackBarSpecularG->Value;
		SpecularColorB = trackBarSpecularB->Value;

		// Update labels (convert 0-300 to 0.00-3.00)
		labelSpecularRValue->Text = String::Format("{0:F2}", SpecularColorR / 100.0f);
		labelSpecularGValue->Text = String::Format("{0:F2}", SpecularColorG / 100.0f);
		labelSpecularBValue->Text = String::Format("{0:F2}", SpecularColorB / 100.0f);
	}
private: System::Void labelSpecularGValue_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void labelSpecularBValue_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
