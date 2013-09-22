#pragma once

#include <vlc/vlc.h>

namespace vlc
{
    class basic_player
    {
    public:
        basic_player();
        ~basic_player();

        bool open(libvlc_instance_t* inst);
        void close();

        bool is_open() const { return _mp != 0; }

        void play();
        void pause();
        void stop();

        void set_media( libvlc_media_t* );

        libvlc_media_t* current_media();

        libvlc_state_t get_state();

        bool is_playing() { return libvlc_Playing == get_state(); };
        bool is_paused() { return libvlc_Paused == get_state(); };
        bool is_stopped() { return libvlc_Stopped == get_state(); }

        libvlc_media_player_t* get_mp() const
            { return _mp; }

    private:
        libvlc_instance_t*     _libvlc_instance;
        libvlc_media_player_t* _mp;
    };
};
