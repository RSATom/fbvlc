#include "vlc_vmem.h"

using namespace vlc;

vmem::vmem( vlc::basic_player& player )
    : _player( player ),
      _desired_width(0), _desired_height(0),
      _media_width(0), _media_height(0)
{
}

unsigned vmem::video_format_cb( char* chroma,
                                unsigned* width, unsigned* height,
                                unsigned* pitches, unsigned* lines )
{
    if ( original_media_width != _desired_width && original_media_height != _desired_height ) {
        float src_aspect = (float)(*width) / (*height);
        float dst_aspect = (float)_desired_width / _desired_height;
        if ( src_aspect > dst_aspect ) {
            if( _desired_width != (*width) ) { //don't scale if size equal
                (*width)  = _desired_width;
                (*height) = static_cast<unsigned>( (*width) / src_aspect + 0.5 );
            }
        }
        else {
            if( _desired_height != (*height) ) { //don't scale if size equal
                (*height) = _desired_height;
                (*width)  = static_cast<unsigned>( (*height) * src_aspect + 0.5 );
            }
        }
    }

    _media_width  = (*width);
    _media_height = (*height);

    memcpy(chroma, DEF_CHROMA, sizeof(DEF_CHROMA)-1);
    (*pitches) = _media_width * DEF_PIXEL_BYTES;
    (*lines)   = _media_height;

    //+1 for vlc 2.0.3/2.1 bug workaround.
    //They writes after buffer end boundary by some reason unknown to me...
    _frame_buf.resize( (*pitches) * ( (*lines) + 1 ) );

    on_frame_setup();

    return 1;
}

void vmem::video_cleanup_cb()
{
    on_frame_cleanup();

    _frame_buf.resize(0);
    _media_width  = 0;
    _media_height = 0;
}

void* vmem::video_lock_cb( void **planes )
{
    (*planes) = _frame_buf.empty()? 0 : &_frame_buf[0];
    return 0;
}

void vmem::video_unlock_cb( void* /*picture*/, void *const * /*planes*/ )
{
}

void vmem::video_display_cb( void * /*picture*/ )
{
    on_frame_ready( _frame_buf );
}

bool vmem::open()
{
    if( !_player.is_open() )
        return false;

    libvlc_video_set_format_callbacks( _player.get_mp(),
                                       video_format_proxy,
                                       video_cleanup_proxy );

    libvlc_video_set_callbacks( _player.get_mp(),
                                video_fb_lock_proxy,
                                video_fb_unlock_proxy,
                                video_fb_display_proxy,
                                this );

    return true;
}

void vmem::close()
{
    if( _player.is_open() ) {
        libvlc_video_set_format_callbacks( _player.get_mp(), NULL, NULL );
        libvlc_video_set_callbacks( _player.get_mp(), NULL, NULL, NULL, this );
    }
}

void vmem::set_desired_size( unsigned width, unsigned height )
{
    _desired_width = width;
    _desired_height = height;
}
