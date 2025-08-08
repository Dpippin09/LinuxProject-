#ifndef PLATFORM_H
#define PLATFORM_H

// Cross-platform compatibility header for Linux Car Stereo

#ifdef _WIN32
    // Windows-specific includes and definitions
    #include <windows.h>
    #include <conio.h>
    #include <io.h>
    
    #define WINDOWS_BUILD
    #define CLEAR_COMMAND "cls"
    #define SLEEP_MS(x) Sleep(x)
    #define SLEEP_SEC(x) Sleep((x) * 1000)
    
    // Windows doesn't have pthread by default
    #define pthread_t HANDLE
    
    // Terminal control alternatives for Windows
    static inline char get_char_windows() {
        return _getch();
    }
    
    static inline void set_console_mode() {
        HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hConsole, &mode);
        SetConsoleMode(hConsole, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
    }
    
    static inline void restore_console_mode() {
        HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hConsole, &mode);
        SetConsoleMode(hConsole, mode | ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
    }

#else
    // Linux/Unix-specific includes and definitions
    #include <unistd.h>
    #include <termios.h>
    #include <pthread.h>
    
    #define LINUX_BUILD
    #define CLEAR_COMMAND "clear"
    #define SLEEP_MS(x) usleep((x) * 1000)
    #define SLEEP_SEC(x) sleep(x)
    
    // Linux terminal control (already implemented in main.c)
    extern char get_input();
    
    static inline char get_char_linux() {
        return get_input();
    }
    
    static inline void set_console_mode() {
        // Linux implementation in get_input() function
    }
    
    static inline void restore_console_mode() {
        // Linux implementation in get_input() function
    }

#endif

// Common cross-platform functions
static inline void clear_screen_platform() {
    system(CLEAR_COMMAND);
}

static inline char get_char_platform() {
#ifdef _WIN32
    return get_char_windows();
#else
    return get_char_linux();
#endif
}

static inline void sleep_ms_platform(int ms) {
    SLEEP_MS(ms);
}

static inline void sleep_sec_platform(int sec) {
    SLEEP_SEC(sec);
}

// Platform-specific audio system detection
static inline const char* get_audio_system() {
#ifdef _WIN32
    return "DirectSound/WASAPI";
#else
    return "ALSA/PulseAudio";
#endif
}

// Platform-specific file paths
static inline const char* get_config_path() {
#ifdef _WIN32
    return "%APPDATA%\\CarStereo\\stereo.conf";
#else
    return "~/.config/car_stereo/stereo.conf";
#endif
}

static inline const char* get_log_path() {
#ifdef _WIN32
    return "%APPDATA%\\CarStereo\\car_stereo.log";
#else
    return "/var/log/car_stereo.log";
#endif
}

#endif // PLATFORM_H
