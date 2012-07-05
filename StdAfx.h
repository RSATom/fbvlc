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
#include "PluginWindowWin.h"
#include "PluginWindowlessWin.h"
#include "PluginEvents/MouseEvents.h"
#include "PluginEvents/AttachedEvent.h"
#include "PluginEvents/DrawingEvents.h"

#include <vlc/vlc.h>

#include "vlc_player.h"

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif
