#include "vlc_current_media.h"

using namespace vlc;

float current_media::get_fps()
{
    if( !_player.is_open() )
        return 0;

    return libvlc_media_player_get_fps( _player.get_mp() );
}

libvlc_time_t current_media::get_length()
{
    if( !_player.is_open() )
        return 0;

    libvlc_time_t t = libvlc_media_player_get_length( _player.get_mp() );

    return t < 0 ? 0 : t ;
}
