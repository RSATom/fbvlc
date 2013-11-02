#include "vlc_video.h"

#include "vlc_helpers.h"

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

unsigned video::track_count()
{
    if( !_player.is_open() )
        return 0;

    int count = libvlc_video_get_track_count( _player.get_mp() );
    return count < 0 ? 0 : count;
}

int video::get_track()
{
    if( !_player.is_open() )
        return -1;

    int track_idx = -1;
    libvlc_track_description_t* tracks =
        libvlc_video_get_track_description( _player.get_mp() );

    if( tracks ) {
        track_idx = track_id_2_track_idx( tracks, libvlc_video_get_track( _player.get_mp() ) );

        libvlc_free( tracks );
    }

    return track_idx;
}

void video::set_track( unsigned idx )
{
    if( !_player.is_open() )
        return;

    libvlc_track_description_t* tracks =
        libvlc_video_get_track_description( _player.get_mp() );

    if( tracks ) {
        int id = track_idx_2_track_id( tracks, idx );
        if( id >= 0)
            libvlc_video_set_track( _player.get_mp(), id );

        libvlc_free( tracks );
    }
}
