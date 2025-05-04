#include <wx/wx.h>

// Define a new application type
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Define a new frame (window) type
class MyFrame : public wxFrame {
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "Dictionary", wxDefaultPosition, wxSize(400, 500))
    {
        // Create a panel in the frame
        wxPanel* mainPnl = new wxPanel(this);
        mainPnl->SetBackgroundColour(wxColour(230, 230, 230));  // Purple background

        // --- Create controls ---
        wxTextCtrl* searchBar = new wxTextCtrl(mainPnl, wxID_ANY, "Enter a word");
        wxButton* searchBtn = new wxButton(mainPnl, wxID_ANY, "Search");

        // --- Horizontal sizer for the search row ---
        wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
        hbox->Add(searchBar, 1, wxEXPAND | wxRIGHT, 10);  // Stretchable textbox
        hbox->Add(searchBtn, 0);  // Fixed-size button

        // --- Vertical sizer for the whole panel ---
        wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
        vbox->Add(hbox, 0, wxEXPAND | wxALL, 10);  // Add horizontal search bar


        // --- Horizontal sizer for the search row ---
        wxBoxSizer* f = new wxBoxSizer(wxHORIZONTAL);
        f->Add(new wxStaticText(mainPnl, wxID_ANY, "Search for a word\n"), 1, wxEXPAND | wxRIGHT, 10);  // Stretchable textbox

        vbox->Add(f, 0, wxEXPAND | wxALL, 10);

        // --- Set sizer on the panel ---
        mainPnl->SetSizer(vbox);
        mainPnl->Layout();

        // --- Now put the panel into the frame ---
        wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
        frameSizer->Add(mainPnl, 1, wxEXPAND);
        this->SetSizer(frameSizer);
        this->Layout();
    }
};



// This macro tells wxWidgets to create the application object the main
wxIMPLEMENT_APP(MyApp);



// Initialize the application and create the main window
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);  // Show the main window
    return true;
}
