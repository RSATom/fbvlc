#include "vlc_video.h"

using namespace vlc;

bool video::has_vout()
{
    if( !_player.is_open() )
        return false;

    return libvlc_media_player_has_vout( _player.get_mp() ) > 0;
}

float video::get_ajust_filter_var( libvlc_video_adjust_option_t option,
                                   float def_v )
{
    if( _player.is_open() ) {
        return libvlc_video_get_adjust_float( _player.get_mp(), option );
    }
    else return def_v;
}

void video::set_ajust_filter_var( libvlc_video_adjust_option_t option, float val )
{
    if( _player.is_open() ) {
        libvlc_video_set_adjust_float( _player.get_mp(), option, val );
    }
}
