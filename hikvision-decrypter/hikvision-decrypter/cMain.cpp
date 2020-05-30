#include "cMain.h"
#include "hikvision.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, OpenFile)
	EVT_BUTTON(10002, SaveFile)
	EVT_BUTTON(10003, StartEncryptThread)
	EVT_BUTTON(10004, StartDecryptThread)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Hikvision Decrypter by WormChickenWizard", wxPoint(30, 30), wxSize(450, 500))
{
	// Create the buttons for opening and saving the configuration file
	m_btn_openFile = new wxButton(this, 10001, "Open Configuration File", wxPoint(280, 350), wxSize(150, 50));
	m_btn_saveFile = new wxButton(this, 10002, "Save Configuration File", wxPoint(280, 405), wxSize(150, 50));
	m_btn_encryptData = new wxButton(this, 10003, "Encrypt Data", wxPoint(125, 350), wxSize(150, 50));
	m_btn_decryptData = new wxButton(this, 10004, "Decrypt Data", wxPoint(125, 405), wxSize(150, 50));


	// Create a textbox for feedback regarding the status of the program
	m_txt_status = new wxTextCtrl(this, wxID_ANY, "Ready", wxPoint(10, 10), wxSize(410, 30));
	m_txt_status->SetEditable(false);
	m_txt_status->SetWindowStyleFlag(wxALIGN_CENTRE);
}

cMain::~cMain()
{
	delete[] fileBytes;
	delete[] aesKey;
	delete[] xorKey;
}

void cMain::OpenFile(wxCommandEvent& evt)
{
	DisableButtons();

	m_txt_status->SetValue("Please select a file");

	// Create an instance of the wxFileDialog to open the file and use it
	wxFileDialog* OpenDialog = new wxFileDialog(this, "Choose a file to open", wxEmptyString, wxEmptyString, wxEmptyString, wxFD_OPEN, wxDefaultPosition);

	int fileDialogOutcome = OpenDialog->ShowModal();

	if (fileDialogOutcome == wxID_OK)
	{
		m_txt_status->SetValue("Opening...");
		fileBytes = readInBytes(std::string(OpenDialog->GetPath().mb_str()), arrLength);
		m_txt_status->SetValue("Successfully loaded file");
		
		// Prompt user to see if the file is a encrypted database or decrypted database
		wxMessageDialog* messageBox = new wxMessageDialog(this, "Is this file a encrypted database or a decrypted database?", wxEmptyString, wxYES_NO | wxCENTRE, wxPoint(225, 250));
		messageBox->SetYesNoLabels("Encrypted", "Decrypted");
		int messageBoxOutcome = messageBox->ShowModal();

		if (messageBoxOutcome == wxID_YES)
			isEncrypted = true;
		else if (messageBoxOutcome == wxID_NO)
			isEncrypted = false;
		else
			m_txt_status->SetValue("An unforseen response occured with the encryption/decryption prompt :/");
		messageBox->Destroy();

	}
	else if (fileDialogOutcome == wxID_CANCEL)
	{
		m_txt_status->SetValue("Open Canceled");
	}
	else
	{
		m_txt_status->SetValue("Something unforseen happened :/");
	}
	OpenDialog->Destroy();
	EnableButtons();
	evt.Skip();
}

void cMain::SaveFile(wxCommandEvent& evt)
{
	if (fileBytes == NULL)
	{
		m_txt_status->SetValue("There's nothing currently to save. Please open a file");
		return;
	}

	DisableButtons();

	wxFileDialog* SaveDialog = new wxFileDialog(this, "Choose where to save", wxEmptyString, wxEmptyString, wxEmptyString, wxFD_SAVE, wxDefaultPosition);
	int fileDialogOutcome = SaveDialog->ShowModal();

	if (fileDialogOutcome == wxID_OK)
	{
		m_txt_status->SetValue("Saving...");
		writeOutBytes(std::string(SaveDialog->GetPath().mb_str()), fileBytes, arrLength);
		m_txt_status->SetValue("Successfully saved file");
	}
	else if (fileDialogOutcome == wxID_CANCEL)
	{
		m_txt_status->SetValue("Save canceled");
	}
	else
	{
		m_txt_status->SetValue("Something unforseen happened :/");
	}
	SaveDialog->Destroy();
	EnableButtons();
	evt.Skip();
}

void cMain::DecryptData()
{
	if (!isEncrypted)
	{
		m_txt_status->SetValue("The data is already decrypted");
		return;
	}

	DisableButtons();

	m_txt_status->SetValue("Decrypting AES...");
	decryptAES(fileBytes, arrLength, aesKey);
	m_txt_status->SetValue("Decrypting XOR...");
	decryptXOR(fileBytes, arrLength, xorKey);
	m_txt_status->SetValue("Successfully decrypted data");
	isEncrypted = false;

	EnableButtons();
}

void cMain::StartDecryptThread(wxCommandEvent& evt)
{
	std::thread threadObject([this] {this->DecryptData(); });
	threadObject.detach();

	evt.Skip();
}

void cMain::StartEncryptThread(wxCommandEvent& evt)
{
	std::thread threadObject([this] {this->EncryptData(); });
	threadObject.detach();

	evt.Skip();
}

void cMain::DisableButtons()
{
	m_btn_openFile->Disable();
	m_btn_saveFile->Disable();
	m_btn_decryptData->Disable();
	m_btn_encryptData->Disable();
}

void cMain::EnableButtons()
{
	m_btn_openFile->Enable();
	m_btn_saveFile->Enable();
	m_btn_decryptData->Enable();
	m_btn_encryptData->Enable();
}

void cMain::EncryptData()
{
	if (isEncrypted)
	{
		m_txt_status->SetValue("The data is already encrypted");
		return;
	}

	DisableButtons();

	m_txt_status->SetValue("Encrypting XOR...");
	decryptXOR(fileBytes, arrLength, xorKey);
	m_txt_status->SetValue("Encrypting AES...");
	encryptAES(fileBytes, arrLength, aesKey);
	m_txt_status->SetValue("Successfully encrypted data");
	isEncrypted = true;

	EnableButtons();
}
