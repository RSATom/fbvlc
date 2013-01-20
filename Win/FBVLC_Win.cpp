#include "FBVLC_Win.h"
#include "resource.h"

////////////////////////////////////////////////////////////////////////////////
//WindowedWM class
////////////////////////////////////////////////////////////////////////////////
WindowedWM::WindowedWM(HMODULE hDllModule, vlc_player_options* po)
    :VLCWindowsManager(hDllModule, m_rc, po)
{
    m_rc.hBackgroundIcon =
        (HICON) LoadImage(hDllModule, MAKEINTRESOURCE(IDI_BG_ICON),
                          IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);

    m_rc.hFullscreenBitmap =
        LoadImage(hDllModule, MAKEINTRESOURCE(IDB_FULLSCREEN),
                  IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);

    m_rc.hDeFullscreenBitmap =
        LoadImage(hDllModule, MAKEINTRESOURCE(IDB_DEFULLSCREEN),
                  IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);

    m_rc.hPauseBitmap =
        LoadImage(hDllModule, MAKEINTRESOURCE(IDB_PAUSE),
                  IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);

    m_rc.hPlayBitmap =
        LoadImage(hDllModule, MAKEINTRESOURCE(IDB_PLAY),
                  IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);

    m_rc.hVolumeBitmap =
        LoadImage(hDllModule, MAKEINTRESOURCE(IDB_VOLUME),
                  IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);

    m_rc.hVolumeMutedBitmap =
        LoadImage(hDllModule, MAKEINTRESOURCE(IDB_MUTED),
                  IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);
}

////////////////////////////////////////////////////////////////////////////////
//FBVLC_Win class
////////////////////////////////////////////////////////////////////////////////
FBVLC_Win::FBVLC_Win()
    :m_hBgBrush( NULL )
{
    vlc_player_options& o = get_options();

    COLORREF bg_color = HtmlColor2RGB( o.get_bg_color(), RGB(0, 0, 0) );
    m_hBgBrush = CreateSolidBrush( bg_color );
}

FBVLC_Win::~FBVLC_Win()
{
    DeleteObject(m_hBgBrush);
}

bool FBVLC_Win::onRefreshEvent(FB::RefreshEvent *evt, FB::PluginWindowlessWin* w)
{
    HDC hDC = w->getHDC();
    FB::Rect fbRect = evt->bounds;

    RECT Rect = {fbRect.left, fbRect.top, fbRect.right, fbRect.bottom};
    FillRect(hDC, &Rect, m_hBgBrush);

    if ( m_frame_buf.size() &&
         m_frame_buf.size() >= m_media_width * m_media_height * DEF_PIXEL_BYTES)
    {
        BITMAPINFO BmpInfo; ZeroMemory(&BmpInfo, sizeof(BmpInfo));
        BITMAPINFOHEADER& BmpH = BmpInfo.bmiHeader;
        BmpH.biSize = sizeof(BITMAPINFOHEADER);
        BmpH.biWidth = m_media_width;
        BmpH.biHeight = -((int)m_media_height);
        BmpH.biPlanes = 1;
        BmpH.biBitCount = DEF_PIXEL_BYTES*8;
        BmpH.biCompression = BI_RGB;
        //following members are already zeroed
        //BmpH.biSizeImage = 0;
        //BmpH.biXPelsPerMeter = 0;
        //BmpH.biYPelsPerMeter = 0;
        //BmpH.biClrUsed = 0;
        //BmpH.biClrImportant = 0;


        FB::Rect wrect;
        if ( getBrowser() == "IE" )
            wrect = fbRect;
        else
            wrect = w->getWindowPosition();

        if( get_options().get_native_scaling() ) {
            const float src_aspect = (float)m_media_width / m_media_height;
            const float dst_aspect = (float)w->getWindowWidth()/w->getWindowHeight();
            unsigned dst_media_width = w->getWindowWidth();
            unsigned dst_media_height = w->getWindowHeight();
            if ( src_aspect > dst_aspect ) {
                if( w->getWindowWidth() != m_media_width ) { //don't scale if size equal
                    dst_media_height = static_cast<unsigned>( w->getWindowWidth() / src_aspect + 0.5);
                }
            }
            else {
                if( w->getWindowHeight() != m_media_height ) { //don't scale if size equal
                    dst_media_width = static_cast<unsigned>( w->getWindowHeight() * src_aspect + 0.5);
                }
            }

            SetStretchBltMode(hDC, COLORONCOLOR);
            BOOL r =
                StretchDIBits(hDC,
                              wrect.left + (w->getWindowWidth() - dst_media_width)/2,
                              wrect.top + (w->getWindowHeight() - dst_media_height)/2,
                              dst_media_width, dst_media_height,
                              0, 0,
                              m_media_width, m_media_height,
                              &m_frame_buf[0],
                              &BmpInfo, DIB_RGB_COLORS, SRCCOPY);
        } else {
            BOOL r =
                SetDIBitsToDevice(hDC,
                                  wrect.left + (w->getWindowWidth() - m_media_width)/2,
                                  wrect.top + (w->getWindowHeight() - m_media_height)/2,
                                  m_media_width, m_media_height,
                                  0, 0,
                                  0, m_media_height,
                                  &m_frame_buf[0],
                                  &BmpInfo, DIB_RGB_COLORS);
        }
    }

    return true;
}

