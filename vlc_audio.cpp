#include "vlc_audio.h"

#include "vlc_helpers.h"

using namespace vlc;

bool audio::is_muted()
{
    if( !_player.is_open() )
        return false;

    return libvlc_audio_get_mute( _player.get_mp() ) != 0;
}

void audio::toggle_mute()
{
    if( _player.is_open() )
        libvlc_audio_toggle_mute( _player.get_mp() );
}

void audio::set_mute(bool mute)
{
    if( _player.is_open() )
        libvlc_audio_set_mute( _player.get_mp(), mute );
}

unsigned audio::get_volume()
{
    if( !_player.is_open() )
        return 0;

    int v = libvlc_audio_get_volume( _player.get_mp() );

    return v < 0 ? 0 : v;
}

void audio::set_volume( unsigned volume )
{
    if( _player.is_open() )
        libvlc_audio_set_volume( _player.get_mp() , volume );
}

unsigned audio::track_count()
{
    if( !_player.is_open() )
        return 0;

    int tc = libvlc_audio_get_track_count( _player.get_mp() );

    return tc < 0 ? 0 : tc ;
}

int audio::get_track()
{
    if( !_player.is_open() )
        return -1;

    int track_idx = -1;
    libvlc_track_description_t* tracks =
        libvlc_audio_get_track_description( _player.get_mp() );

    if( tracks ) {
        track_idx = track_id_2_track_idx( tracks, libvlc_audio_get_track( _player.get_mp() ) );

        libvlc_free( tracks );
    }

    return track_idx;
}

void audio::set_track( unsigned idx )
{
    if( !_player.is_open() )
        return;

    libvlc_track_description_t* tracks =
        libvlc_audio_get_track_description( _player.get_mp() );

    if( tracks ) {
        int id = track_idx_2_track_id( tracks, idx );
        if( id >= 0 )
            libvlc_audio_set_track( _player.get_mp(), id );

        libvlc_free( tracks );
    }
}

libvlc_audio_output_channel_t audio::get_channel()
{
    if( !_player.is_open() )
        return libvlc_AudioChannel_Error;

    return (libvlc_audio_output_channel_t) libvlc_audio_get_channel( _player.get_mp() );
}

void audio::set_channel(libvlc_audio_output_channel_t channel)
{
    if( _player.is_open() )
        libvlc_audio_set_channel( _player.get_mp(), channel );
}
