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
		static int CurrentMode = 0; // 0 = Move Light, 1 = Transform, 2 = Water Scene, 3 = Space Scene

		// Mode 0: Move Light - Specular controls
		static int SpecularStrength = 4; // 1-128
		static int SpecularColorR = 100; // 0-300
		static int SpecularColorG = 100; // 0-300
		static int SpecularColorB = 100; // 0-300
		static bool ResetLightPosition = false;

		// Mode 1: Transform
		static bool ResetTransform = false;
		static bool EnableTranslate = false;
		static bool EnableRotate = false;
		static bool EnableScale = false;

		// Mode 2: Water Scene
		static int WaterFrequency = 200;     // 0-400 (display as 0.00-4.00, divide by 100)
		static int WaterAmplitude = 50;      // 0-100 (display as 0.00-1.00, divide by 100)
		static bool WireframeRender = false;
		static bool TintBlue = false;

		ToolWindow(void)
		{
			InitializeComponent();
			CurrentMode = 0; // Move Light by default

			// Mode 0: Move Light
			SpecularStrength = 4;
			SpecularColorR = 100;
			SpecularColorG = 100;
			SpecularColorB = 100;
			ResetLightPosition = false;

			// Mode 1: Transform
			ResetTransform = false;
			EnableTranslate = false;
			EnableRotate = false;
			EnableScale = false;

			// Mode 2: Water Scene
			WaterFrequency = 200;      // Default 2.00
			WaterAmplitude = 50;       // Default 0.50
			WireframeRender = false;
			TintBlue = false;

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
		System::Windows::Forms::RadioButton^ radioButtonTransform;
		System::Windows::Forms::RadioButton^ radioButtonWaterScene;
		System::Windows::Forms::RadioButton^ radioButtonSpaceScene;

		// Mode 0: Move Light Controls
		System::Windows::Forms::Button^ buttonResetLight;
		System::Windows::Forms::TrackBar^ trackBarSpecularStrength;
		System::Windows::Forms::TrackBar^ trackBarSpecularR;
		System::Windows::Forms::TrackBar^ trackBarSpecularG;
		System::Windows::Forms::TrackBar^ trackBarSpecularB;
		System::Windows::Forms::Label^ labelSpecularStrength;
		System::Windows::Forms::Label^ labelSpecularStrengthValue;
		System::Windows::Forms::Label^ labelSpecularR;
		System::Windows::Forms::Label^ labelSpecularG;
		System::Windows::Forms::Label^ labelSpecularB;
		System::Windows::Forms::Label^ labelSpecularRValue;
		System::Windows::Forms::Label^ labelSpecularGValue;
		System::Windows::Forms::Label^ labelSpecularBValue;

		// Mode 1: Transform Controls
		System::Windows::Forms::Button^ buttonResetTransform;
		System::Windows::Forms::CheckBox^ checkBoxTranslate;
		System::Windows::Forms::CheckBox^ checkBoxRotate;
		System::Windows::Forms::CheckBox^ checkBoxScale;

		// Mode 2: Water Scene Controls
		System::Windows::Forms::TrackBar^ trackBarWaterFrequency;
		System::Windows::Forms::TrackBar^ trackBarWaterAmplitude;
		System::Windows::Forms::Label^ labelWaterFrequency;
		System::Windows::Forms::Label^ labelWaterFrequencyValue;
		System::Windows::Forms::Label^ labelWaterAmplitude;
		System::Windows::Forms::Label^ labelWaterAmplitudeValue;
		System::Windows::Forms::CheckBox^ checkBoxWireframe;
		System::Windows::Forms::CheckBox^ checkBoxTintBlue;

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
			// Radio Buttons
			this->radioButtonMoveLight = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonTransform = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonWaterScene = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonSpaceScene = (gcnew System::Windows::Forms::RadioButton());

			// Mode 0: Move Light
			this->buttonResetLight = (gcnew System::Windows::Forms::Button());
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

			// Mode 1: Transform
			this->buttonResetTransform = (gcnew System::Windows::Forms::Button());
			this->checkBoxTranslate = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxRotate = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxScale = (gcnew System::Windows::Forms::CheckBox());

			// Mode 2: Water Scene
			this->trackBarWaterFrequency = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarWaterAmplitude = (gcnew System::Windows::Forms::TrackBar());
			this->labelWaterFrequency = (gcnew System::Windows::Forms::Label());
			this->labelWaterFrequencyValue = (gcnew System::Windows::Forms::Label());
			this->labelWaterAmplitude = (gcnew System::Windows::Forms::Label());
			this->labelWaterAmplitudeValue = (gcnew System::Windows::Forms::Label());
			this->checkBoxWireframe = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxTintBlue = (gcnew System::Windows::Forms::CheckBox());

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularG))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpecularB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarWaterFrequency))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarWaterAmplitude))->BeginInit();
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
			// radioButtonTransform
			//
			this->radioButtonTransform->AutoSize = true;
			this->radioButtonTransform->Location = System::Drawing::Point(13, 240);
			this->radioButtonTransform->Name = L"radioButtonTransform";
			this->radioButtonTransform->Size = System::Drawing::Size(78, 17);
			this->radioButtonTransform->TabIndex = 1;
			this->radioButtonTransform->Text = L"Transform";
			this->radioButtonTransform->UseVisualStyleBackColor = true;
			this->radioButtonTransform->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButtonTransform_CheckedChanged);
			//
			// radioButtonWaterScene
			//
			this->radioButtonWaterScene->AutoSize = true;
			this->radioButtonWaterScene->Location = System::Drawing::Point(13, 380);
			this->radioButtonWaterScene->Name = L"radioButtonWaterScene";
			this->radioButtonWaterScene->Size = System::Drawing::Size(90, 17);
			this->radioButtonWaterScene->TabIndex = 2;
			this->radioButtonWaterScene->Text = L"Water Scene";
			this->radioButtonWaterScene->UseVisualStyleBackColor = true;
			this->radioButtonWaterScene->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButtonWaterScene_CheckedChanged);
			//
			// radioButtonSpaceScene
			//
			this->radioButtonSpaceScene->AutoSize = true;
			this->radioButtonSpaceScene->Location = System::Drawing::Point(13, 580);
			this->radioButtonSpaceScene->Name = L"radioButtonSpaceScene";
			this->radioButtonSpaceScene->Size = System::Drawing::Size(90, 17);
			this->radioButtonSpaceScene->TabIndex = 3;
			this->radioButtonSpaceScene->Text = L"Space Scene";
			this->radioButtonSpaceScene->UseVisualStyleBackColor = true;
			this->radioButtonSpaceScene->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButtonSpaceScene_CheckedChanged);
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
			// buttonResetTransform
			//
			this->buttonResetTransform->Location = System::Drawing::Point(32, 263);
			this->buttonResetTransform->Name = L"buttonResetTransform";
			this->buttonResetTransform->Size = System::Drawing::Size(120, 23);
			this->buttonResetTransform->TabIndex = 17;
			this->buttonResetTransform->Text = L"Reset Transform";
			this->buttonResetTransform->UseVisualStyleBackColor = true;
			this->buttonResetTransform->Click += gcnew System::EventHandler(this, &ToolWindow::buttonResetTransform_Click);
			//
			// checkBoxTranslate
			//
			this->checkBoxTranslate->AutoSize = true;
			this->checkBoxTranslate->Location = System::Drawing::Point(32, 295);
			this->checkBoxTranslate->Name = L"checkBoxTranslate";
			this->checkBoxTranslate->Size = System::Drawing::Size(70, 17);
			this->checkBoxTranslate->TabIndex = 18;
			this->checkBoxTranslate->Text = L"Translate";
			this->checkBoxTranslate->UseVisualStyleBackColor = true;
			this->checkBoxTranslate->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxTranslate_CheckedChanged);
			//
			// checkBoxRotate
			//
			this->checkBoxRotate->AutoSize = true;
			this->checkBoxRotate->Checked = false;
			this->checkBoxRotate->CheckState = System::Windows::Forms::CheckState::Unchecked;
			this->checkBoxRotate->Location = System::Drawing::Point(32, 320);
			this->checkBoxRotate->Name = L"checkBoxRotate";
			this->checkBoxRotate->Size = System::Drawing::Size(60, 17);
			this->checkBoxRotate->TabIndex = 19;
			this->checkBoxRotate->Text = L"Rotate";
			this->checkBoxRotate->UseVisualStyleBackColor = true;
			this->checkBoxRotate->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxRotate_CheckedChanged);
			//
			// checkBoxScale
			//
			this->checkBoxScale->AutoSize = true;
			this->checkBoxScale->Location = System::Drawing::Point(32, 345);
			this->checkBoxScale->Name = L"checkBoxScale";
			this->checkBoxScale->Size = System::Drawing::Size(55, 17);
			this->checkBoxScale->TabIndex = 20;
			this->checkBoxScale->Text = L"Scale";
			this->checkBoxScale->UseVisualStyleBackColor = true;
			this->checkBoxScale->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxScale_CheckedChanged);
			//
			// trackBarWaterFrequency
			//
			this->trackBarWaterFrequency->Location = System::Drawing::Point(140, 403);
			this->trackBarWaterFrequency->Maximum = 400;
			this->trackBarWaterFrequency->Minimum = 0;
			this->trackBarWaterFrequency->Name = L"trackBarWaterFrequency";
			this->trackBarWaterFrequency->Size = System::Drawing::Size(200, 45);
			this->trackBarWaterFrequency->TabIndex = 22;
			this->trackBarWaterFrequency->Value = 200;
			this->trackBarWaterFrequency->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarWaterFrequency_Scroll);
			//
			// labelWaterFrequency
			//
			this->labelWaterFrequency->AutoSize = true;
			this->labelWaterFrequency->Location = System::Drawing::Point(29, 403);
			this->labelWaterFrequency->Name = L"labelWaterFrequency";
			this->labelWaterFrequency->Size = System::Drawing::Size(60, 13);
			this->labelWaterFrequency->TabIndex = 21;
			this->labelWaterFrequency->Text = L"Frequency";
			//
			// labelWaterFrequencyValue
			//
			this->labelWaterFrequencyValue->AutoSize = true;
			this->labelWaterFrequencyValue->Location = System::Drawing::Point(346, 403);
			this->labelWaterFrequencyValue->Name = L"labelWaterFrequencyValue";
			this->labelWaterFrequencyValue->Size = System::Drawing::Size(30, 13);
			this->labelWaterFrequencyValue->TabIndex = 23;
			this->labelWaterFrequencyValue->Text = L"0.50";
			//
			// trackBarWaterAmplitude
			//
			this->trackBarWaterAmplitude->Location = System::Drawing::Point(140, 450);
			this->trackBarWaterAmplitude->Maximum = 100;
			this->trackBarWaterAmplitude->Minimum = 0;
			this->trackBarWaterAmplitude->Name = L"trackBarWaterAmplitude";
			this->trackBarWaterAmplitude->Size = System::Drawing::Size(200, 45);
			this->trackBarWaterAmplitude->TabIndex = 25;
			this->trackBarWaterAmplitude->Value = 50;
			this->trackBarWaterAmplitude->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarWaterAmplitude_Scroll);
			//
			// labelWaterAmplitude
			//
			this->labelWaterAmplitude->AutoSize = true;
			this->labelWaterAmplitude->Location = System::Drawing::Point(29, 450);
			this->labelWaterAmplitude->Name = L"labelWaterAmplitude";
			this->labelWaterAmplitude->Size = System::Drawing::Size(58, 13);
			this->labelWaterAmplitude->TabIndex = 24;
			this->labelWaterAmplitude->Text = L"Amplitude";
			//
			// labelWaterAmplitudeValue
			//
			this->labelWaterAmplitudeValue->AutoSize = true;
			this->labelWaterAmplitudeValue->Location = System::Drawing::Point(346, 450);
			this->labelWaterAmplitudeValue->Name = L"labelWaterAmplitudeValue";
			this->labelWaterAmplitudeValue->Size = System::Drawing::Size(30, 13);
			this->labelWaterAmplitudeValue->TabIndex = 26;
			this->labelWaterAmplitudeValue->Text = L"0.50";
			//
			// checkBoxWireframe
			//
			this->checkBoxWireframe->AutoSize = true;
			this->checkBoxWireframe->Location = System::Drawing::Point(32, 510);
			this->checkBoxWireframe->Name = L"checkBoxWireframe";
			this->checkBoxWireframe->Size = System::Drawing::Size(110, 17);
			this->checkBoxWireframe->TabIndex = 27;
			this->checkBoxWireframe->Text = L"Wireframe Render";
			this->checkBoxWireframe->UseVisualStyleBackColor = true;
			this->checkBoxWireframe->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxWireframe_CheckedChanged);
			//
			// checkBoxTintBlue
			//
			this->checkBoxTintBlue->AutoSize = true;
			this->checkBoxTintBlue->Location = System::Drawing::Point(32, 535);
			this->checkBoxTintBlue->Name = L"checkBoxTintBlue";
			this->checkBoxTintBlue->Size = System::Drawing::Size(70, 17);
			this->checkBoxTintBlue->TabIndex = 28;
			this->checkBoxTintBlue->Text = L"Tint Blue";
			this->checkBoxTintBlue->UseVisualStyleBackColor = true;
			this->checkBoxTintBlue->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxTintBlue_CheckedChanged);
			//
			// ToolWindow
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(400, 650);

			// Add Mode 0 controls
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
			this->Controls->Add(this->buttonResetLight);

			// Add Mode 1 controls
			this->Controls->Add(this->buttonResetTransform);
			this->Controls->Add(this->checkBoxTranslate);
			this->Controls->Add(this->checkBoxRotate);
			this->Controls->Add(this->checkBoxScale);

			// Add Mode 2 controls
			this->Controls->Add(this->labelWaterAmplitudeValue);
			this->Controls->Add(this->labelWaterAmplitude);
			this->Controls->Add(this->trackBarWaterAmplitude);
			this->Controls->Add(this->labelWaterFrequencyValue);
			this->Controls->Add(this->labelWaterFrequency);
			this->Controls->Add(this->trackBarWaterFrequency);
			this->Controls->Add(this->checkBoxWireframe);
			this->Controls->Add(this->checkBoxTintBlue);

			// Add Radio Buttons
			this->Controls->Add(this->radioButtonSpaceScene);
			this->Controls->Add(this->radioButtonWaterScene);
			this->Controls->Add(this->radioButtonTransform);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarWaterFrequency))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarWaterAmplitude))->EndInit();
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

	private: System::Void radioButtonTransform_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (radioButtonTransform->Checked) {
			CurrentMode = 1;
		}
	}

	private: System::Void radioButtonWaterScene_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (radioButtonWaterScene->Checked) {
			CurrentMode = 2;
		}
	}

	private: System::Void radioButtonSpaceScene_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (radioButtonSpaceScene->Checked) {
			CurrentMode = 3;
		}
	}

	private: System::Void buttonResetLight_Click(System::Object^ sender, System::EventArgs^ e) {
		ResetLightPosition = true;
	}

	// Mode 1: Transform event handlers
	private: System::Void buttonResetTransform_Click(System::Object^ sender, System::EventArgs^ e) {
		ResetTransform = true;
	}

	private: System::Void checkBoxTranslate_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		EnableTranslate = checkBoxTranslate->Checked;
	}

	private: System::Void checkBoxRotate_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		EnableRotate = checkBoxRotate->Checked;
	}

	private: System::Void checkBoxScale_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		EnableScale = checkBoxScale->Checked;
	}

	// Mode 2: Water Scene event handlers
	private: System::Void trackBarWaterFrequency_Scroll(System::Object^ sender, System::EventArgs^ e) {
		WaterFrequency = trackBarWaterFrequency->Value;
		labelWaterFrequencyValue->Text = String::Format("{0:F2}", WaterFrequency / 100.0f);
	}

	private: System::Void trackBarWaterAmplitude_Scroll(System::Object^ sender, System::EventArgs^ e) {
		WaterAmplitude = trackBarWaterAmplitude->Value;
		labelWaterAmplitudeValue->Text = String::Format("{0:F2}", WaterAmplitude / 100.0f);
	}

	private: System::Void checkBoxWireframe_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		WireframeRender = checkBoxWireframe->Checked;
	}

	private: System::Void checkBoxTintBlue_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		TintBlue = checkBoxTintBlue->Checked;
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
