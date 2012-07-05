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

#include "vlc_player.h"

vlc_player::vlc_player()
    :_libvlc_instance(0), _ml(0), _mp(0), _ml_p(0)
{
}

vlc_player::~vlc_player(void)
{
    close();
}

bool vlc_player::open(libvlc_instance_t* inst)
{
    if( !inst )
        return false;

    if( is_open() )
        close();

    _libvlc_instance = inst;

    _mp   = libvlc_media_player_new(inst);
    _ml   = libvlc_media_list_new(inst);
    _ml_p = libvlc_media_list_player_new(inst);

    if( _mp && _ml && _ml_p ) {
        libvlc_media_list_player_set_media_list(_ml_p, _ml);
        libvlc_media_list_player_set_media_player(_ml_p, _mp);
    }
    else{
        close();
        return false;
    }

    return true;
}

bool vlc_player::is_playing()
{
    return _ml_p && libvlc_media_list_player_is_playing(_ml_p) != 0;
}

libvlc_state_t vlc_player::get_state()
{
    if( !is_open() )
        return libvlc_NothingSpecial;

    return libvlc_media_list_player_get_state(_ml_p);
}

void vlc_player::close()
{
    if(_ml_p) {
        libvlc_media_list_player_release(_ml_p);
        _ml_p = 0;
    }

    if(_ml) {
        libvlc_media_list_release(_ml);
        _ml = 0;
    }

    if(_mp) {
        libvlc_media_player_release(_mp);
        _mp = 0;
    }

    _libvlc_instance = 0;
}

int vlc_player::add_item(const char * mrl, unsigned int optc, const char **optv)
{
    if( !is_open() )
        return -1;

    int item = -1;

    libvlc_media_t* media = libvlc_media_new_location(_libvlc_instance, mrl);
    if( !media )
        return -1;

    for( unsigned int i = 0; i < optc; ++i )
        libvlc_media_add_option_flag(media, optv[i], libvlc_media_option_unique);

    libvlc_media_list_lock(_ml);
    if( 0 == libvlc_media_list_add_media(_ml, media) )
         item = libvlc_media_list_count(_ml) - 1;
    libvlc_media_list_unlock(_ml);

    libvlc_media_release(media);

    return item;
}

int vlc_player::current_item()
{
    if( !is_open() )
        return -1;

    libvlc_media_t* media = libvlc_media_player_get_media(_mp);

    if( !media )
        return -1;

    return libvlc_media_list_index_of_item(_ml, media);
}

int vlc_player::items_count()
{
    if( !is_open() )
        return 0;

    libvlc_media_list_lock(_ml);
    int icnt = libvlc_media_list_count(_ml);
    libvlc_media_list_unlock(_ml);
    return icnt;
}

bool vlc_player::delete_item(unsigned int idx)
{
    if( !is_open() )
        return false;

    libvlc_media_list_lock(_ml);
    bool ret = libvlc_media_list_remove_index(_ml, idx) == 0;
    libvlc_media_list_unlock(_ml);

    return ret;
}

void vlc_player::clear_items()
{
    if( !is_open() )
        return;

    libvlc_media_list_lock(_ml);
    for( int i = libvlc_media_list_count(_ml); i > 0; --i) {
        libvlc_media_list_remove_index(_ml, i - 1);
    }
    libvlc_media_list_unlock(_ml);
}

void vlc_player::play()
{
    if( !is_open() )
        return;

    libvlc_media_list_player_play(_ml_p);
    on_player_action(pa_play);
}

bool vlc_player::play(unsigned int idx)
{
    if( !is_open() )
        return false;

    const int r = libvlc_media_list_player_play_item_at_index(_ml_p, idx);
    if( 0 == r ) {
        on_player_action(pa_play);
        return true;
    }

    return false;
}

void vlc_player::pause()
{
    if( is_open() ) {
        libvlc_media_list_player_pause(_ml_p);
        on_player_action(pa_pause);
    }
}

