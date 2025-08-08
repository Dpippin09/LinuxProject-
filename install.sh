#!/bin/bash

# Installation script for Linux Car Stereo
# This script sets up the car stereo system for various Linux distributions

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
PURPLE='\033[0;35m'
NC='\033[0m'

echo -e "${BLUE}🚗 Linux Car Stereo Installation Script 🎵${NC}"
echo "================================================"
echo

# Check if running as root for system installation
if [[ $EUID -eq 0 ]]; then
    SYSTEM_INSTALL=true
    echo -e "${YELLOW}Running as root - will install system-wide${NC}"
else
    SYSTEM_INSTALL=false
    echo -e "${YELLOW}Running as user - will install locally${NC}"
fi

# Detect Linux distribution
if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$NAME
    VER=$VERSION_ID
    echo -e "${GREEN}Detected OS: $OS $VER${NC}"
else
    echo -e "${YELLOW}Cannot detect OS - proceeding with generic installation${NC}"
    OS="Unknown"
fi

echo

# Install dependencies based on distribution
echo -e "${YELLOW}Installing dependencies...${NC}"

case $OS in
    "Ubuntu"*)
        echo "Installing packages for Ubuntu..."
        apt-get update
        apt-get install -y build-essential gcc make libc6-dev
        apt-get install -y alsa-utils pulseaudio-utils
        apt-get install -y bluetooth bluez-tools
        ;;
    "Debian"*)
        echo "Installing packages for Debian..."
        apt-get update
        apt-get install -y build-essential gcc make libc6-dev
        apt-get install -y alsa-utils pulseaudio-utils
        ;;
    "CentOS"*|"Red Hat"*)
        echo "Installing packages for CentOS/RHEL..."
        yum groupinstall -y "Development Tools"
        yum install -y gcc make glibc-devel
        yum install -y alsa-utils pulseaudio-utils
        ;;
    "Fedora"*)
        echo "Installing packages for Fedora..."
        dnf groupinstall -y "Development Tools"
        dnf install -y gcc make glibc-devel
        dnf install -y alsa-utils pulseaudio-utils
        ;;
    "Arch Linux"*)
        echo "Installing packages for Arch Linux..."
        pacman -Sy --noconfirm base-devel gcc make
        pacman -S --noconfirm alsa-utils pulseaudio
        ;;
    *)
        echo -e "${YELLOW}Unknown distribution - please install manually:${NC}"
        echo "- build-essential or equivalent"
        echo "- gcc, make"
        echo "- alsa-utils, pulseaudio-utils"
        echo "- bluetooth support (optional)"
        read -p "Continue anyway? (y/N): " -n 1 -r
        echo
        if [[ ! $REPLY =~ ^[Yy]$ ]]; then
            exit 1
        fi
        ;;
esac

echo -e "${GREEN}✅ Dependencies installed${NC}"
echo

# Build the application
echo -e "${YELLOW}Building car stereo application...${NC}"
./build.sh

# Create installation directories
if [ "$SYSTEM_INSTALL" = true ]; then
    INSTALL_DIR="/usr/local/bin"
    CONFIG_DIR="/etc/car_stereo"
    LOG_DIR="/var/log/car_stereo"
    
    echo -e "${YELLOW}Creating system directories...${NC}"
    mkdir -p $INSTALL_DIR
    mkdir -p $CONFIG_DIR
    mkdir -p $LOG_DIR
    
    # Copy files
    echo -e "${YELLOW}Installing system files...${NC}"
    cp car_stereo $INSTALL_DIR/
    chmod +x $INSTALL_DIR/car_stereo
    
    cp config/stereo.conf $CONFIG_DIR/
    
    # Create desktop entry
    cat > /usr/share/applications/car_stereo.desktop << EOF
[Desktop Entry]
Name=Linux Car Stereo
Comment=Car stereo system for Linux
Exec=/usr/local/bin/car_stereo
Icon=audio-card
Terminal=true
Type=Application
Categories=AudioVideo;Audio;
EOF
    
    echo -e "${GREEN}✅ System installation complete${NC}"
    echo -e "${BLUE}Car stereo installed to: $INSTALL_DIR/car_stereo${NC}"
    echo -e "${BLUE}Configuration file: $CONFIG_DIR/stereo.conf${NC}"
    
