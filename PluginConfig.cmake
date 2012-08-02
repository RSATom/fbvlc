#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for FireBreathed VLC
#
#\**********************************************************/

set(PLUGIN_NAME "FBVLC")
set(PLUGIN_PREFIX "FBVLC")
set(COMPANY_NAME "RSATom")
set(PLUGIN_VERSION "0.0.0.6")

# ActiveX constants:
set(FBTYPELIB_NAME FBVLCLib)
set(FBTYPELIB_DESC "FBVLC ${PLUGIN_VERSION} Type Library")
set(IFBControl_DESC "FBVLC Control Interface")
set(FBControl_DESC "FBVLC Control Class")
set(IFBComJavascriptObject_DESC "FBVLC IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "FBVLC ComJavascriptObject Class")
set(IFBComEventSource_DESC "FBVLC IFBComEventSource Interface")
set(AXVERSION_NUM "${PLUGIN_VERSION}")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID a6283703-2b52-5487-b262-119d9bf8c79c)
set(IFBControl_GUID 70347ffa-4dc3-5310-8305-db6ff9803d4f)
set(FBControl_GUID 52d4e39e-6cbd-524b-9922-e932946f6d1e)
set(IFBComJavascriptObject_GUID 0228042b-17ee-5faa-b4d7-3d641f286d91)
set(FBComJavascriptObject_GUID 2b900a1a-dca9-593f-bb5e-59f32aa454ee)
set(IFBComEventSource_GUID d6053191-c33f-5ef6-b69c-36f18d100f6b)

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "RSATom.FBVLC")
set(MOZILLA_PLUGINID "RSATom.name/FBVLC")

# strings
set(FBSTRING_CompanyName "RSATom")
set(FBSTRING_PluginDescription "VLC Web Plugin (powered by FireBreath)")
set(FBSTRING_PLUGIN_VERSION "${PLUGIN_VERSION}")
set(FBSTRING_LegalCopyright "Copyright 2012 RSATom")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "FireBreathed VLC")
set(FBSTRING_FileExtents "")
set(FBSTRING_PluginName "FireBreathed VLC")
set(FBSTRING_MIMEType "application/x-fb-vlc")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

#set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 1)
set(FBMAC_USE_COCOA 1)
set(FBMAC_USE_COREGRAPHICS 1)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
