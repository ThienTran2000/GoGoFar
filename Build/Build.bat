@echo off


if not exist "%~dp0Logs" mkdir "%~dp0Logs"
if not exist "%~dp0Build" mkdir "%~dp0Build"

pushd .\Build
if "%~1"=="" (
    python ..\Scripts\makecmake.py  > ..\Logs\makecmake.log 2>&1
) else (
    python ..\Scripts\makecmake.py %~1 > ..\Logs\makecmake.log 2>&1
)


cmake -G "MinGW Makefiles"

mingw32-make -j16

popd
