#include "FBVLC_Win.h"

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
        HDC hMemDC = CreateCompatibleDC(hDC);
        HBITMAP hBmp = CreateCompatibleBitmap(hDC, m_media_width, m_media_height);

        BITMAPINFO BmpInfo; ZeroMemory(&BmpInfo, sizeof(BmpInfo));
        BITMAPINFOHEADER& BmpH = BmpInfo.bmiHeader;
        BmpH.biSize = sizeof(BITMAPINFOHEADER);
        BmpH.biWidth = m_media_width;
        BmpH.biHeight = m_media_height;
        BmpH.biPlanes = 1;
        BmpH.biBitCount = DEF_PIXEL_BYTES*8;
        BmpH.biCompression = BI_RGB;
        //following members are already zeroed
        //BmpH.biSizeImage = 0;
        //BmpH.biXPelsPerMeter = 0;
        //BmpH.biYPelsPerMeter = 0;
        //BmpH.biClrUsed = 0;
        //BmpH.biClrImportant = 0;
        SetDIBits(hMemDC, hBmp, 0, m_media_height,
                  &m_frame_buf[0], &BmpInfo, DIB_RGB_COLORS);

        HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDC, hBmp);
        DeleteObject(hOldBmp);

        FB::Rect wrect;
        if ( getBrowser() == "IE" )
            wrect = fbRect;
        else
            wrect = w->getWindowPosition();

        BOOL r =
            StretchBlt( hDC,
                        wrect.left + (w->getWindowWidth() - m_media_width)/2,
                        wrect.top + (w->getWindowHeight() - m_media_height)/2,
                        m_media_width, m_media_height,
                        hMemDC, 0, m_media_height,
                        m_media_width, -((signed)m_media_height), SRCCOPY);

        DeleteDC(hMemDC);
    }

    return true;
}

void FBVLC_Win::on_option_change(vlc_player_option_e option)
{
    FBVLC::on_option_change(option);

    vlc_player_options& o = get_options();

    switch (option) {
        case po_bg_color: {
            HBRUSH hTmpBrush = m_hBgBrush;
            COLORREF bg_color = HtmlColor2RGB( o.get_bg_color(), RGB(0, 0, 0) );
            m_hBgBrush = CreateSolidBrush( bg_color );
            DeleteObject(hTmpBrush);

            if ( GetWindow() )
                GetWindow()->InvalidateWindow();
            break;
        }
        default:
            break;
    }
}
