#pragma once

#include "wx/wx.h"
#include <thread>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	wxButton* m_btn_openFile = NULL;
	wxButton* m_btn_saveFile = NULL;
	wxButton* m_btn_encryptData = NULL;
	wxButton* m_btn_decryptData = NULL;
	wxTextCtrl* m_txt_status = NULL;

	void OpenFile(wxCommandEvent&);
	void SaveFile(wxCommandEvent&);
	void EncryptData();
	void DecryptData();
	void StartDecryptThread(wxCommandEvent&);
	void StartEncryptThread(wxCommandEvent&);
	void DisableButtons();
	void EnableButtons();

	wxDECLARE_EVENT_TABLE();

private:
	bool isEncrypted = false;
	unsigned char* fileBytes = NULL;
	size_t arrLength = 0;
	unsigned char* aesKey = new unsigned char[16]{ 0x27, 0x99, 0x77, 0xf6, 0x2f, 0x6c, 0xfd, 0x2d, 0x91, 0xcd, 0x75, 0xb8, 0x89, 0xce, 0x0c, 0x9a };
	unsigned char* xorKey = new unsigned char[4]{ 0x73, 0x8B, 0x55, 0x44 };
};

