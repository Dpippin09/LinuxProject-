@echo off
echo 🔧 Windows Compiler Setup Guide
echo ==============================
echo.

echo To build and run the car stereo on Windows:
echo.
echo Option 1: MinGW-w64 (Recommended)
echo ----------------------------------
echo 1. Download from: https://www.mingw-w64.org/downloads/
echo 2. Install to C:\mingw64
echo 3. Add C:\mingw64\bin to your PATH
echo 4. Restart command prompt
echo 5. Run: build.bat
echo.

echo Option 2: MSYS2 (Easy Install)
echo ------------------------------
echo 1. Download from: https://www.msys2.org/
echo 2. Install MSYS2
echo 3. In MSYS2 terminal: pacman -S mingw-w64-x86_64-gcc
echo 4. Add to PATH: C:\msys64\mingw64\bin
echo 5. Run: build.bat
echo.

echo Option 3: Visual Studio Build Tools
echo -----------------------------------
echo 1. Download Visual Studio Build Tools
echo 2. Install C++ build tools
echo 3. Open "Developer Command Prompt"
echo 4. Run: build.bat
echo.

echo Quick Test (after installing compiler):
echo ---------------------------------------
echo   build.bat
echo   car_stereo.exe
echo.

echo 🎯 For immediate viewing without compilation:
echo   - Check demo_interface.txt (visual preview)
echo   - Use online C compiler (repl.it, onlinegdb.com)
echo   - Install WSL for full Linux experience
echo.

pause
