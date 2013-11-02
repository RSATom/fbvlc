#include "vlc_helpers.h"

int vlc::track_idx_2_track_id( const libvlc_track_description_t *const tracks, int idx )
{
    if( tracks && idx >= 0) {
        const libvlc_track_description_t* t = tracks;
        for( ; t && idx; --idx, t = t->p_next );
        if( t )
            return t->i_id;
    }

    return -1;
}

int vlc::track_id_2_track_idx( const libvlc_track_description_t *const tracks, int id )
{
    if( tracks && id >= 0) {
        const libvlc_track_description_t* t = tracks;
        for( unsigned idx = 0; t; ++idx, t = t->p_next ) {
            if( t->i_id == id )
                return idx;
        }
    }

    return -1;
}
