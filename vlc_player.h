#pragma once

//include stdint.h before boost to avoid conflicts
#include <stdint.h>

#include <deque>
#include <boost/thread/recursive_mutex.hpp>

#include "vlc_basic_player.h"
#include "vlc_audio.h"
#include "vlc_video.h"
#include "vlc_current_media.h"

namespace vlc
{
    enum player_action_e
    {
        pa_play,
        pa_pause,
        pa_stop,
        pa_current_changed,
    };

    enum playback_mode_e
    {
        mode_normal,
        mode_loop,
    };

    class player
    {
    public:
        player();
        ~player();

        bool open(libvlc_instance_t* inst);
        void close();

        bool is_open() const { return _player.is_open(); }

        libvlc_state_t get_state() { return _player.get_state(); };
        bool is_playing() { return libvlc_Playing == get_state(); };

        int add_media( const char * mrl_or_path,
                                   unsigned int optc, const char **optv,
                                   bool is_path = false )
            { return add_media(mrl_or_path, optc, optv, 0, 0, is_path); }
        int add_media( const char * mrl_or_path, bool is_path = false )
            { return add_media(mrl_or_path, 0, 0, is_path); }
        int add_media( const char * mrl_or_path,
                                   unsigned int optc, const char **optv,
                                   unsigned int trusted_optc, const char **trusted_optv,
                                   bool is_path = false );
        bool delete_item( unsigned idx );
        void clear_items();
        int  item_count();

        int  current_item();
        void set_current( unsigned idx );

        void play();
        bool play( unsigned idx );
        void pause();
        void stop();
        void next();
        void prev();

        float get_rate();
        void set_rate( float );

        float get_position();
        void  set_position( float );

        libvlc_time_t get_time();
        void set_time( libvlc_time_t );

        void set_playback_mode( playback_mode_e m )
            { _mode = m; }

        vlc::basic_player& basic_player() { return _player; }
        vlc::video& video() { return _video; }
        vlc::audio& audio() { return _audio; }
        vlc::current_media& current_media() { return _current_media; }

        libvlc_media_player_t* get_mp() const
            { return _player.get_mp(); }

    protected:
        //may come from another thread
        virtual void on_player_action( player_action_e ){};

    private:
        static void libvlc_event_proxy( const struct libvlc_event_t* event, void* user_data);
        void libvlc_event( const struct libvlc_event_t* event );

        bool try_expand_current();

    private:
        struct playlist_item
        {
            libvlc_media_t* media;
        };

        typedef std::deque<playlist_item> playlist_t;
        typedef playlist_t::iterator playlist_it;
        typedef playlist_t::const_iterator playlist_cit;

    private:
        libvlc_instance_t* _libvlc_instance;

        vlc::basic_player  _player;
        vlc::video         _video;
        vlc::audio         _audio;
        vlc::current_media _current_media;

        playback_mode_e    _mode;

        typedef boost::recursive_mutex mutex_t;
        mutex_t    _playlist_guard;
        playlist_t _playlist;
        int        _current_idx;
    };
};

typedef vlc::player vlc_player;
