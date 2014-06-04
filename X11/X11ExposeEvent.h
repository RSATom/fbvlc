#pragma once

#include "X11.h"

#include <PluginEvents/DrawingEvents.h>

class X11ExposeEvent : public FB::RefreshEvent
{
public:
    X11ExposeEvent( Display* display, Drawable drawable, const FB::Rect& bounds )
        : RefreshEvent( bounds ), display( display ), drawable( drawable ) {}
public:
    Display *const display;
    const Drawable drawable;
};
