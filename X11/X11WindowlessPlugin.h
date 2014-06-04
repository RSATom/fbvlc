#pragma once

#include <X11/NpapiPluginX11.h>

class X11WindowlessWindow; //#include "X11WindowlessWindow.h"

class X11WindowlessPlugin :
    public FB::Npapi::NpapiPluginX11
{
public:
    X11WindowlessPlugin( const FB::Npapi::NpapiBrowserHostPtr& host,
                         const std::string& mimetype );
    ~X11WindowlessPlugin();

    virtual NPError SetWindow( NPWindow* );
    virtual int16_t HandleEvent( void* event );

private:
    NPWindow* m_npWindow;
    boost::scoped_ptr<X11WindowlessWindow> m_pluginWindow;
};
