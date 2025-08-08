#!/bin/bash

# Linux Car Stereo Demo Script
# This script demonstrates the features of the car stereo system

echo "🚗🎵 Linux Car Stereo Demo 🎵🚗"
echo "=================================="
echo

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Function to print colored output
print_step() {
    echo -e "${BLUE}[DEMO]${NC} $1"
    sleep 2
}

print_feature() {
    echo -e "${GREEN}✅${NC} $1"
    sleep 1
}

print_info() {
    echo -e "${YELLOW}ℹ️${NC}  $1"
    sleep 1
}

echo -e "${CYAN}This demo showcases the Linux Car Stereo System features:${NC}"
echo

# Check if the binary exists
if [ ! -f "./car_stereo" ]; then
    echo -e "${RED}❌ Car stereo binary not found. Building first...${NC}"
    make clean && make all
    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ Build failed. Please check compilation errors.${NC}"
        exit 1
    fi
    echo -e "${GREEN}✅ Build successful!${NC}"
    echo
fi

print_step "📋 System Overview"
print_feature "Multi-source audio system (Radio, USB, Bluetooth, AUX)"
print_feature "10 FM radio stations with presets"
print_feature "Music playlist with 10 sample tracks"
print_feature "3-band equalizer with 8 presets"
print_feature "Volume control with visual indicators"
print_feature "Interactive terminal-based interface"

echo
print_step "🎛️ Available Controls"
echo -e "   ${PURPLE}P${NC} - Power on/off"
echo -e "   ${PURPLE}+/-${NC} - Volume control"
echo -e "   ${PURPLE}M${NC} - Switch modes (Radio → USB → Bluetooth → AUX)"
echo -e "   ${PURPLE}N/B${NC} - Next/Previous track or station"
echo -e "   ${PURPLE}Space${NC} - Play/Pause"
echo -e "   ${PURPLE}S${NC} - Scan radio stations"
echo -e "   ${PURPLE}1-5${NC} - Quick presets"
echo -e "   ${PURPLE}E${NC} - Equalizer settings"
echo -e "   ${PURPLE}Q${NC} - Quit application"

echo
print_step "📻 Radio Features"
print_feature "88.5 FM - Rock FM"
print_feature "92.1 FM - Pop Hits"
print_feature "95.7 FM - Classic Rock"
print_feature "98.3 FM - Jazz Lounge"
print_feature "101.1 FM - Hip Hop"
print_info "Plus 5 more stations with signal strength indicators"

echo
print_step "🎵 Music Library"
print_feature "Highway Dreams - The Rockers"
print_feature "City Lights - Urban Sound"
print_feature "Summer Breeze - Chill Vibes"
print_feature "Thunder Road - Classic Band"
print_feature "Digital Love - Electronic Mix"
print_info "Plus 5 more tracks with full metadata"

echo
print_step "🎚️ Equalizer Presets"
print_feature "Rock - Enhanced bass and treble"
print_feature "Pop - Balanced with vocal clarity"
print_feature "Jazz - Smooth mid-range focus"
print_feature "Classical - Natural sound reproduction"
print_feature "Bass+ - Maximum low-end boost"
print_info "Plus Vocal, Flat, and Custom presets"

echo
print_step "🔧 Technical Specifications"
print_info "Written in C99 with POSIX compliance"
print_info "Multi-threaded audio processing"
print_info "Terminal-based user interface"
print_info "Modular architecture for easy extension"
print_info "Memory-efficient design"

echo
print_step "🚀 Ready to Launch!"
echo -e "${CYAN}The car stereo system is ready to run.${NC}"
echo
echo -e "${YELLOW}Quick Start Instructions:${NC}"
echo "1. Press 'P' to power on the system"
echo "2. Use '+' and '-' to adjust volume"
echo "3. Press 'M' to switch between modes"
echo "4. Press 'Space' to start playing"
echo "5. Press 'E' to access equalizer"
echo "6. Press 'Q' to quit when done"
echo
echo -e "${GREEN}Starting Linux Car Stereo in 3 seconds...${NC}"
sleep 1
echo -e "${GREEN}3...${NC}"
sleep 1
echo -e "${GREEN}2...${NC}"
sleep 1
echo -e "${GREEN}1...${NC}"
sleep 1

# Launch the car stereo
echo -e "${CYAN}🚗 Starting your Linux Car Stereo! 🎵${NC}"
echo
./car_stereo
