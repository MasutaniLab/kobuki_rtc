@echo off
: libkobuki.dll���g�����߂ɕK�v�D
if "%LIBKOBUKI_ROOT%" == "" (
  echo ���ϐ�LIBKOBUKI_ROOT���ݒ肳��Ă��܂���D
  exit /b 1
  rem /b�I�v�V�����͐e���I��点�Ȃ����߂ɕK�{
)
set PATH=%LIBKOBUKI_ROOT%\bin;%PATH%
pushd %~dp0
if not defined RTM_VC_CONFIG set RTM_VC_CONFIG=Release
start "%~n0" "build\src\%RTM_VC_CONFIG%\%~n0Comp.exe"
popd
