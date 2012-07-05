/*****************************************************************************
 * Copyright © 2002-2011 VideoLAN and VLC authors
 * $Id$
 *
 * Authors: Sergey Radionov <rsatom_gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#pragma once

#include <vlc/vlc.h>

enum vlc_player_action_e
{
    pa_play,
    pa_pause,
    pa_stop,
    pa_next,
    pa_prev
};

class vlc_player
{
public:
    vlc_player();
    ~vlc_player(void);

    bool open(libvlc_instance_t* inst);
    void close();

    bool is_open() const { return _ml_p != 0; }
    bool is_playing();
    libvlc_state_t get_state();
    bool is_stopped() { return libvlc_Stopped == get_state(); }

    int add_item(const char * mrl, unsigned int optc, const char **optv);
    int add_item(const char * mrl)
        { return add_item(mrl, 0, 0); }

    int  current_item();
    int  items_count();
    bool delete_item(unsigned int idx);
    void clear_items();

    void play();
    bool play(unsigned int idx);
    void pause();
    void stop();

    bool next();
    bool prev();

    float get_rate();
    void set_rate(float);

    float get_fps();

    bool has_vout();

    float get_position();
    void  set_position(float);

    libvlc_time_t get_time();
    void set_time(libvlc_time_t);

    libvlc_time_t get_length();

    void set_mode(libvlc_playback_mode_t);

    bool is_muted();
    void toggle_mute();
    void set_mute(bool);

    unsigned int get_volume();
    void set_volume(unsigned int);

    unsigned int track_count();
    unsigned int get_track();
    void set_track(unsigned int);

    unsigned int get_channel();
    void set_channel(unsigned int);

    libvlc_media_player_t* get_mp() const
        { return _mp; }

protected:
    virtual void on_player_action( vlc_player_action_e ){};

private:
    libvlc_instance_t *         _libvlc_instance;
    libvlc_media_player_t*      _mp;
    libvlc_media_list_t*        _ml;
    libvlc_media_list_player_t* _ml_p;
};
