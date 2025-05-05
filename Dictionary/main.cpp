#include <wx/wx.h>
#include "Dictionary.h"
#include <map>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "Dictionary", wxDefaultPosition, wxSize(400, 500))
    {
        wxPanel* mainPnl = new wxPanel(this);
        mainPnl->SetBackgroundColour(wxColour(230, 230, 230));

        searchBar = new wxTextCtrl(mainPnl, wxID_ANY, "Enter a word");
        wxButton* searchBtn = new wxButton(mainPnl, wxID_ANY, "Search");

        wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
        hbox->Add(searchBar, 1, wxEXPAND | wxRIGHT, 10);  
        hbox->Add(searchBtn, 0); 

        wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
        vbox->Add(hbox, 0, wxEXPAND | wxALL, 10);  

		wxPanel* resultPanel = new wxPanel(mainPnl);
		resultPanel->SetBackgroundColour(wxColour(255, 255, 255));
        
		resultLabel = new wxStaticText(resultPanel, wxID_ANY, "");
		resultLabel->SetForegroundColour(wxColour(0, 0, 0));
		resultLabel->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

        vbox->Add(resultPanel, 1, wxEXPAND | wxALL, 10);

        mainPnl->SetSizer(vbox);
        mainPnl->Layout();

        wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
        frameSizer->Add(mainPnl, 1, wxEXPAND);
        this->SetSizer(frameSizer);
        this->Layout();

        searchBtn->Bind(wxEVT_BUTTON, &MyFrame::OnSearch, this);

    }
private:
    wxTextCtrl* searchBar;
    std::vector<WordEntry> wordEntries = parseWordMeaningsFromFile("dictionary.json");
    void OnSearch(wxCommandEvent& event);
    wxStaticText* resultLabel;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show(true); 
    return true;
}

void MyFrame::OnSearch(wxCommandEvent& event)
{
	wxString word = searchBar->GetValue();
	if (wordEntries.empty()) {
		wxMessageBox("Failed to load dictionary data.");
		return;
	}
    int index = binarySearch(wordEntries, word.ToStdString());
	if (index != -1) {
		resultLabel->SetLabel(wordEntries[index].meaning);
	}
	else if (word.IsEmpty()) {
		wxMessageBox("Please enter a word to search.");
	}
	else {
		wxMessageBox("Word not found in the dictionary.");
	}
}
