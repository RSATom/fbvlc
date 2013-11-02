#pragma once

#include "vlc_basic_player.h"

namespace vlc
{
    class subtitles
    {
    public:
        subtitles( vlc::basic_player& player )
            : _player( player ) {};

        unsigned track_count();

        //can return -1 if there are no active subtitle
        int get_track();
        void set_track( unsigned );

        int64_t get_delay();
        void set_delay( int64_t );

    private:
        vlc::basic_player& _player;
    };
};
