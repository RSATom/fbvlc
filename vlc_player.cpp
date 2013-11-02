#include "vlc_player.h"

#include <boost/thread/locks.hpp>
#include <boost/thread/thread.hpp>

using namespace vlc;

player::player()
    : _libvlc_instance(0),
      _video(_player), _audio(_player), _current_media(_player),
      _mode( mode_normal ), _current_idx(-1)
{
}

player::~player()
{
    close();
}

void player::libvlc_event_proxy( const struct libvlc_event_t* event, void* user_data )
{
    static_cast<player*>(user_data)->libvlc_event(event);
}

void player::libvlc_event( const struct libvlc_event_t* event )
{
    //come from another thread
    if( libvlc_MediaPlayerEndReached == event->type ||
        libvlc_MediaPlayerEncounteredError == event->type )
    {
        //to avoid deadlock we should execute commands on another thread
        boost::thread th( boost::bind(&player::next, this) );
    }
}

bool player::open( libvlc_instance_t* inst )
{
    _libvlc_instance = inst;
    if( _player.open( inst ) ) {
        libvlc_event_manager_t* em = libvlc_media_player_event_manager( _player.get_mp() );

        libvlc_event_attach( em, libvlc_MediaPlayerEndReached, libvlc_event_proxy, this );
        libvlc_event_attach( em, libvlc_MediaPlayerEncounteredError, libvlc_event_proxy, this );

        return true;
    }
    return false;
}

void player::close()
{
    _player.close();
    clear_items();
    _libvlc_instance = 0;
}

int player::add_media( const char * mrl_or_path,
                       unsigned optc, const char **optv,
                       unsigned trusted_optc, const char **trusted_optv,
                       bool is_path /*= false*/ )
{
    if( !is_open() )
        return -1;

    libvlc_media_t* media = is_path ?
                            libvlc_media_new_path(_libvlc_instance, mrl_or_path) :
                            libvlc_media_new_location(_libvlc_instance, mrl_or_path);

    if( !media )
        return -1;

    unsigned i;
    for( i = 0; i < optc; ++i )
        libvlc_media_add_option_flag(media, optv[i], libvlc_media_option_unique);

    for( i = 0; i < trusted_optc; ++i )
        libvlc_media_add_option_flag( media, trusted_optv[i],
                                      libvlc_media_option_unique | libvlc_media_option_trusted );

    boost::lock_guard<mutex_t> lock( _playlist_guard );
    playlist_item item = { media };
    playlist_it it = _playlist.insert( _playlist.end(), item );

    return it - _playlist.begin();
}

bool player::delete_item( unsigned idx )
{
    boost::lock_guard<mutex_t> lock( _playlist_guard );

    unsigned sz = _playlist.size();
    assert( _current_idx < static_cast<int>( sz ) );

    if( sz && idx < sz ) {
        if( _current_idx > static_cast<int>( idx ) ||
            ( _current_idx == idx && (sz - 1) == _current_idx ) )
        {
            --_current_idx;
        }

        if( idx < sz ) {
            playlist_cit it = ( _playlist.begin() + idx );
            libvlc_media_release( it->media );
            _playlist.erase( it );
            return true;
        }
    }

    return false;
}

void player::clear_items()
{
    boost::lock_guard<mutex_t> lock( _playlist_guard );

    playlist_it it = _playlist.begin();
    playlist_it end_it = _playlist.end();
    for( ; it != end_it; ++it ) {
        libvlc_media_release( it->media );
        it->media = 0;
    }

    _playlist.clear();

    _current_idx = -1;
}

int player::current_item()
{
    boost::lock_guard<mutex_t> lock( _playlist_guard );

    return _current_idx;
}

int player::item_count()
{
    boost::lock_guard<mutex_t> lock( _playlist_guard );

    return _playlist.size();
}

void player::set_current( unsigned idx )
{
    boost::lock_guard<mutex_t> lock( _playlist_guard );

    if( idx < _playlist.size() ) {
        _current_idx = idx;
        _player.set_media( _playlist[_current_idx].media );
        on_player_action( pa_current_changed );
    }
}

