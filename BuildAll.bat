@echo ���̃X�N���v�g�����s����ɂ́Acmake�����msbuild�̑o����PATH�ɓ����Ă���K�v������܂��B
@echo �ʏ�Acmake�̃p�X�́AC:\Program Files (x86)\CMake 2.8\bin�B
@echo msbuild�̃p�X�́AC:\Windows\Microsoft.NET\Framework\v4.0.30319�ł��B

@timeout 5

@if NOT EXIST build-win32 mkdir build-win32
@cd build-win32
@cmake ../ -G "Visual Studio 10"
@msbuild KobukiRTC.sln /p:Configuration=Release /p:Platform=WIN32
@cd ../
@exit /b