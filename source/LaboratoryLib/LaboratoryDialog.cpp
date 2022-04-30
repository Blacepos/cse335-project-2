/**
 * @file LaboratoryDialog.cpp
 * @author Charles Owen
 *
 * You are not allowed to change this class in any way!
 */

#include "pch.h"

#include <wx/valnum.h>
#include <wx/stdpaths.h>

#include "Laboratory.h"

#include "LaboratoryDialog.h"

/**
 * Constructor
 * @param parent Parent window to put this dialog box inside
 * @param laboratory Laboratory we are editing
 */
LaboratoryDialog::LaboratoryDialog(wxWindow* parent, std::shared_ptr<Laboratory> laboratory) :
        wxDialog(parent, wxID_ANY, L"Laboratory Selection"), mLaboratory(laboratory)
{
    mLaboratoryNumber = laboratory->GetLaboratoryNumber();

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxBoxSizer* sizerMain;
    sizerMain = new wxBoxSizer( wxVERTICAL );

    // Where do the images come from?
    auto standardPaths = wxStandardPaths::Get();
    auto resourcesDir = standardPaths.GetResourcesDir().ToStdWstring();

    wxStaticBitmap* bitmap;
    bitmap = new wxStaticBitmap( this, wxID_ANY, wxBitmap( resourcesDir + "/images/frank.jpg", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
    sizerMain->Add( bitmap, 0, 0, 5 );

    wxBoxSizer* sizerHorz;
    sizerHorz = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText* labelLaboratoryNumber;
    labelLaboratoryNumber = new wxStaticText( this, wxID_ANY, wxT("Laboratory Number:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
    labelLaboratoryNumber->Wrap( -1 );
    sizerHorz->Add( labelLaboratoryNumber, 1, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxTOP, 10 );


    sizerHorz->Add( 5, 0, 0, wxEXPAND, 5 );

    mLaboratoryNumberCtrl = new wxTextCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
    sizerHorz->Add( mLaboratoryNumberCtrl, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxTOP, 10 );


    sizerMain->Add( sizerHorz, 1, wxALIGN_CENTER_HORIZONTAL, 5 );

    auto sizerButtons = new wxStdDialogButtonSizer();
    auto sizerButtonsOK = new wxButton( this, wxID_OK );
    sizerButtons->AddButton( sizerButtonsOK );
    auto sizerButtonsCancel = new wxButton( this, wxID_CANCEL );
    sizerButtons->AddButton( sizerButtonsCancel );
    sizerButtons->Realize();

    sizerMain->Add( sizerButtons, 1, wxEXPAND, 5 );

    this->SetSizer( sizerMain );
    this->Layout();
    sizerMain->Fit( this );

    this->Centre( wxBOTH );

    wxIntegerValidator<int> validator(&mLaboratoryNumber);
    mLaboratoryNumberCtrl->SetValidator(validator);

    Bind(wxEVT_BUTTON, &LaboratoryDialog::OnOK, this,wxID_OK);
    Bind(wxEVT_INIT_DIALOG, &LaboratoryDialog::OnInitDialog, this);
}

/**
 * Handle the OK button press event
 * @param event Button press event
 */
void LaboratoryDialog::OnOK(wxCommandEvent& event)
{
    if ( Validate() && TransferDataFromWindow() )
    {
        EndModal(wxID_OK);
        mLaboratory->SetLaboratoryNumber(mLaboratoryNumber);
    }
}

/**
 * Initialize dialog event handler.
 *
 * This allows us to preselect the content of the edit control
 * so we don't have to do so manually to change it.
 *
 * @param event EVT_INIT_DIALOG event object
 */
void LaboratoryDialog::OnInitDialog(wxInitDialogEvent& event)
{
    TransferDataToWindow();
    mLaboratoryNumberCtrl->SelectAll();
}