void FBVLC_Win::on_option_change(vlc_player_option_e option)
{
    FBVLC::on_option_change(option);

    vlc_player_options& o = get_options();

    switch (option) {
        case po_bg_color: {
            if ( isWindowless() ) {
                HBRUSH hTmpBrush = m_hBgBrush;
                COLORREF bg_color = HtmlColor2RGB( o.get_bg_color(), RGB(0, 0, 0) );
                m_hBgBrush = CreateSolidBrush( bg_color );
                DeleteObject(hTmpBrush);

                if ( GetWindow() )
                    GetWindow()->InvalidateWindow();
            }
            else {
            }
            break;
        }
        default:
            break;
    }
}

bool FBVLC_Win::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindowWin* w)
{
    m_wm.reset(new WindowedWM(GetModuleHandleA(getFSPath().c_str()), &get_options()));
    m_wm->CreateWindows(w->getHWND());
    vlc_open();
    m_wm->LibVlcAttach(&get_player());
    return true;
}

bool FBVLC_Win::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindowWin* w)
{
    m_wm->LibVlcDetach();
    vlc_close();
    m_wm->DestroyWindows();
    return true;
}

bool FBVLC_Win::onWindowResized(FB::ResizedEvent *evt, FB::PluginWindowWin* w)
{
    VLCWnd* child = m_wm->getHolderWnd();
    if ( child ) {
        RECT rect;
        GetClientRect(w->getHWND(), &rect);
        MoveWindow(child->hWnd(),
                   0, 0,
                   rect.right-rect.left, rect.bottom-rect.top,
                   TRUE);
    };

    return true;
}

bool FBVLC_Win::is_fullscreen()
{
    if ( isWindowless() ) {
        return false;//fullscreen mode not supported in windowless mode for now
    } else {
        return m_wm.get() ? m_wm->IsFullScreen() : false ;
    }
}

void FBVLC_Win::set_fullscreen(bool fs)
{
    //fullscreen mode not supported in windowless mode for now
    if ( !isWindowless() && m_wm.get() ) {
        if ( !m_wm->IsFullScreen() && fs ) {
            m_wm->StartFullScreen();
        } else if ( m_wm->IsFullScreen() && !fs ) {
            m_wm->EndFullScreen();
        }
    }
}
void FBVLC_Win::toggle_fullscreen()
{
    //fullscreen mode not supported in windowless mode for now
    if ( !isWindowless() && m_wm.get() ) {
        m_wm->ToggleFullScreen();
    }
}
