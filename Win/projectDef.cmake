#/**********************************************************\ 
# Auto-generated Windows project definition file for the
# FireBreathed VLC project
#\**********************************************************/

# Windows template platform definition CMake file
# Included from ../CMakeLists.txt

# remember that the current source dir is the project root; this file is in Win/
file (GLOB PLATFORM RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Win/[^.]*.cpp
    Win/[^.]*.h
    Win/[^.]*.cmake
    Win/[^.]*.rc
    )

# use this to add preprocessor definitions
add_definitions(
    /D "_ATL_STATIC_REGISTRY"
)

# get PCH related files
file (GLOB PCH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    StdAfx.*
)

# make sure that PCH-related files is NOT part of ${SOURCES} 
LIST(REMOVE_ITEM SOURCES ${PCH})

SOURCE_GROUP("PCH files" FILES ${PCH})
SOURCE_GROUP(Win FILES ${PLATFORM})

set (SOURCES
    ${SOURCES}
    ${PLATFORM}
    )

# set PCH
MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
 GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
 SET(__PrecompiledBinary "$(IntDir)\\$(TargetName).pch")
  
 SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
   PROPERTIES COMPILE_FLAGS "/Yc -Zm160")
   #OBJECT_OUTPUTS "${__PrecompiledBinary}"
  
 foreach(CURFILE ${${SourcesVar}})
   GET_FILENAME_COMPONENT(CURFILE_EXT ${CURFILE} EXT)
   GET_FILENAME_COMPONENT(CURFILE_NAME ${CURFILE} NAME)
   if (CURFILE_EXT STREQUAL ".cpp" AND NOT CURFILE_NAME STREQUAL PrecompiledBasename)
     SET_SOURCE_FILES_PROPERTIES(${CURFILE}
       PROPERTIES COMPILE_FLAGS "/Yu /FI\"${PrecompiledHeader}\" -Zm160")
       #OBJECT_DEPENDS "${__PrecompiledBinary}"
   endif()
 endforeach()
 
 # Add precompiled header to SourcesVar
 LIST(APPEND ${SourcesVar} ${PrecompiledSource})
 LIST(APPEND ${SourcesVar} ${PrecompiledHeader})
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)

# activate PCH
ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" SOURCES)

add_windows_plugin(${PROJECT_NAME} SOURCES)

# This is an example of how to add a build step to sign the plugin DLL before
# the WiX installer builds.  The first filename (certificate.pfx) should be
# the path to your pfx file.  If it requires a passphrase, the passphrase
# should be located inside the second file. If you don't need a passphrase
# then set the second filename to "".  If you don't want signtool to timestamp
# your DLL then make the last parameter "".
#
# Note that this will not attempt to sign if the certificate isn't there --
# that's so that you can have development machines without the cert and it'll
# still work. Your cert should only be on the build machine and shouldn't be in
# source control!
# -- uncomment lines below this to enable signing --
#firebreath_sign_plugin(${PROJECT_NAME}
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/certificate.pfx"
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/passphrase.txt"
#    "http://timestamp.verisign.com/scripts/timestamp.dll")

# add library dependencies here; leave ${PLUGIN_INTERNAL_DEPS} there unless you know what you're doing!
target_link_libraries(${PROJECT_NAME}
    ${PLUGIN_INTERNAL_DEPS}
    libvlc.lib
    )

set(WIX_HEAT_FLAGS
    -gg                 # Generate GUIDs
    -srd                # Suppress Root Dir
    -cg PluginDLLGroup  # Set the Component group name
    -dr INSTALLDIR      # Set the directory ID to put the files in
    )

SET(FB_WIX_DEST ${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${PROJNAME}_${FBSTRING_PLUGIN_VERSION}.msi)
add_wix_installer( ${PLUGIN_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/Win/WiX/FBVLCInstaller.wxs
    PluginDLLGroup
    ${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/
    ${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${FBSTRING_PluginFileName}.dll
    ${PROJECT_NAME}
    )

if(DEFINED VLC_VERSION)
set (WIX_SOURCES_WITH_VLC
    ${CMAKE_CURRENT_SOURCE_DIR}/Win/WiX/FBVLC_WITH_VLC_Installer.wxs
    ${CMAKE_CURRENT_SOURCE_DIR}/Win/WiX/vlc.wxs
    )

set(WIX_HEAT_SUFFIX "_WITH_VLC_main")
set(FB_WIX_SUFFIX _WITH_VLC_WiXInstall)
set(WIX_LINK_FLAGS ${WIX_LINK_FLAGS} -dVLC=${CMAKE_CURRENT_SOURCE_DIR}/Win/WiX/vlc-${VLC_VERSION})
set(FB_WIX_DEST ${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${PROJNAME}_${FBSTRING_PLUGIN_VERSION}_VLC_${VLC_VERSION}.msi)

add_wix_installer( ${PLUGIN_NAME}
    "${WIX_SOURCES_WITH_VLC}"
    PluginDLLGroup
    ${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/
    ${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${FBSTRING_PluginFileName}.dll
    ${PROJECT_NAME}
    )
endif()

# This is an example of how to add a build step to sign the WiX installer
# -- uncomment lines below this to enable signing --
#firebreath_sign_file("${PLUGIN_NAME}_WiXInstall"
#    "${FB_BIN_DIR}/${PLUGIN_NAME}/${CMAKE_CFG_INTDIR}/${PLUGIN_NAME}.msi"
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/certificate.pfx"
#    "${CMAKE_CURRENT_SOURCE_DIR}/sign/passphrase.txt"
#    "http://timestamp.verisign.com/scripts/timestamp.dll")
