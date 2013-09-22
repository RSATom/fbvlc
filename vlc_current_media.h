#pragma once

#include "vlc_basic_player.h"

namespace vlc
{
    class current_media
    {
    public:
        current_media(vlc::basic_player& player)
            : _player( player ) {};

        float get_fps();
        libvlc_time_t get_length();

    private:
        vlc::basic_player& _player;
    };
};
