@echo off
: libkobuki.dll���g�����߂ɕK�v�D
set PATH=C:\Program Files\kobuki\bin;%PATH%
pushd %~dp0
if not defined RTM_VC_CONFIG set RTM_VC_CONFIG=Release
start "%~n0" "build\src\%RTM_VC_CONFIG%\%~n0Comp.exe"
popd
