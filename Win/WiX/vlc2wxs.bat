@echo off
for %%i in ("%~0") do set THIS_BAT_PATH=%%~dpi

set VLC_VERSION=2.0.3
set HARVEST_DIR="%THIS_BAT_PATH%\vlc-%VLC_VERSION%"
set VLC_WIX_FILE="%THIS_BAT_PATH%\vlc.wxs"

"%WIX%\bin\heat.exe" dir %HARVEST_DIR% -cg VLC -dr INSTALLDIR -var var.VLC -template fragment -gg -srd -sfrag -sreg  -out %VLC_WIX_FILE% -t vlc.xslt
pause