void vlc_player::stop()
{
    if( is_open() ){
        libvlc_media_list_player_stop(_ml_p);
        on_player_action(pa_stop);
    }
}

bool vlc_player::next()
{
    if( !is_open() )
        return false;

    const int r = libvlc_media_list_player_next(_ml_p);
    if( 0 == r ) {
        on_player_action(pa_next);
        return true;
    }

    return false;
}

bool vlc_player::prev()
{
    if( !is_open() )
        return false;

    const int r = libvlc_media_list_player_previous(_ml_p);
    if( 0 == r ) {
        on_player_action(pa_prev);
        return true;
    }

    return false;
}

float vlc_player::get_rate()
{
    if( !is_open() )
        return 1.f;

    return libvlc_media_player_get_rate(_mp);
}

void vlc_player::set_rate(float rate)
{
    if( !is_open() )
        return;

    libvlc_media_player_set_rate(_mp, rate);
}

float vlc_player::get_fps()
{
    if( !is_open() )
        return 0;

    return libvlc_media_player_get_fps(_mp);
}

bool vlc_player::has_vout()
{
    if( !is_open() )
        return false;

    return libvlc_media_player_has_vout(_mp) > 0;
}

float vlc_player::get_position()
{
    if( !is_open() )
        return 0.f;

    float p = libvlc_media_player_get_position(_mp);

    return p<0 ? 0 : p;
}

void vlc_player::set_position(float p)
{
    if( !is_open() )
        return;

    libvlc_media_player_set_position(_mp, p);
}

libvlc_time_t vlc_player::get_time()
{
    if( !is_open() )
        return 0;

    libvlc_time_t t = libvlc_media_player_get_time(_mp);

    return t<0 ? 0 : t ;
}

void vlc_player::set_time(libvlc_time_t t)
{
    if( !is_open() )
        return;

    libvlc_media_player_set_time(_mp, t);
}

libvlc_time_t vlc_player::get_length()
{
    if( !is_open() )
        return 0;

    libvlc_time_t t = libvlc_media_player_get_length(_mp);

    return t<0 ? 0 : t ;
}

void vlc_player::set_mode(libvlc_playback_mode_t mode)
{
    if( is_open() )
        libvlc_media_list_player_set_playback_mode(_ml_p, mode);
}

bool vlc_player::is_muted()
{
    if( !is_open() )
        return false;

    return libvlc_audio_get_mute(_mp) != 0;
}

void vlc_player::toggle_mute()
{
    if( is_open() )
        libvlc_audio_toggle_mute(_mp);
}

void vlc_player::set_mute(bool mute)
{
    if( is_open() )
        libvlc_audio_set_mute(_mp, mute);
}

unsigned int vlc_player::get_volume()
{
    if( !is_open() )
        return 0;

    int v = libvlc_audio_get_volume(_mp);

    return v<0 ? 0 : v;
}

void vlc_player::set_volume(unsigned int volume)
{
    if( is_open() )
        libvlc_audio_set_volume(_mp, volume);
}

unsigned int vlc_player::track_count()
{
    if( !is_open() )
        return 0;

    int tc = libvlc_audio_get_track_count(_mp);

    return tc<0 ? 0 : tc ;
}

unsigned int vlc_player::get_track()
{
    if( !is_open() )
        return 0;

    int t = libvlc_audio_get_track(_mp);

    return t<0 ? 0 : t ;
}

void vlc_player::set_track(unsigned int track)
{
    if( is_open() )
        libvlc_audio_set_track(_mp, track);
}

unsigned int vlc_player::get_channel()
{
    if( !is_open() )
        return 0;

    int c =libvlc_audio_get_channel(_mp);

    return c<0 ? 0 : c ;
}

void vlc_player::set_channel(unsigned int channel)
{
    if( is_open() )
        libvlc_audio_set_channel(_mp, channel);
}