void player::play()
{
    boost::lock_guard<mutex_t> lock( _playlist_guard );

    if( _playlist.empty() && _player.current_media() )
        //special case for empty playlist
        _player.play();
    else
        internalPlay( _current_idx );
}

void player::internalPlay( int idx )
{
    if( _playlist.empty() )
        return;

    if( idx < 0 || static_cast<unsigned>( idx ) > ( _playlist.size() - 1 ) )
        idx = 0;

    if( _player.current_media() != _playlist[idx].media )
        set_current( idx );

    _player.play();

    on_player_action( pa_play );
}

bool player::play( unsigned idx )
{
    boost::lock_guard<mutex_t> lock( _playlist_guard );

    if( idx < _playlist.size() ) {
        internalPlay( idx );
        return true;
    }

    return false;
}

void player::pause()
{
    _player.pause();

    on_player_action( pa_pause );
}

void player::stop()
{
    _player.stop();

    on_player_action( pa_stop );
}

void player::prev()
{
    boost::lock_guard<mutex_t> lock( _playlist_guard );

    unsigned sz = _playlist.size();
    assert( _current_idx < static_cast<int>( sz ) );

    if( !sz )
        return;

    if( _current_idx <= 0 ) {
        if( mode_loop == _mode )
            internalPlay( sz - 1 );
    } else
        internalPlay( _current_idx - 1 );
}

bool player::try_expand_current()
{
    //_playlist_guard should be locked before

    assert( _current_idx < static_cast<int>( _playlist.size() ) );

    libvlc_media_t* media = _playlist[_current_idx].media;
    if( !media )
        return false;

    libvlc_media_list_t* sub_items = libvlc_media_subitems( media );
    if( !sub_items )
        return false;

    libvlc_media_list_lock( sub_items );

    int sub_items_count = libvlc_media_list_count( sub_items );
    unsigned items_added = 0;

    playlist_cit insert_before_it = _playlist.begin() + _current_idx + 1;
    for( int i = 0; i < sub_items_count; ++i ) {
        libvlc_media_t* sub_item = libvlc_media_list_item_at_index( sub_items, i );
        if( sub_item ) {
            playlist_item item = { sub_item };
            insert_before_it = _playlist.insert( insert_before_it, item ) + 1;
            ++items_added;
        }
    }

    libvlc_media_list_unlock( sub_items );

    libvlc_media_list_release( sub_items );

    if( items_added ) {
        _playlist.erase( _playlist.begin() + _current_idx );
        libvlc_media_release( media );
        return true;
    }

    return false;
}

void player::next()
{
    boost::lock_guard<mutex_t> lock( _playlist_guard );

    bool expanded = try_expand_current();

    unsigned sz = _playlist.size();
    assert( _current_idx < static_cast<int>( sz ) );

    if( !sz )
        return;

    if( expanded )
        internalPlay( _current_idx );
    else if( sz - 1 == _current_idx || _current_idx < 0 ) {
        if( mode_loop == _mode )
            internalPlay( 0 );
    } else
        internalPlay( _current_idx + 1 );
}

float player::get_rate()
{
    if( !_player.is_open() )
        return 1.f;

    return libvlc_media_player_get_rate( _player.get_mp() );
}

void player::set_rate( float rate )
{
    if( !_player.is_open() )
        return;

    libvlc_media_player_set_rate( _player.get_mp(), rate );
}

float player::get_position()
{
    if( !is_open() )
        return 0.f;

    float p = libvlc_media_player_get_position( _player.get_mp() );

    return p < 0 ? 0 : p;
}

void player::set_position(float p)
{
    if( !is_open() )
        return;

    libvlc_media_player_set_position( _player.get_mp(), p );
}

libvlc_time_t player::get_time()
{
    if( !is_open() )
        return 0;

    libvlc_time_t t = libvlc_media_player_get_time( _player.get_mp() );

    return t < 0 ? 0 : t ;
}

void player::set_time(libvlc_time_t t)
{
    if( !is_open() )
        return;

    libvlc_media_player_set_time( _player.get_mp(), t );
}
