#pragma once

#include "vlc_basic_player.h"

namespace vlc
{
    class audio
    {
    public:
        audio(vlc::basic_player& player)
            : _player( player ) {};

        bool is_muted();
        void toggle_mute();
        void set_mute(bool);

        unsigned get_volume();
        void set_volume( unsigned );

        unsigned track_count();
        //can return -1 if there is no active audio track
        int get_track();
        void set_track( unsigned );

        libvlc_audio_output_channel_t get_channel();
        void set_channel(libvlc_audio_output_channel_t);

    private:
        vlc::basic_player& _player;
    };
};
