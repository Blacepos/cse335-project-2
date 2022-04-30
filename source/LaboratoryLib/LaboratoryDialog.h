/**
 * @file LaboratoryDialog.h
 * @author Charles Owen
 *
 * Class that implements a dialog box for laboratory selection
 *
 * You are not allowed to change this class in any way!
 */

#ifndef CANADIANEXPERIENCE_LABORATORYDIALOG_H
#define CANADIANEXPERIENCE_LABORATORYDIALOG_H

class Laboratory;

/**
 * Exported dialog box class for selecting a laboratory
 *
 * You are not allowed to change this class in any way!
 */
class LaboratoryDialog : public wxDialog {
private:
    void OnOK(wxCommandEvent& event);
    void OnInitDialog(wxInitDialogEvent& event);

    /// Laboratory we are editing
    std::shared_ptr<Laboratory> mLaboratory;

    /// The laboratory number as used by the validator
    int mLaboratoryNumber;

    /// The laboratory number control
    wxTextCtrl* mLaboratoryNumberCtrl;

public:
    LaboratoryDialog(wxWindow *parent, std::shared_ptr<Laboratory> laboratory);

};

#endif //CANADIANEXPERIENCE_LABORATORYDIALOG_H
