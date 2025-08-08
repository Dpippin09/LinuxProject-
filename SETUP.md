# Linux Car Stereo Setup Guide 🚗🎵

This guide will help you set up the Linux Car Stereo system on various platforms and environments.

## Quick Start

### Linux Users (Recommended)
```bash
# Clone and build
git clone https://github.com/Dpippin09/LinuxProject-.git
cd LinuxProject-
./build.sh

# Run the car stereo
./car_stereo
```

### Windows Users
```cmd
# Clone the repository
git clone https://github.com/Dpippin09/LinuxProject-.git
cd LinuxProject-

# Build with the Windows batch file
build.bat

# Run the car stereo
car_stereo.exe
```

### WSL (Windows Subsystem for Linux) Users
```bash
# Use Linux instructions inside WSL
./build.sh
./car_stereo
```

## Platform-Specific Installation

### 🐧 Linux Installation

#### Ubuntu/Debian
```bash
# Install dependencies
sudo apt-get update
sudo apt-get install build-essential gcc make
sudo apt-get install alsa-utils pulseaudio-utils

# Build and install
./install.sh
```

#### CentOS/RHEL/Fedora
```bash
# CentOS/RHEL
sudo yum groupinstall "Development Tools"
sudo yum install alsa-utils pulseaudio-utils

# Fedora
sudo dnf groupinstall "Development Tools"
sudo dnf install alsa-utils pulseaudio-utils

# Build and install
./install.sh
```

#### Arch Linux
```bash
# Install dependencies
sudo pacman -S base-devel gcc make
sudo pacman -S alsa-utils pulseaudio

# Build and install
./install.sh
```

### 🪟 Windows Installation

#### Option 1: MinGW-w64 (Recommended)
1. Download MinGW-w64 from: https://www.mingw-w64.org/
2. Install and add to PATH
3. Run `build.bat`

#### Option 2: Visual Studio Build Tools
1. Install Visual Studio Build Tools
2. Open Developer Command Prompt
3. Run `build.bat`

#### Option 3: WSL (Best Linux compatibility)
1. Install WSL2 from Microsoft Store
2. Install Ubuntu or your preferred Linux distribution
3. Follow Linux installation steps inside WSL

### 🍎 macOS Installation
```bash
# Install Xcode command line tools
xcode-select --install

# Install dependencies via Homebrew
brew install gcc make

# Build
make all
./car_stereo
```

## Development Environment Setup

### VS Code Setup
1. Install VS Code
2. Install C/C++ extension
3. Open the project folder
4. Use Ctrl+Shift+P → "Tasks: Run Task" → "Build"

### Eclipse CDT Setup
1. Install Eclipse CDT
2. Import existing C project
3. Configure build settings
4. Build and run

### Code::Blocks Setup
1. Install Code::Blocks
2. Create new project from existing sources
3. Configure compiler settings
4. Build and run

## Hardware Integration

### Raspberry Pi Setup
```bash
# Enable audio
sudo raspi-config
# Advanced Options → Audio → Force 3.5mm jack

# Install additional packages
sudo apt-get install wiringpi

# For GPIO button support
sudo usermod -a -G gpio pi
```

### Audio System Configuration

#### PulseAudio Setup (Recommended)
```bash
# Install PulseAudio
sudo apt-get install pulseaudio pulseaudio-utils

# Start PulseAudio
pulseaudio --start

# Test audio
paplay /usr/share/sounds/alsa/Front_Right.wav
```

#### ALSA Setup (Alternative)
```bash
# Install ALSA
sudo apt-get install alsa-utils

# Configure audio devices
sudo alsamixer

# Test audio
aplay /usr/share/sounds/alsa/Front_Right.wav
```

### Bluetooth Setup
```bash
# Install BlueZ
sudo apt-get install bluetooth bluez bluez-tools

# Enable Bluetooth
sudo systemctl enable bluetooth
sudo systemctl start bluetooth

# Make device discoverable
sudo bluetoothctl
> discoverable on
> pairable on
```

## Troubleshooting

### Common Issues

#### Build Errors
```bash
# Missing compiler
sudo apt-get install build-essential

# Missing pthread
sudo apt-get install libc6-dev

# Permission denied
chmod +x build.sh install.sh demo.sh
```

#### Audio Issues
```bash
# No sound output
pulseaudio --kill
pulseaudio --start

# Check audio devices
aplay -l
pactl list short sinks
```

#### Display Issues
```bash
# Terminal not clearing properly
export TERM=xterm-256color

# Unicode characters not displaying
sudo locale-gen en_US.UTF-8
```

### Platform-Specific Issues

#### Windows
- **Issue**: GCC not found
- **Solution**: Install MinGW-w64 or use WSL

#### Linux
- **Issue**: Permission denied for audio devices
- **Solution**: Add user to audio group: `sudo usermod -a -G audio $USER`

#### macOS
- **Issue**: pthread library issues
- **Solution**: Use `clang` instead of `gcc`

## Advanced Configuration

### Custom Audio Devices
Edit `config/stereo.conf`:
```ini
[Audio]
default_output_device = hw:1,0
sample_rate = 44100
buffer_size = 1024
```

### GPIO Integration (Raspberry Pi)
```c
// In car_stereo.h, add:
#define GPIO_VOLUME_UP    18
#define GPIO_VOLUME_DOWN  19
#define GPIO_MODE_SWITCH  20
```

### Network Audio Streaming
```bash
# Install streaming support
sudo apt-get install gstreamer1.0-plugins-good
sudo apt-get install icecast2
```

## Performance Optimization

### CPU Optimization
```bash
# Set CPU governor to performance
sudo cpufreq-set -g performance

# Set process priority
nice -n -10 ./car_stereo
```

### Memory Optimization
```bash
# Reduce memory usage
export MALLOC_TRIM_THRESHOLD_=100000

# Use memory mapping for audio files
export AUDIO_BUFFER_SIZE=4096
```

## Security Considerations

### File Permissions
```bash
# Secure configuration files
chmod 600 config/stereo.conf

# Create dedicated user
sudo useradd -r -s /bin/false car_stereo
```

### Network Security
```bash
# Firewall rules for Bluetooth
sudo ufw allow from 00:00:00:00:00:00 to any port 1234
```

## Getting Help

- **GitHub Issues**: https://github.com/Dpippin09/LinuxProject-/issues
- **Documentation**: Check README.md for detailed usage
- **Community**: Join our Discord server (link in README)

## Contributing

See CONTRIBUTING.md for development setup and contribution guidelines.

---

**Happy coding! 🚗🎵**
