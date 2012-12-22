///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __OFXWXPICKABLESCENEBASE_H__
#define __OFXWXPICKABLESCENEBASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ofxWxPickableSceneFrameBase
///////////////////////////////////////////////////////////////////////////////
class ofxWxPickableSceneFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar1;
		wxMenu* m_fileMenu;
		wxMenu* m_menuHelp;
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panel4;
		wxButton* m_hiButton;
		wxStaticText* m_staticText1;
		wxPanel* m_panel3;
		wxPanel* m_glCanvasParentPanel;
		wxStatusBar* m_statusBar2;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnQuitMenuItemSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAboutMenuItemSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHiButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ofxWxPickableSceneFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ofxWxPickableScene"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1000,728 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~ofxWxPickableSceneFrameBase();
		
		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 365 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( ofxWxPickableSceneFrameBase::m_splitter1OnIdle ), NULL, this );
		}
	
};

#endif //__OFXWXPICKABLESCENEBASE_H__
