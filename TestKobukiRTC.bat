@echo off
: KobukiRTC�̃e�X�g
: ise-robot��Controller RTC�𗘗p

:�l�[�~���O�T�[�r�X�̊m�F
rtls /localhost > nul
if errorlevel 1 (
  echo �l�[�~���O�T�[�o��������܂���
  pause
  exit /b 1
  rem /b�I�v�V�����͐e���I��点�Ȃ����߂ɕK�{
)

:�R���|�[�l���g�̋N��
call ..\kobuki_rtc\KobukiRTC.bat
start "Controller" ..\..\ise-robot\Controller\Debug\ControllerComp.exe

:�R���|�[�l���g����ϐ���
set c=/localhost/Controller0.rtc
set k=/localhost/KobukiRTC0.rtc

:���ԑ҂�
timeout 5

:�ڑ�
rtcon %c%:targetVelocity %k%:targetVelocity
rtcon %k%:currentPose %c%:currentPose

:�A�N�e�B�x�[�g
rtact %c% %k%

:loop
set /p ans="�I�����܂����H (y/n)"
if not "%ans%"=="y" goto loop

:�f�B�A�N�e�B�x�[�g
rtdeact  %c% %k%

:�I���irtexit�́C����������j
rtexit %c%
rtexit %k%
