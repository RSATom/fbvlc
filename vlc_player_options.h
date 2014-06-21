/*****************************************************************************
 * Copyright � 2002-2011 VideoLAN and VLC authors
 * $Id$
 *
 * Authors: Sergey Radionov <rsatom_gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef _VLC_PLAYER_OPTIONS_H_
#define _VLC_PLAYER_OPTIONS_H_

#include <string>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#endif

bool HtmlColor2RGB( const std::string& HtmlColor,
                    uint8_t* r, uint8_t* g, uint8_t* b );

#ifdef _WIN32
inline COLORREF HtmlColor2RGB( const std::string& HtmlColor,
                               COLORREF DefColor )
{
    uint8_t r, g, b; r = g = b = 0;

    if( !HtmlColor2RGB( HtmlColor, &r, &g, &b ) )
        return DefColor;

    return RGB( r, g, b );
}
#endif

enum vlc_player_option_e
{
    po_autoplay,
    po_show_toolbar,
    po_show_fs_toolbar,
    po_enable_fullscreen,
    po_bg_text,
    po_bg_color,
    po_native_scaling,
    po_use_proxy
};

class vlc_player_options
{
public:
    vlc_player_options()
        : _autoplay( true ), _show_toolbar( true ),
          _show_fs_toolbar( true ), _enable_fullscreen( true ),
          _native_scaling( false ), _use_proxy( true ), _bg_color( /*black*/"#000000" )
    {}

    void set_autoplay( bool ap ) {
        _autoplay = ap;
        on_option_change( po_autoplay );
    }
    bool get_autoplay() const
        { return _autoplay; }

    void set_show_toolbar( bool st ) {
        _show_toolbar = st;
        on_option_change( po_show_toolbar );
    }
    bool get_show_toolbar() const
        { return _show_toolbar; }

    void set_show_fs_toolbar( bool st ) {
        _show_fs_toolbar = st;
        on_option_change( po_show_fs_toolbar );
    }
    bool get_show_fs_toolbar() const
        { return _show_fs_toolbar; }

    void set_enable_fs( bool ef ) {
        _enable_fullscreen = ef;
        on_option_change( po_enable_fullscreen );
    }
    bool get_enable_fs() const
        { return _enable_fullscreen; }

    void set_bg_text( const std::string& bt ) {
        _bg_text = bt;
        on_option_change( po_bg_text );
    }
    const std::string& get_bg_text() const {
        return _bg_text;
    }

    void set_bg_color( const std::string& bc ) {
        _bg_color = bc;
        on_option_change( po_bg_color );
    }
    const std::string& get_bg_color() const {
        return _bg_color;
    }

    void set_native_scaling( bool s ) {
        _native_scaling = s;
        on_option_change( po_native_scaling );
    }
    bool get_native_scaling() const
        { return _native_scaling; }

    void set_use_proxy( bool up ) {
        _use_proxy = up;
        on_option_change( po_use_proxy );
    }
    bool get_use_proxy() const
        { return _use_proxy; }

protected:
    virtual void on_option_change( vlc_player_option_e ) {};

private:
    bool         _autoplay;
    bool         _show_toolbar;
    bool         _show_fs_toolbar;
    bool         _enable_fullscreen;
    bool         _native_scaling;
    bool         _use_proxy;
    std::string  _bg_text;
    //background color format is "#rrggbb"
    std::string  _bg_color;
};

#endif //_VLC_PLAYER_OPTIONS_H_
