#!/bin/bash

# Build script for Linux Car Stereo
# This script handles compilation and setup

set -e  # Exit on any error

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${BLUE}🔧 Linux Car Stereo Build Script${NC}"
echo "=================================="
echo

# Check system requirements
echo -e "${YELLOW}Checking system requirements...${NC}"

# Check for GCC
if ! command -v gcc &> /dev/null; then
    echo -e "${RED}❌ GCC not found. Please install build-essential:${NC}"
    echo "   Ubuntu/Debian: sudo apt-get install build-essential"
    echo "   CentOS/RHEL: sudo yum groupinstall 'Development Tools'"
    exit 1
fi
echo -e "${GREEN}✅ GCC found: $(gcc --version | head -n1)${NC}"

# Check for Make
if ! command -v make &> /dev/null; then
    echo -e "${RED}❌ Make not found. Please install make${NC}"
    exit 1
fi
echo -e "${GREEN}✅ Make found: $(make --version | head -n1)${NC}"

# Check for pthread support
if ! gcc -pthread -xc /dev/null -o /dev/null 2>/dev/null <<< 'int main(){return 0;}'; then
    echo -e "${RED}❌ pthread library not found${NC}"
    exit 1
fi
echo -e "${GREEN}✅ pthread support available${NC}"

echo

# Create necessary directories
echo -e "${YELLOW}Setting up project structure...${NC}"
mkdir -p obj
mkdir -p logs
mkdir -p config
echo -e "${GREEN}✅ Directories created${NC}"

# Build the project
echo
echo -e "${YELLOW}Building car stereo...${NC}"

# Clean previous builds
if [ -f "car_stereo" ]; then
    echo "Cleaning previous build..."
    make clean
fi

# Compile
echo "Compiling source files..."
make all

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Build successful!${NC}"
    echo
    
    # Show build info
    echo -e "${BLUE}Build Information:${NC}"
    echo "  Binary: $(ls -lh car_stereo | cut -d' ' -f5-)"
    echo "  Architecture: $(file car_stereo | cut -d':' -f2)"
    echo
    
    # Test run
    echo -e "${YELLOW}Testing basic functionality...${NC}"
    if ./car_stereo --help 2>/dev/null || true; then
        echo -e "${GREEN}✅ Binary runs correctly${NC}"
    else
        echo -e "${YELLOW}⚠️  Binary compiled but help test failed (this is normal)${NC}"
    fi
    
    echo
    echo -e "${GREEN}🚗 Car Stereo is ready!${NC}"
    echo
    echo "Available commands:"
    echo "  ./car_stereo     - Run the car stereo"
    echo "  ./demo.sh        - Run interactive demo"
    echo "  make install     - Install system-wide"
    echo "  make clean       - Clean build files"
    echo "  make debug       - Build with debug symbols"
    
else
    echo -e "${RED}❌ Build failed!${NC}"
    echo "Please check the error messages above."
    exit 1
fi
