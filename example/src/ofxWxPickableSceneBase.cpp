///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "src/ofxWxPickableSceneBase.h"

///////////////////////////////////////////////////////////////////////////

ofxWxPickableSceneFrameBase::ofxWxPickableSceneFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar1 = new wxMenuBar( 0 );
	m_fileMenu = new wxMenu();
	wxMenuItem* m_quitMenuItem;
	m_quitMenuItem = new wxMenuItem( m_fileMenu, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	m_fileMenu->Append( m_quitMenuItem );
	
	m_menubar1->Append( m_fileMenu, wxT("File") ); 
	
	m_menuHelp = new wxMenu();
	wxMenuItem* m_aboutMenuItem;
	m_aboutMenuItem = new wxMenuItem( m_menuHelp, wxID_ANY, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuHelp->Append( m_aboutMenuItem );
	
	m_menubar1->Append( m_menuHelp, wxT("Help") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( ofxWxPickableSceneFrameBase::m_splitter1OnIdle ), NULL, this );
	
	m_panel4 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel4->SetMaxSize( wxSize( 120,-1 ) );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_hiButton = new wxButton( m_panel4, wxID_ANY, wxT("Hi!"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	bSizer8->Add( m_hiButton, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText1 = new wxStaticText( m_panel4, wxID_ANY, wxT("Click a box and it should turn red.\nAlt + Left Mouse = dolly camera\nAlt + Middle Mouse = pan camera\nAlt + Right Mouse = zoom camera. "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer8->Add( m_staticText1, 1, wxALL|wxEXPAND, 5 );
	
	m_panel4->SetSizer( bSizer8 );
	m_panel4->Layout();
	bSizer8->Fit( m_panel4 );
	m_panel3 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_glCanvasParentPanel = new wxPanel( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxTRANSPARENT_WINDOW, wxT("glCanvasParentPanel") );
	bSizer2->Add( m_glCanvasParentPanel, 1, wxEXPAND | wxALL, 5 );
	
	m_panel3->SetSizer( bSizer2 );
	m_panel3->Layout();
	bSizer2->Fit( m_panel3 );
	m_splitter1->SplitVertically( m_panel4, m_panel3, 365 );
	bSizer1->Add( m_splitter1, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	m_statusBar2 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( m_quitMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ofxWxPickableSceneFrameBase::OnQuitMenuItemSelection ) );
	this->Connect( m_aboutMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ofxWxPickableSceneFrameBase::OnAboutMenuItemSelection ) );
	m_hiButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ofxWxPickableSceneFrameBase::OnHiButtonClick ), NULL, this );
}

ofxWxPickableSceneFrameBase::~ofxWxPickableSceneFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ofxWxPickableSceneFrameBase::OnQuitMenuItemSelection ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( ofxWxPickableSceneFrameBase::OnAboutMenuItemSelection ) );
	m_hiButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ofxWxPickableSceneFrameBase::OnHiButtonClick ), NULL, this );
	
}
