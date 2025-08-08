@echo off
REM Windows build script for Linux Car Stereo
REM This script compiles the project using MinGW or Visual Studio tools

echo Building Linux Car Stereo on Windows...
echo ========================================
echo.

REM Check for MinGW-w64 GCC
where gcc >nul 2>&1
if %errorlevel% equ 0 (
    echo Found GCC compiler
    goto :compile_gcc
)

REM Check for Visual Studio tools
where cl >nul 2>&1
if %errorlevel% equ 0 (
    echo Found Visual Studio compiler
    goto :compile_msvc
)

REM Check for TDM-GCC
where tdm-gcc >nul 2>&1
if %errorlevel% equ 0 (
    echo Found TDM-GCC compiler
    goto :compile_tdm
)

echo ERROR: No compiler found!
echo.
echo Please install one of the following:
echo 1. MinGW-w64: https://www.mingw-w64.org/
echo 2. Visual Studio Build Tools: https://visualstudio.microsoft.com/
echo 3. TDM-GCC: https://jmeubank.github.io/tdm-gcc/
echo 4. Or use WSL (Windows Subsystem for Linux)
echo.
pause
exit /b 1

:compile_gcc
echo Compiling with GCC...
if not exist obj mkdir obj

gcc -Wall -Wextra -std=c99 -O2 -Iinclude -DWINDOWS_BUILD src\main.c src\audio_control.c src\radio.c src\playlist.c src\audio_effects.c -o car_stereo.exe -lws2_32

if %errorlevel% equ 0 (
    echo.
    echo ✅ Build successful!
    echo Binary created: car_stereo.exe
    echo.
    echo Run with: car_stereo.exe
    goto :end
) else (
    echo.
    echo ❌ Build failed!
    goto :end
)

:compile_msvc
echo Compiling with MSVC...
if not exist obj mkdir obj

cl /nologo /W3 /O2 /I include /D WINDOWS_BUILD src\*.c /Fe:car_stereo.exe ws2_32.lib

if %errorlevel% equ 0 (
    echo.
    echo ✅ Build successful!
    echo Binary created: car_stereo.exe
    echo.
    echo Run with: car_stereo.exe
    goto :end
) else (
    echo.
    echo ❌ Build failed!
    goto :end
)

:compile_tdm
echo Compiling with TDM-GCC...
if not exist obj mkdir obj

tdm-gcc -Wall -Wextra -std=c99 -O2 -Iinclude -DWINDOWS_BUILD src\main.c src\audio_control.c src\radio.c src\playlist.c src\audio_effects.c -o car_stereo.exe -lws2_32

if %errorlevel% equ 0 (
    echo.
    echo ✅ Build successful!
    echo Binary created: car_stereo.exe
    echo.
    echo Run with: car_stereo.exe
    goto :end
) else (
    echo.
    echo ❌ Build failed!
    goto :end
)

:end
echo.
echo Build process completed.
pause
