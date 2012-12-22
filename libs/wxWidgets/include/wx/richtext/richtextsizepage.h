/////////////////////////////////////////////////////////////////////////////
// Name:        wx/richtext/richtextsizepage.h
// Purpose:
// Author:      Julian Smart
// Modified by:
// Created:     20/10/2010 10:23:24
// RCS-ID:
// Copyright:   (c) Julian Smart
// Licence:
/////////////////////////////////////////////////////////////////////////////

#ifndef _RICHTEXTSIZEPAGE_H_
#define _RICHTEXTSIZEPAGE_H_

/*!
 * Includes
 */

#include "wx/richtext/richtextdialogpage.h"
#include "wx/sizer.h"

////@begin includes
#include "wx/statline.h"
#include "wx/valgen.h"
////@end includes

/*!
 * Forward declarations
 */


/*!
 * Control identifiers
 */

////@begin control identifiers
#define SYMBOL_WXRICHTEXTSIZEPAGE_STYLE wxTAB_TRAVERSAL
#define SYMBOL_WXRICHTEXTSIZEPAGE_TITLE wxEmptyString
#define SYMBOL_WXRICHTEXTSIZEPAGE_IDNAME ID_WXRICHTEXTSIZEPAGE
#define SYMBOL_WXRICHTEXTSIZEPAGE_SIZE wxSize(400, 300)
#define SYMBOL_WXRICHTEXTSIZEPAGE_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * wxRichTextSizePage class declaration
 */

class WXDLLIMPEXP_RICHTEXT wxRichTextSizePage: public wxRichTextDialogPage
{
    DECLARE_DYNAMIC_CLASS( wxRichTextSizePage )
    DECLARE_EVENT_TABLE()
    DECLARE_HELP_PROVISION()

public:
    /// Constructors
    wxRichTextSizePage();
    wxRichTextSizePage( wxWindow* parent, wxWindowID id = SYMBOL_WXRICHTEXTSIZEPAGE_IDNAME, const wxPoint& pos = SYMBOL_WXRICHTEXTSIZEPAGE_POSITION, const wxSize& size = SYMBOL_WXRICHTEXTSIZEPAGE_SIZE, long style = SYMBOL_WXRICHTEXTSIZEPAGE_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_WXRICHTEXTSIZEPAGE_IDNAME, const wxPoint& pos = SYMBOL_WXRICHTEXTSIZEPAGE_POSITION, const wxSize& size = SYMBOL_WXRICHTEXTSIZEPAGE_SIZE, long style = SYMBOL_WXRICHTEXTSIZEPAGE_STYLE );

    /// Destructor
    ~wxRichTextSizePage();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

    /// Gets the attributes from the formatting dialog
    wxRichTextAttr* GetAttributes();

    /// Data transfer
    virtual bool TransferDataToWindow();
    virtual bool TransferDataFromWindow();

    /// Show/hide position controls
    void ShowPositionControls(bool show);

    /// Show/hide floating controls
    void ShowFloatingControls(bool show);

////@begin wxRichTextSizePage event handler declarations

