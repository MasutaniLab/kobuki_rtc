@echo off
: libkobuki.dllを使うために必要．
if "%LIBKOBUKI_ROOT%" == "" (
  echo 環境変数LIBKOBUKI_ROOTが設定されていません．
  exit /b 1
  rem /bオプションは親を終わらせないために必須
)
set PATH=%LIBKOBUKI_ROOT%\bin;%PATH%
pushd %~dp0
if not defined RTM_VC_CONFIG set RTM_VC_CONFIG=Release
start "%~n0" "build\src\%RTM_VC_CONFIG%\%~n0Comp.exe"
popd