else
    # Local installation
    INSTALL_DIR="$HOME/.local/bin"
    CONFIG_DIR="$HOME/.config/car_stereo"
    
    echo -e "${YELLOW}Creating user directories...${NC}"
    mkdir -p $INSTALL_DIR
    mkdir -p $CONFIG_DIR
    
    # Copy files
    echo -e "${YELLOW}Installing user files...${NC}"
    cp car_stereo $INSTALL_DIR/
    chmod +x $INSTALL_DIR/car_stereo
    
    cp config/stereo.conf $CONFIG_DIR/
    
    # Add to PATH if not already there
    if ! echo $PATH | grep -q "$INSTALL_DIR"; then
        echo "export PATH=\$PATH:$INSTALL_DIR" >> ~/.bashrc
        echo -e "${YELLOW}Added $INSTALL_DIR to PATH in ~/.bashrc${NC}"
        echo -e "${YELLOW}Please run 'source ~/.bashrc' or restart your terminal${NC}"
    fi
    
    echo -e "${GREEN}✅ User installation complete${NC}"
    echo -e "${BLUE}Car stereo installed to: $INSTALL_DIR/car_stereo${NC}"
    echo -e "${BLUE}Configuration file: $CONFIG_DIR/stereo.conf${NC}"
fi

echo

# Audio system setup
echo -e "${YELLOW}Setting up audio system...${NC}"

# Check for PulseAudio
if command -v pulseaudio &> /dev/null; then
    echo -e "${GREEN}✅ PulseAudio found${NC}"
    # Start PulseAudio if not running
    if ! pulseaudio --check; then
        echo "Starting PulseAudio..."
        pulseaudio --start &
        sleep 2
    fi
else
    echo -e "${YELLOW}⚠️  PulseAudio not found - using ALSA${NC}"
fi

# Check for ALSA
if command -v aplay &> /dev/null; then
    echo -e "${GREEN}✅ ALSA found${NC}"
else
    echo -e "${RED}❌ No audio system found${NC}"
fi

echo

# Create startup script
if [ "$SYSTEM_INSTALL" = true ]; then
    cat > /usr/local/bin/start_car_stereo << 'EOF'
#!/bin/bash
# Car stereo startup script

# Check audio system
if ! pulseaudio --check 2>/dev/null; then
    echo "Starting PulseAudio..."
    pulseaudio --start
    sleep 2
fi

# Start car stereo
exec /usr/local/bin/car_stereo "$@"
EOF
    chmod +x /usr/local/bin/start_car_stereo
    echo -e "${GREEN}✅ Startup script created: /usr/local/bin/start_car_stereo${NC}"
fi

echo
echo -e "${PURPLE}═══════════════════════════════════════${NC}"
echo -e "${GREEN}🎉 Installation Complete! 🎉${NC}"
echo -e "${PURPLE}═══════════════════════════════════════${NC}"
echo

echo -e "${BLUE}How to use:${NC}"
if [ "$SYSTEM_INSTALL" = true ]; then
    echo "• Run: car_stereo"
    echo "• Or run: start_car_stereo (with audio setup)"
    echo "• Desktop: Look for 'Linux Car Stereo' in applications menu"
else
    echo "• Run: ~/.local/bin/car_stereo"
    echo "• Or run: car_stereo (if PATH is updated)"
fi

echo
echo -e "${BLUE}Quick start:${NC}"
echo "1. Power on with 'P'"
echo "2. Adjust volume with '+/-'"
echo "3. Switch modes with 'M'"
echo "4. Play/pause with Space"
echo "5. Access equalizer with 'E'"
echo "6. Quit with 'Q'"

echo
echo -e "${YELLOW}For help and documentation, visit:${NC}"
echo -e "${BLUE}https://github.com/Dpippin09/LinuxProject-${NC}"

echo
echo -e "${GREEN}Enjoy your Linux Car Stereo! 🚗🎵${NC}"