    /// wxEVT_UPDATE_UI event handler for ID_RICHTEXT_VERTICAL_ALIGNMENT_COMBOBOX
    void OnRichtextVerticalAlignmentComboboxUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_RICHTEXT_WIDTH
    void OnRichtextWidthUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_RICHTEXT_HEIGHT
    void OnRichtextHeightUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_RICHTEXT_MIN_WIDTH
    void OnRichtextMinWidthUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_RICHTEXT_MIN_HEIGHT
    void OnRichtextMinHeightUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_RICHTEXT_MAX_WIDTH
    void OnRichtextMaxWidthUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_RICHTEXT_MAX_HEIGHT
    void OnRichtextMaxHeightUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_RICHTEXT_LEFT
    void OnRichtextLeftUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_RICHTEXT_LEFT_UNITS
    void OnRichtextTopUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_RICHTEXT_RIGHT
    void OnRichtextRightUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_RICHTEXT_BOTTOM
    void OnRichtextBottomUpdate( wxUpdateUIEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RICHTEXT_PARA_UP
    void OnRichtextParaUpClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RICHTEXT_PARA_DOWN
    void OnRichtextParaDownClick( wxCommandEvent& event );

////@end wxRichTextSizePage event handler declarations

////@begin wxRichTextSizePage member function declarations

    int GetPositionMode() const { return m_positionMode ; }
    void SetPositionMode(int value) { m_positionMode = value ; }

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end wxRichTextSizePage member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin wxRichTextSizePage member variables
    wxBoxSizer* m_parentSizer;
    wxBoxSizer* m_floatingControls;
    wxComboBox* m_float;
    wxBoxSizer* m_alignmentControls;
    wxCheckBox* m_verticalAlignmentCheckbox;
    wxComboBox* m_verticalAlignmentComboBox;
    wxCheckBox* m_widthCheckbox;
    wxTextCtrl* m_width;
    wxComboBox* m_unitsW;
    wxCheckBox* m_heightCheckbox;
    wxTextCtrl* m_height;
    wxComboBox* m_unitsH;
    wxCheckBox* m_minWidthCheckbox;
    wxTextCtrl* m_minWidth;
    wxComboBox* m_unitsMinW;
    wxCheckBox* m_minHeightCheckbox;
    wxTextCtrl* m_minHeight;
    wxComboBox* m_unitsMinH;
    wxCheckBox* m_maxWidthCheckbox;
    wxTextCtrl* m_maxWidth;
    wxComboBox* m_unitsMaxW;
    wxCheckBox* m_maxHeightCheckbox;
    wxTextCtrl* m_maxHeight;
    wxComboBox* m_unitsMaxH;
    wxBoxSizer* m_positionControls;
    wxBoxSizer* m_moveObjectParentSizer;
    wxComboBox* m_positionModeCtrl;
    wxCheckBox* m_positionLeftCheckbox;
    wxTextCtrl* m_left;
    wxComboBox* m_unitsLeft;
    wxCheckBox* m_positionTopCheckbox;
    wxTextCtrl* m_top;
    wxComboBox* m_unitsTop;
    wxCheckBox* m_positionRightCheckbox;
    wxTextCtrl* m_right;
    wxComboBox* m_unitsRight;
    wxCheckBox* m_positionBottomCheckbox;
    wxTextCtrl* m_bottom;
    wxComboBox* m_unitsBottom;
    wxBoxSizer* m_moveObjectSizer;
    int m_positionMode;
    /// Control identifiers
    enum {
        ID_WXRICHTEXTSIZEPAGE = 10700,
        ID_RICHTEXT_FLOATING_MODE = 10701,
        ID_RICHTEXT_VERTICAL_ALIGNMENT_CHECKBOX = 10708,
        ID_RICHTEXT_VERTICAL_ALIGNMENT_COMBOBOX = 10709,
        ID_RICHTEXT_WIDTH_CHECKBOX = 10702,
        ID_RICHTEXT_WIDTH = 10703,
        ID_RICHTEXT_UNITS_W = 10704,
        ID_RICHTEXT_HEIGHT_CHECKBOX = 10705,
        ID_RICHTEXT_HEIGHT = 10706,
        ID_RICHTEXT_UNITS_H = 10707,
        ID_RICHTEXT_MIN_WIDTH_CHECKBOX = 10715,
        ID_RICHTEXT_MIN_WIDTH = 10716,
        ID_RICHTEXT_UNITS_MIN_W = 10717,
        ID_RICHTEXT_MIN_HEIGHT_CHECKBOX = 10718,
        ID_RICHTEXT_MIN_HEIGHT = 10719,
        ID_RICHTEXT_UNITS_MIN_H = 10720,
        ID_RICHTEXT_MAX_WIDTH_CHECKBOX = 10721,
        ID_RICHTEXT_MAX_WIDTH = 10722,
        ID_RICHTEXT_UNITS_MAX_W = 10723,
        ID_RICHTEXT_MAX_HEIGHT_CHECKBOX = 10724,
        ID_RICHTEXT_MAX_HEIGHT = 10725,
        ID_RICHTEXT_UNITS_MAX_H = 10726,
        ID_RICHTEXT_POSITION_MODE = 10735,
        ID_RICHTEXT_LEFT_CHECKBOX = 10710,
        ID_RICHTEXT_LEFT = 10711,
        ID_RICHTEXT_LEFT_UNITS = 10712,
        ID_RICHTEXT_TOP_CHECKBOX = 10710,
        ID_RICHTEXT_TOP = 10728,
        ID_RICHTEXT_TOP_UNITS = 10729,
        ID_RICHTEXT_RIGHT_CHECKBOX = 10727,
        ID_RICHTEXT_RIGHT = 10730,
        ID_RICHTEXT_RIGHT_UNITS = 10731,
        ID_RICHTEXT_BOTTOM_CHECKBOX = 10732,
        ID_RICHTEXT_BOTTOM = 10733,
        ID_RICHTEXT_BOTTOM_UNITS = 10734,
        ID_RICHTEXT_PARA_UP = 10713,
        ID_RICHTEXT_PARA_DOWN = 10714
    };
////@end wxRichTextSizePage member variables
};

#endif
    // _RICHTEXTSIZEPAGE_H_
