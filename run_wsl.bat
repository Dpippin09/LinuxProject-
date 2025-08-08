@echo off
echo 🚗🎵 Linux Car Stereo - WSL Quick Setup
echo ====================================
echo.

echo Checking for WSL...
where wsl >nul 2>&1
if %errorlevel% neq 0 (
    echo ❌ WSL not found. Install WSL2 from Microsoft Store:
    echo    https://aka.ms/wsl2
    echo.
    echo After installing WSL2:
    echo 1. Install Ubuntu from Microsoft Store
    echo 2. Run: wsl
    echo 3. In WSL: sudo apt update ^&^& sudo apt install build-essential
    echo 4. Clone this project in WSL
    echo 5. Run: ./build.sh ^&^& ./car_stereo
    pause
    exit /b 1
)

echo ✅ WSL found! Starting WSL session...
echo.
echo In WSL, run these commands:
echo   cd /mnt/c/Users/dpipp/LinuxProject-
echo   ./build.sh
echo   ./car_stereo
echo.

wsl
