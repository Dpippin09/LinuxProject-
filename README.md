# Linux Car Stereo System 🚗🎵

A comprehensive car stereo system built for Linux, featuring radio, USB playback, Bluetooth connectivity, and advanced audio controls.

## Features

### 🎵 Audio Sources
- **FM Radio** - 10 preset stations with signal strength display
- **USB Storage** - Support for MP3 playback from USB devices
- **Bluetooth** - Wireless audio streaming from mobile devices
- **AUX Input** - 3.5mm auxiliary input support

### 🎚️ Audio Controls
- **Volume Control** - 30-level volume adjustment with visual indicator
- **Equalizer** - 3-band EQ (Bass, Treble, Balance) with presets
- **Audio Presets** - Rock, Pop, Jazz, Classical, Bass+, Vocal, Flat
- **Balance Control** - Left/Right audio balance adjustment

### 📻 Radio Features
- **Station Scanning** - Automatic FM station detection
- **Preset Memory** - Save favorite stations (1-5 presets)
- **Signal Strength** - Visual signal quality indicator
- **RDS Support** - Radio Data System information display

### 💾 Playlist Management
- **Track Navigation** - Next/Previous track controls
- **Playlist Display** - Track information with artist and title
- **Shuffle Mode** - Random track playback order
- **Progress Tracking** - Visual playback progress indicator

## System Requirements

- **OS**: Linux (Ubuntu, Debian, CentOS, etc.)
- **Compiler**: GCC with C99 support
- **Libraries**: pthread (POSIX threads)
- **Hardware**: Audio output device, optional radio tuner

## Installation

### Quick Install
```bash
# Clone the repository
git clone https://github.com/Dpippin09/LinuxProject-.git
cd LinuxProject-

# Build and install
make all
sudo make install
```

### Manual Build
```bash
# Compile the project
gcc -Wall -Wextra -std=c99 -O2 -Iinclude src/*.c -o car_stereo -lpthread

# Run the application
./car_stereo
```

## Usage

### Starting the System
```bash
# If installed system-wide
car_stereo

# Or run locally
./car_stereo
```

### Controls

| Key | Action | Description |
|-----|---------|------------|
| `P` | Power | Toggle stereo on/off |
| `+/-` | Volume | Adjust volume up/down |
| `M` | Mode | Switch between Radio/USB/Bluetooth/AUX |
| `N` | Next | Next track/station |
| `B` | Previous | Previous track/station |
| `Space` | Play/Pause | Toggle playback |
| `S` | Scan | Scan radio stations |
| `1-5` | Presets | Select preset station/track |
| `E` | Equalizer | Open EQ settings menu |
| `Q` | Quit | Exit application |

### Equalizer Controls

| Key | Action | Range |
|-----|--------|--------|
| `Z/X` | Bass | -10dB to +10dB |
| `C/V` | Treble | -10dB to +10dB |
| `B/N` | Balance | Left to Right |
| `R` | Reset | Flat EQ settings |
| `1-7` | Presets | Audio presets |

## Project Structure

```
LinuxProject-/
├── include/
│   └── car_stereo.h        # Header file with all declarations
├── src/
│   ├── main.c              # Main application and UI
│   ├── audio_control.c     # Basic audio controls
│   ├── radio.c             # FM radio functionality
│   ├── playlist.c          # USB/Music playlist management
│   └── audio_effects.c     # Equalizer and audio effects
├── Makefile                # Build configuration
├── README.md               # This file
└── LICENSE                 # License information
```

## Development

### Building for Development
```bash
# Debug build with symbols
make debug

# Memory leak checking (requires valgrind)
make memcheck

# System requirements check
make syscheck
```

### Adding New Features
The codebase is modular and easy to extend:

- **New audio sources**: Add to `AudioMode` enum and implement handlers
- **Additional presets**: Extend preset arrays in respective modules
- **Enhanced UI**: Modify display functions in `main.c`
- **Hardware integration**: Add hardware-specific code in separate modules

## Hardware Integration

This software can be integrated with actual car stereo hardware:

- **GPIO Controls**: Physical buttons via Raspberry Pi GPIO
- **Display Output**: LCD/TFT displays via framebuffer
- **Audio Hardware**: ALSA/PulseAudio integration
- **Radio Tuner**: SI4703/SI4713 FM tuner modules
- **Bluetooth**: BlueZ stack integration

## Supported Platforms

- **Raspberry Pi** (Recommended for car installations)
- **Linux Desktop** (Development and testing)
- **Embedded Linux** (Custom car stereo hardware)
- **WSL/Docker** (Development environments)

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/new-feature`)
3. Commit changes (`git commit -am 'Add new feature'`)
4. Push to branch (`git push origin feature/new-feature`)
5. Create a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Future Enhancements

- [ ] Internet radio streaming
- [ ] Hands-free calling support
- [ ] Voice commands
- [ ] Smartphone app integration
- [ ] GPS navigation audio
- [ ] Multi-zone audio support
- [ ] Touch screen interface
- [ ] Android Auto/CarPlay compatibility

## Support

For support, please open an issue on GitHub or contact the maintainers.

---

**Made with ❤️ for the Linux community**
