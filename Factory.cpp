/*****************************************************************************
 * Copyright (c) 2012-2014 Sergey Radionov <rsatom_gmail.com>
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

#include "FactoryBase.h"
#include "FBVLC.h"
#include <boost/make_shared.hpp>

#ifdef FB_WIN
#    include "Win/FBVLC_Win.h"
#elif defined FB_X11
#    include "X11/FBVLC_X11.h"
#    include "X11/X11WindowlessPlugin.h"
#elif defined FB_MACOSX
#    include "Mac/FBVLC_Mac.h"
#endif

class PluginFactory : public FB::FactoryBase
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// @fn FB::PluginCorePtr createPlugin(const std::string& mimetype)
    ///
    /// @brief  Creates a plugin object matching the provided mimetype
    ///         If mimetype is empty, returns the default plugin
    ///////////////////////////////////////////////////////////////////////////////
    FB::PluginCorePtr createPlugin(const std::string& mimetype)
    {
#ifdef FB_WIN
        return boost::make_shared<FBVLC_Win>();
#elif defined FB_X11
        return boost::make_shared<FBVLC_X11>();
#elif defined FB_MACOSX
        return boost::make_shared<FBVLC_Mac>();
#endif
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    /// @see FB::FactoryBase::globalPluginInitialize
    ///////////////////////////////////////////////////////////////////////////////
    void globalPluginInitialize()
    {
        FBVLC::StaticInitialize();
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    /// @see FB::FactoryBase::globalPluginDeinitialize
    ///////////////////////////////////////////////////////////////////////////////
    void globalPluginDeinitialize()
    {
        FBVLC::StaticDeinitialize();
    }

#ifdef FB_X11
    FB::Npapi::NpapiPluginPtr createNpapiPlugin( const FB::Npapi::NpapiBrowserHostPtr& host,
                                                 const std::string& mimetype );
#endif
};

///////////////////////////////////////////////////////////////////////////////
/// @fn getFactoryInstance()
///
/// @brief  Returns the factory instance for this plugin module
///////////////////////////////////////////////////////////////////////////////
FB::FactoryBasePtr getFactoryInstance()
{
    static boost::shared_ptr<PluginFactory> factory = boost::make_shared<PluginFactory>();
    return factory;
}

#ifdef FB_X11
FB::Npapi::NpapiPluginPtr
    PluginFactory::createNpapiPlugin( const FB::Npapi::NpapiBrowserHostPtr& host,
                                      const std::string& mimetype )
{
    return boost::make_shared<X11WindowlessPlugin>( host, mimetype );
}
#endif
