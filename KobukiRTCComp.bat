@echo off
set PATH=C:\Program Files\kobuki\bin;%PATH%
if not defined RTM_VC_CONFIG set RTM_VC_CONFIG=Release
start "%~n0" "build\src\%RTM_VC_CONFIG%\%~n0.exe"
