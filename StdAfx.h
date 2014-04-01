#pragma once

#include <string>
#include <string>
#include <sstream>

#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>

#include "PluginCore.h"
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "PluginWindow.h"
#include "PluginEvents/MouseEvents.h"
#include "PluginEvents/AttachedEvent.h"
#include "PluginEvents/DrawingEvents.h"

#if defined(FB_WIN)
#include "PluginWindowWin.h"
#include "PluginWindowlessWin.h"
#endif

#include <vlc/vlc.h>

#include "libvlc_wrapper/vlc_player.h"

#ifdef FB_WIN
#define NOMINMAX
#include <windows.h>
#endif
