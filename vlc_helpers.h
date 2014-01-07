#pragma once

#include <vlc/vlc.h>

namespace vlc
{
    int track_idx_2_track_id( const libvlc_track_description_t *const, int );
    int track_id_2_track_idx( const libvlc_track_description_t *const, int );
};
