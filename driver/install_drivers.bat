@echo off

echo Installing Matrix DFU driver...
"%~dp0wdi-simple" --vid 0x0203 --pid 0x0003 --type 1 --name "Matrix DFU" --dest "%~dp0matrix-dfu"
echo.

echo Installing Matrix Serial driver...
"%~dp0wdi-simple" --vid 0x0203 --pid 0x0004 --type 3 --name "Matrix Serial" --dest "%~dp0matrix-serial"
echo.

pause
