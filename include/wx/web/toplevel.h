#ifndef __WX_TOPLEVEL_H__
#define __WX_TOPLEVEL_H__

/* WARNING: right now we assume there is ONLY ONE top level window
 * TODO: fix this
 *       - modify wxWindowDC so that it sends enough information so that the
 *       client can select the appropriate window/canvas to draw to
 */

class wxTopLevelWindowWeb : public wxTopLevelWindowBase {
public:
    wxTopLevelWindowWeb();
    wxTopLevelWindowWeb(wxWindow *parent,
                            wxWindowID id,
                            const wxString& title,
                            const wxPoint& pos = wxDefaultPosition,
                            const wxSize& size = wxDefaultSize,
                            long style = wxDEFAULT_FRAME_STYLE,
                            const wxString& name = wxFrameNameStr);

    bool Create(wxWindow *parent,
                wxWindowID id,
                const wxString& title,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxDEFAULT_FRAME_STYLE,
                const wxString& name = wxFrameNameStr);

    virtual ~wxTopLevelWindowWeb();

    /* For now, these functions are all stubs. Most of them will have to stay that way since
     * Javascript doesn't provide methods for iconizing or putting in full screen (right?).
     * Maximimization is technically possible by resizing and repositioning the window, but
     * doing so probably violates user expectations for a web page */
    virtual void Maximize(bool maximize = true) {}
    virtual bool IsMaximized() const {return false;}
    virtual void Iconize(bool iconize = true) {}
    virtual bool IsIconized() const {return false;}
    virtual void Restore() {}
    virtual bool ShowFullScreen(bool show, long style = wxFULLSCREEN_ALL) {return false;}
    virtual bool IsFullScreen() const {return false;}

    virtual bool Show(bool show = true);

    virtual void SetTitle(const wxString &title) {m_title = title;}
    virtual wxString GetTitle() const {return m_title;}

private:
    wxString m_title;
};

#endif // __WX_TOPLEVEL_H__
