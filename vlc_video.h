#pragma once

#include "vlc_basic_player.h"

namespace vlc
{
    class video
    {
    public:
        video(vlc::basic_player& player)
            : _player( player ) {};

        unsigned track_count();

        unsigned get_track();
        void set_track( unsigned idx );

        bool has_vout();

        float get_contrast()
            { return get_ajust_filter_var( libvlc_adjust_Contrast, 1.0f ); }
        void set_contrast(float val)
            { set_ajust_filter_var( libvlc_adjust_Contrast, val ); }

        float get_brightness()
            { return get_ajust_filter_var( libvlc_adjust_Brightness, 1.0f ); }
        void set_brightness(float val)
            { set_ajust_filter_var( libvlc_adjust_Brightness, val ); }

        float get_hue()
            { return get_ajust_filter_var( libvlc_adjust_Hue, .0f ); }
        void set_hue(float val)
            { set_ajust_filter_var( libvlc_adjust_Hue, val ); }

        float get_saturation()
            { return get_ajust_filter_var( libvlc_adjust_Saturation, 1.0f ); }
        void set_saturation(float val)
            { set_ajust_filter_var( libvlc_adjust_Saturation, val ); }

        float get_gamma()
            { return get_ajust_filter_var( libvlc_adjust_Gamma, 1.0f ); }
        void set_gamma(float val)
            { set_ajust_filter_var( libvlc_adjust_Gamma, val ); }

    private:
        float get_ajust_filter_var( libvlc_video_adjust_option_t option, float def_v );
        void set_ajust_filter_var( libvlc_video_adjust_option_t option, float val );

    private:
        vlc::basic_player& _player;
    };
};
