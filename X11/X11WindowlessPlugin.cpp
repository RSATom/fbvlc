#define MOZ_X11 1
#include "X11WindowlessPlugin.h"

#include "X11.h"

#include <PluginCore.h>
#include <PluginEvents/DrawingEvents.h>

#include "X11ExposeEvent.h"
#include "X11WindowlessWindow.h"

X11WindowlessPlugin::X11WindowlessPlugin( const FB::Npapi::NpapiBrowserHostPtr& host,
                                          const std::string& mimetype )
    : FB::Npapi::NpapiPluginX11( host, mimetype ), m_npWindow( 0 )
{
}

X11WindowlessPlugin::~X11WindowlessPlugin()
{
}

NPError X11WindowlessPlugin::SetWindow( NPWindow* window )
{
    if( !pluginMain->isWindowless() )
        return FB::Npapi::NpapiPluginX11::SetWindow( window );

    if( !window || window != m_npWindow ) {
        if( m_pluginWindow ) {
            pluginMain->ClearWindow();
            m_pluginWindow.reset();
        }
        m_npWindow = window;
    }

    if( !window )
        return NPERR_NO_ERROR;

    if( !m_pluginWindow ) {
        NPSetWindowCallbackStruct* cs =
            reinterpret_cast<NPSetWindowCallbackStruct*>( window->ws_info );
        if( !cs->display || !cs->colormap )
            return NPERR_NO_ERROR;

        Window browserWindow;
        if( NPERR_NO_ERROR != m_npHost->GetValue( NPNVnetscapeWindow,
                                                  (void*)&browserWindow ) )
        {
            return NPERR_GENERIC_ERROR;
        }

        m_pluginWindow.reset( new X11WindowlessWindow( m_npHost,
                                                       cs->display,
                                                       cs->colormap,
                                                       browserWindow ) );

        pluginMain->SetWindow( m_pluginWindow.get() );
    }

    if( m_pluginWindow ) {
        const FB::Rect windowRect =
            makeRect( window->x, window->y,
                      window->width, window->height );
        m_pluginWindow->setWindowPosition( windowRect );

        FB::Rect clipRect = { window->clipRect.top, window->clipRect.left,
                              window->clipRect.bottom, window->clipRect.right };
        m_pluginWindow->setWindowClipping( clipRect );
    }

    return NPERR_NO_ERROR;
}

int16_t X11WindowlessPlugin::HandleEvent( void* event )
{
    if( !pluginMain->isWindowless() )
        return FB::Npapi::NpapiPluginX11::HandleEvent( event );

    if( !m_pluginWindow )
        return 0;

    XEvent* xEvent = reinterpret_cast<XEvent*>( event );
    switch( xEvent->type ) {
        case GraphicsExpose: {
            XGraphicsExposeEvent& exposeEvent = xEvent->xgraphicsexpose;
            FB::Rect boundsRect =
                makeRect( exposeEvent.x, exposeEvent.y,
                          exposeEvent.width, exposeEvent.height );

            X11ExposeEvent pluginEvent( exposeEvent.display,
                                        exposeEvent.drawable,
                                        boundsRect );
            m_pluginWindow->SendEvent( &pluginEvent );
            break;
        }
    }

    return 0;
}
