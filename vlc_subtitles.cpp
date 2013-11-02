#include "vlc_subtitles.h"

#include "vlc_helpers.h"

using namespace vlc;

unsigned subtitles::track_count()
{
    if( _player.is_open() )
        return libvlc_video_get_spu_count( _player.get_mp() );

    return 0;
}

int subtitles::get_track()
{
    if( !_player.is_open() )
        return -1;

    int track_idx = -1;
    libvlc_track_description_t* tracks =
        libvlc_video_get_spu_description( _player.get_mp() );

    if( tracks ) {
        track_idx = track_id_2_track_idx( tracks, libvlc_video_get_spu( _player.get_mp() ) );

        libvlc_free( tracks );
    }

    return track_idx;
}

void subtitles::set_track( unsigned idx )
{
    if( !_player.is_open() )
        return;

    libvlc_track_description_t* tracks =
        libvlc_video_get_spu_description( _player.get_mp() );

    if( tracks ) {
        int id = track_idx_2_track_id( tracks, idx );
        if( id >= 0)
            libvlc_video_set_spu( _player.get_mp(), id );

        libvlc_free( tracks );
    }
}

int64_t subtitles::get_delay()
{
    if( !_player.is_open() )
        return 0;

    return libvlc_video_get_spu_delay( _player.get_mp() );
}

void subtitles::set_delay( int64_t d )
{
    if( !_player.is_open() )
        return;

    libvlc_video_set_spu_delay( _player.get_mp(), d );
}
