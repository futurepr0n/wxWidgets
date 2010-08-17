/////////////////////////////////////////////////////////////////////////////
// Name:        src/msw/richmsgdlg.cpp
// Purpose:     wxRichMessageDialog
// Author:      Rickard Westerlund
// Created:     2010-07-04
// RCS-ID:      $Id$
// Copyright:   (c) 2010 wxWidgets team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#if wxUSE_RICHMSGDLG

#include "wx/scopedptr.h"
#include "wx/dynlib.h"
#include "wx/msw/private/msgdlg.h"
#include "wx/richmsgdlg.h"

#ifdef wxHAS_MSW_TASKDIALOG
using wxMSWMessageDialog::wxMSWTaskDialogConfig;
#endif

// ----------------------------------------------------------------------------
// wxRichMessageDialog
// ----------------------------------------------------------------------------

int wxRichMessageDialog::ShowModal()
{
#ifdef wxHAS_MSW_TASKDIALOG
    // use generic version when task dialogs aren't available.
    if ( !wxMSWMessageDialog::HasNativeTaskDialog() )
        return wxGenericRichMessageDialog::ShowModal();

    // create a task dialog
    WinStruct<TASKDIALOGCONFIG> tdc;
    wxMSWTaskDialogConfig wxTdc(*this);

    wxTdc.MSWCommonTaskDialogInit( tdc );

    // add a checkbox
    if ( !m_checkBoxText.empty() )
    {
        tdc.pszVerificationText = m_checkBoxText.wx_str();
        if ( m_checkBoxValue )
            tdc.dwFlags |= TDF_VERIFICATION_FLAG_CHECKED;
    }

    // add collapsible footer
    if ( !m_detailedText.empty() )
        tdc.pszExpandedInformation = m_detailedText.wx_str();

    wxLoadedDLL dllComCtl32( "comctl32.dll" );
    taskDialogIndirect_t taskDialogIndirect =
        (taskDialogIndirect_t) dllComCtl32.GetSymbol( "TaskDialogIndirect" );

    // create the task dialog, process the answer and return it.
    BOOL checkBoxChecked;
    int msAns;
    HRESULT hr = taskDialogIndirect( &tdc, &msAns, NULL, &checkBoxChecked );
    if ( FAILED(hr) )
    {
        wxLogApiError( "TaskDialogIndirect", hr );
        return wxID_CANCEL;
    }
    m_checkBoxValue = checkBoxChecked != FALSE;

    return wxMSWMessageDialog::MSWTranslateReturnCode( msAns );
#else
    // use the generic version when task dialogs aren't available
    // at compile time.
    return wxGenericRichMessageDialog::ShowModal();
#endif // wxHAS_MSW_TASKDIALOG
}

#endif // wxUSE_RICHMSGDLG