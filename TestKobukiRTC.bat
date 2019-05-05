@echo off
: KobukiRTCのテスト
: ise-robotのController RTCを利用

:ネーミングサービスの確認
rtls /localhost > nul
if errorlevel 1 (
  echo ネーミングサーバが見つかりません
  pause
  exit /b 1
  rem /bオプションは親を終わらせないために必須
)

:コンポーネントの起動
call ..\kobuki_rtc\KobukiRTC.bat
start "Controller" ..\..\ise-robot\Controller\Debug\ControllerComp.exe

:コンポーネント名を変数化
set c=/localhost/Controller0.rtc
set k=/localhost/KobukiRTC0.rtc

:時間待ち
timeout 5

:接続
rtcon %c%:targetVelocity %k%:targetVelocity
rtcon %k%:currentPose %c%:currentPose

:アクティベート
rtact %c% %k%

:loop
set /p ans="終了しますか？ (y/n)"
if not "%ans%"=="y" goto loop

:ディアクティベート
rtdeact  %c% %k%

:終了（rtexitは，引数を一つずつ）
rtexit %c%
rtexit %k%
