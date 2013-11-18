#include "vlc_basic_player.h"

#include <boost/thread/thread.hpp>

using namespace vlc;

basic_player::basic_player()
    : _libvlc_instance(0), _mp(0)
{
}

basic_player::~basic_player()
{
    close();
}

libvlc_state_t basic_player::get_state()
{
    if( !is_open() )
        return libvlc_NothingSpecial;

    return libvlc_media_player_get_state( _mp );
}

bool basic_player::open(libvlc_instance_t* inst)
{
    if( !inst )
        return false;

    if( is_open() )
        close();

    _libvlc_instance = inst;
    _mp = libvlc_media_player_new( inst );

    return 0 != _mp;
}

void basic_player::close()
{
    if(_mp) {
        libvlc_media_player_release( _mp );
        _mp = 0;
    }

    _libvlc_instance = 0;
}

void basic_player::play()
{
    if( is_open() )
        libvlc_media_player_play( _mp );
}

void basic_player::pause()
{
    if( is_open() )
        libvlc_media_player_set_pause( _mp, true );
}

void basic_player::stop( bool async /*= false*/ )
{
    if( !is_open() )
        return;

    if( async )
        boost::thread( boost::bind( libvlc_media_player_stop, _mp ) );
    else
        libvlc_media_player_stop( _mp );
}

libvlc_media_t* basic_player::current_media()
{
    if( is_open() )
        return libvlc_media_player_get_media( _mp );
    else
        return 0;
}

void basic_player::set_media( libvlc_media_t* media )
{
    if( is_open() )
        return libvlc_media_player_set_media( _mp, media );
}
