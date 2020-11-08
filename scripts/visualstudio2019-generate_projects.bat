@echo off
pushd %~dp0\..\
call utils\premake\windows-premake5.exe vs2019
popd
PAUSE