@echo off
cd /d "%~dp0"
echo File loaded: "%~f1"
echo. 
rem dfu-util.exe --list
dfu-util.exe -a 2 -R -d 1 0203:0003 -D "%~f1"
pause