/**
 * @file ViewEdit.h
 * @author Charles B. Owen
 *
 *  Basic edit view class for the Canadian Experience
 *
 * The window is a child of the main frame, which holds this
 * window, the menu bar, and the status bar.
 */

#ifndef CANADIANEXPERIENCE_VIEWEDIT_H
#define CANADIANEXPERIENCE_VIEWEDIT_H

#include "PictureObserver.h"

class Actor;
class Drawable;
class LabDrawable;

/**
 * View class for our aquarium
 */
class ViewEdit final : public wxScrolledCanvas, public PictureObserver {
private:
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftDoubleClick(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);

    void OnEditMove(wxCommandEvent& event);
    void OnEditRotate(wxCommandEvent& event);
    void OnUpdateEditMove(wxUpdateUIEvent& event);
    void OnUpdateEditRotate(wxUpdateUIEvent& event);

    /// The last mouse position
    wxPoint mLastMouse = wxPoint(0, 0);

    /// The currently selected actor
    std::shared_ptr<Actor> mSelectedActor;

    /// The currently selected drawable
    std::shared_ptr<Drawable> mSelectedDrawable;

    /// A pointer to the lab drawable so it can show the dialog box
    std::shared_ptr<LabDrawable> mLabDrawable;

public:
    /// The current mouse mode
    enum class Mode {Move, Rotate};

    /// The currently set mouse mode
    Mode mMode = Mode::Move;

public:
    ViewEdit(wxFrame* parent);

    void UpdateObserver() override;

    /**
     * Let ViewEdit know about the lab drawable so it can show the dialog box
     * @param labDrawable A pointer to the lab drawable
     */
    void SetLabDrawable(std::shared_ptr<LabDrawable> labDrawable) { mLabDrawable = labDrawable; }
};

#endif //CANADIANEXPERIENCE_VIEWEDIT_H
