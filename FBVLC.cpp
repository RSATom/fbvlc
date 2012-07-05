/**********************************************************\

  Auto-generated FBVLC.cpp

  This file contains the auto-generated main plugin object
  implementation for the FireBreathed VLC project

\**********************************************************/

#include "FBVLCAPI.h"

#include "FBVLC.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn FBVLC::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginInitialize()
///
/// @see FB::FactoryBase::globalPluginInitialize
///////////////////////////////////////////////////////////////////////////////
void FBVLC::StaticInitialize()
{
    // Place one-time initialization stuff here; As of FireBreath 1.4 this should only
    // be called once per process
}

///////////////////////////////////////////////////////////////////////////////
/// @fn FBVLC::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginDeinitialize()
///
/// @see FB::FactoryBase::globalPluginDeinitialize
///////////////////////////////////////////////////////////////////////////////
void FBVLC::StaticDeinitialize()
{
    // Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
    // always be called just before the plugin library is unloaded
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  FBVLC constructor.  Note that your API is not available
///         at this point, nor the window.  For best results wait to use
///         the JSAPI object until the onPluginReady method is called
///////////////////////////////////////////////////////////////////////////////
FBVLC::FBVLC()
    :m_libvlc(0), m_media_width(0), m_media_height(0)
{
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  FBVLC destructor.
///////////////////////////////////////////////////////////////////////////////
FBVLC::~FBVLC()
{
    // This is optional, but if you reset m_api (the shared_ptr to your JSAPI
    // root object) and tell the host to free the retained JSAPI objects then
    // unless you are holding another shared_ptr reference to your JSAPI object
    // they will be released here.
    releaseRootJSAPI();
    m_host->freeRetainedObjects();
}

const char DEF_CHROMA[] = "RV32";
enum{
    DEF_PIXEL_BYTES = 4
};

unsigned FBVLC::video_format_cb(char *chroma,
                                unsigned *width, unsigned *height,
                                unsigned *pitches, unsigned *lines)
{
    FB::PluginWindow* w = GetWindow();
    if ( w ) {
        float src_aspect = (float)(*width) / (*height);
        float dst_aspect = (float)w->getWindowWidth()/w->getWindowHeight();
        if ( src_aspect > dst_aspect ) {
            (*width)  = w->getWindowWidth();
            (*height) = static_cast<unsigned>( (*width) / src_aspect );
        }
        else {
            (*height) = w->getWindowHeight();
            (*width)  = static_cast<unsigned>( (*height) * src_aspect );
        }
    }

    m_media_width  = (*width);
    m_media_height = (*height);

    memcpy(chroma, DEF_CHROMA, sizeof(DEF_CHROMA)-1);
    (*pitches) = m_media_width * DEF_PIXEL_BYTES;
    (*lines)   = m_media_height;

    m_frame_buf.resize( m_media_width * m_media_height * DEF_PIXEL_BYTES );

    return 1;
}

void FBVLC::video_cleanup_cb()
{
    m_frame_buf.resize(0);
    m_media_width  = 0;
    m_media_height = 0;
}

void* FBVLC::video_lock_cb(void **planes)
{
    (*planes) = &m_frame_buf[0];
    return 0;
}

void FBVLC::video_unlock_cb(void* /*picture*/, void *const * /*planes*/)
{
}

void FBVLC::video_display_cb(void * /*picture*/)
{
    FB::PluginWindow* w = GetWindow();
    if ( w ) {
        w->InvalidateWindow();
    }
}

void FBVLC::onPluginReady()
{
    // When this is called, the BrowserHost is attached, the JSAPI object is
    // created, and we are ready to interact with the page and such.  The
    // PluginWindow may or may not have already fire the AttachedEvent at
    // this point.

    /* prepare VLC command line */
    const char *libvlc_argv[] = {
        "--no-video-title-show",
#ifdef _DEBUG
        "-vvv",
#endif
    };

    m_libvlc = libvlc_new( sizeof(libvlc_argv) / sizeof(libvlc_argv[0]),
                           libvlc_argv );

    if ( m_libvlc ) {
        m_player.open(m_libvlc);
    }

    if ( m_player.is_open() && isWindowless() ) {
        libvlc_video_set_format_callbacks(get_player().get_mp(),
                                          video_format_proxy,
                                          video_cleanup_proxy);

        libvlc_video_set_callbacks(get_player().get_mp(),
                                   video_fb_lock_proxy,
                                   video_fb_unlock_proxy,
                                   video_fb_display_proxy,
                                   this);
    }
}

void FBVLC::shutdown()
{
    // This will be called when it is time for the plugin to shut down;
    // any threads or anything else that may hold a shared_ptr to this
    // object should be released here so that this object can be safely
    // destroyed. This is the last point that shared_from_this and weak_ptr
    // references to this object will be valid

    m_player.stop();

    if ( m_player.is_open() && isWindowless() ) {

        libvlc_video_set_format_callbacks(get_player().get_mp(),
                                          NULL,
                                          NULL);

        libvlc_video_set_callbacks(get_player().get_mp(),
                                   NULL,
                                   NULL,
                                   NULL,
                                   this);
    }

    if ( m_player.is_open() ) {
        m_player.close();
    }

    if ( m_libvlc ) {
        libvlc_free(m_libvlc);
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  Creates an instance of the JSAPI object that provides your main
///         Javascript interface.
///
/// Note that m_host is your BrowserHost and shared_ptr returns a
/// FB::PluginCorePtr, which can be used to provide a
/// boost::weak_ptr<FBVLC> for your JSAPI class.
///
/// Be very careful where you hold a shared_ptr to your plugin class from,
/// as it could prevent your plugin class from getting destroyed properly.
///////////////////////////////////////////////////////////////////////////////
FB::JSAPIPtr FBVLC::createJSAPI()
{
    // m_host is the BrowserHost
    return boost::make_shared<FBVLCAPI>(FB::ptr_cast<FBVLC>(shared_from_this()), m_host);
}

/*
bool FBVLC::onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse down at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool FBVLC::onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse up at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool FBVLC::onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse move at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}
*/

bool FBVLC::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *)
{
    // The window is attached; act appropriately
    return false;
}

bool FBVLC::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *)
{
    // The window is about to be detached; act appropriately
    return false;
}

bool FBVLC::onRefreshEvent(FB::RefreshEvent *evt, FB::PluginWindowlessWin* w)
{
    HDC hDC = w->getHDC();
    FB::Rect fbRect = evt->bounds;

    RECT Rect = {fbRect.left, fbRect.top, fbRect.right, fbRect.bottom};
    FillRect(hDC, &Rect, (HBRUSH) GetStockObject(BLACK_BRUSH));

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

        BOOL r =
            StretchBlt( hDC,
                        fbRect.left + (w->getWindowWidth() - m_media_width)/2,
                        fbRect.top + (w->getWindowHeight() - m_media_height)/2,
                        m_media_width, m_media_height,
                        hMemDC, 0, m_media_height,
                        m_media_width, -((signed)m_media_height), SRCCOPY);

        DeleteDC(hMemDC);
    }

    return true;
}

