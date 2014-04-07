#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for FireBreathed VLC
#
#\**********************************************************/

set(PLUGIN_VERSION "0.1.2.1")
set(PLUGIN_NAME "FBVLC")
set(PLUGIN_PREFIX "FBVLC")
set(PLUGIN_DESCRIPTION "VLC Web Plugin (powered by FireBreath)")
set(PRODUCT_NAME "FireBreathed VLC")
set(COMPANY_NAME "RSATom")
set(COMPANY_DOMAIN "RSATom.name")
set(COPYRIGHT_YEARS "2012-2014")
set(PLUGIN_MIMETYPE "application/x-fb-vlc")

#if you want embed vlc into FBVLC distribution:
# 1) place vlc into FBVLC\Win\WiX\vlc-${VLC_VERSION}
# 2) uncomment following
if(APPLE)
    set(VLC_VERSION "2.1.4")
else()
    set(VLC_VERSION "2.1.3")
endif()
# 3) run prepXXXX.cmd from FireBreath

#unfortunately current implementation does not work :(
#set(BUILD_IE_CAB 1)

# ActiveX constants:
set(FBTYPELIB_NAME ${PLUGIN_NAME}Lib)
set(FBTYPELIB_DESC "${PLUGIN_NAME} ${PLUGIN_VERSION} Type Library")
set(IFBControl_DESC "${PLUGIN_NAME} Control Interface")
set(FBControl_DESC "${PLUGIN_NAME} Control Class")
set(IFBComJavascriptObject_DESC "${PLUGIN_NAME} IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "${PLUGIN_NAME} ComJavascriptObject Class")
set(IFBComEventSource_DESC "${PLUGIN_NAME} IFBComEventSource Interface")
set(AXVERSION_NUM "${PLUGIN_VERSION}")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID a6283703-2b52-5487-b262-119d9bf8c79c)
set(IFBControl_GUID 70347ffa-4dc3-5310-8305-db6ff9803d4f)
set(FBControl_GUID 52d4e39e-6cbd-524b-9922-e932946f6d1e)
set(IFBComJavascriptObject_GUID 0228042b-17ee-5faa-b4d7-3d641f286d91)
set(FBComJavascriptObject_GUID 2b900a1a-dca9-593f-bb5e-59f32aa454ee)
set(IFBComEventSource_GUID d6053191-c33f-5ef6-b69c-36f18d100f6b)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID {5A8B0484-C183-495C-B9BC-7B3172752862})
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID {47A068B1-EF68-48B6-9725-761AE603BF85})
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "${COMPANY_NAME}.${PLUGIN_NAME}")
if ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "${COMPANY_DOMAIN}/${PLUGIN_NAME}")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "${COMPANY_DOMAIN}/${PLUGIN_NAME}_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )

# strings
set(FBSTRING_CompanyName "${COMPANY_NAME}")
set(FBSTRING_PluginDescription "${PLUGIN_DESCRIPTION}")
set(FBSTRING_PLUGIN_VERSION "${PLUGIN_VERSION}")
set(FBSTRING_LegalCopyright "Copyright ${COPYRIGHT_YEARS} ${COMPANY_NAME}")
if(WIN32)
    set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
elseif(APPLE)
    set(FBSTRING_PluginFileName "${PLUGIN_NAME}")
else()
    set(FBSTRING_PluginFileName "np${PLUGIN_NAME}")
endif()
set(FBSTRING_ProductName "${PRODUCT_NAME}")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "${PLUGIN_NAME}")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "${PLUGIN_NAME}_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "${PLUGIN_MIMETYPE}")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

#set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 0)
set(FBMAC_USE_COCOA 1)
set(FBMAC_USE_COREGRAPHICS 1)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
