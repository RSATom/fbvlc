/**********************************************************\ 
 
 Auto-generated Factory.cpp
 
 This file contains the auto-generated factory methods 
 for the FBVLC project
 
\**********************************************************/

#include "FactoryBase.h"
#include "FBVLC.h"
#include <boost/make_shared.hpp>

#ifdef FB_WIN
#    include "Win/FBVLC_Win.h"
#elif defined FB_X11
#    include "X11/FBVLC_X11.h"
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

