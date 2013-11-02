#include "vlc_audio.h"

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

unsigned int audio::get_track()
{
    if( !_player.is_open() )
        return 0;

    int t = libvlc_audio_get_track( _player.get_mp() );

    return t < 0 ? 0 : t ;
}

void audio::set_track(unsigned int track)
{
    if( _player.is_open() )
        libvlc_audio_set_track( _player.get_mp(), track );
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
