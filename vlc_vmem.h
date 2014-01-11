#pragma once

#include <vector>

#include "vlc_basic_player.h"

namespace vlc
{
    const char DEF_CHROMA[] = "RV32";
    enum {
        DEF_PIXEL_BYTES = 4,

        original_media_width = 0,
        original_media_height = 0,
    };

    class vmem
    {
    public:
        vmem( vlc::basic_player& player );
        bool open();
        void close();

        //0 - use size same as source have
        void set_desired_size( unsigned width, unsigned height );

        unsigned width() const { return _media_width; }
        unsigned height() const { return _media_height; }
        const std::vector<char>& frame_buf() { return _frame_buf; }

    protected:
        //on_frame_setup/on_frame_ready/on_frame_cleanup will come from worker thread
        virtual void on_frame_setup() {};
        virtual void on_frame_ready( const std::vector<char>& frame_buf ) = 0;
        virtual void on_frame_cleanup() = 0;

    private:
        //for libvlc_video_set_format_callbacks
        static unsigned video_format_proxy( void **opaque, char *chroma,
                                            unsigned *width, unsigned *height,
                                            unsigned *pitches, unsigned *lines )
            { return reinterpret_cast<vmem*>( *opaque )->video_format_cb( chroma,
                                                                          width, height,
                                                                          pitches, lines ); }
        static void video_cleanup_proxy( void *opaque )
            { reinterpret_cast<vmem*>( opaque )->video_cleanup_cb(); };

        unsigned video_format_cb( char *chroma,
                                  unsigned *width, unsigned *height,
                                  unsigned *pitches, unsigned *lines );
        void video_cleanup_cb();
        //end (for libvlc_video_set_format_callbacks)

        //for libvlc_video_set_callbacks
        static void* video_fb_lock_proxy( void *opaque, void **planes )
            { return reinterpret_cast<vmem*>( opaque )->video_lock_cb(planes); }
        static void  video_fb_unlock_proxy( void *opaque, void *picture, void *const *planes )
            { reinterpret_cast<vmem*>( opaque )->video_unlock_cb( picture, planes ); }
        static void  video_fb_display_proxy( void *opaque, void *picture )
            { reinterpret_cast<vmem*>( opaque )->video_display_cb( picture ); }

        void* video_lock_cb( void **planes );
        void  video_unlock_cb( void *picture, void *const *planes );
        void  video_display_cb( void *picture );
        //end (for libvlc_video_set_callbacks)

    private:
        vlc::basic_player& _player;
        std::vector<char>  _frame_buf;
        unsigned           _desired_width;
        unsigned           _desired_height;
        unsigned           _media_width;
        unsigned           _media_height;
    };
};
