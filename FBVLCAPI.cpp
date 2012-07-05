/**********************************************************\

  Auto-generated FBVLCAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "FBVLCAPI.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn FBVLCPtr FBVLCAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
FBVLCPtr FBVLCAPI::getPlugin()
{
    FBVLCPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read-only property version
std::string FBVLCAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

void FBVLCAPI::play(const std::string& mrl)
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.clear_items();

    int item = p.add_item(mrl.c_str(), 0, 0);
    if( item >= 0) {
        p.play(item);
    }
}

void FBVLCAPI::togglePause()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    if ( p.is_playing() ) p.pause();
    else p.play();
}

void FBVLCAPI::stop()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.stop();
    p.clear_items();
}

void FBVLCAPI::toggleMute()
{
    FBVLCPtr plg = getPlugin();
    vlc_player& p = plg->get_player();

    p.toggle_mute();
}

std::string FBVLCAPI::get_bgcolor()
{
    FBVLCPtr plg = getPlugin();
    vlc_player_options& o = plg->get_options();

    return o.get_bg_color();
}

void FBVLCAPI::set_bgcolor(const std::string& bg)
{
    FBVLCPtr plg = getPlugin();
    vlc_player_options& o = plg->get_options();

    o.set_bg_color(bg);
}
