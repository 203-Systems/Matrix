@echo off
echo File loaded: %~1
echo. 
dfu-util --list
pause
dfu-util -a 2 -R -d 1 1EAF:0003 -D "%~1"
pause