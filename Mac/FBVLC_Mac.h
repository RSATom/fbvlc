#ifndef H_FBVLCPLUGIN_MAC
#define H_FBVLCPLUGIN_MAC

#include "../FBVLC.h"

#include "PluginEvents/MacEventCocoa.h"
#include "Mac/PluginWindowMac.h"
#include "Mac/PluginWindowMacCG.h"

////////////////////////////////////////////////////////////////////////////////
//FBVLC_Mac class
////////////////////////////////////////////////////////////////////////////////
FB_FORWARD_PTR(FBVLC_Mac)
class FBVLC_Mac: public FBVLC
{
public:
    FBVLC_Mac();
    virtual ~FBVLC_Mac();

    //mac plugins is always windowless
    virtual bool isWindowless() { return true; }

    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::CoreGraphicsDraw, onCoreGraphicsDraw, FB::PluginWindowMacCG)
        PLUGIN_EVENT_MAP_CASCADE(FBVLC)
    END_PLUGIN_EVENT_MAP()

private:
    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    bool onCoreGraphicsDraw(FB::CoreGraphicsDraw *evt, FB::PluginWindowMacCG*);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/

public:
    virtual bool is_fullscreen() { return false; };
    virtual void set_fullscreen(bool fs) { };
    virtual void toggle_fullscreen() { };

protected:
    virtual void on_option_change(vlc_player_option_e );

private:
    void updateBgComponents();

private:
    CGFloat m_bgComponents[4];
};

#endif//H_FBVLCPLUGIN_MAC
