#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "car_stereo.h"

#ifndef _WIN32
#include <unistd.h>
#include <pthread.h>
#include <termios.h>
#include <fcntl.h>
#endif

// Global stereo state
CarStereo stereo = {
    .power_on = 0,
    .volume = 15,
    .current_mode = MODE_RADIO,
    .current_station = 0,
    .current_track = 0,
    .is_playing = 0,
    .bass = 0,
    .treble = 0,
    .balance = 0
};

void clear_screen() {
    clear_screen_platform();
}

void display_header() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════╗\n");
    printf("║              LINUX CAR STEREO                ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
}

void display_status() {
    printf("\n┌─── Status ───────────────────────────────────┐\n");
    printf("│ Power: %s | Volume: %02d | Mode: %s    │\n", 
           stereo.power_on ? "ON " : "OFF", 
           stereo.volume,
           get_mode_name(stereo.current_mode));
    
    if (stereo.power_on) {
        switch (stereo.current_mode) {
            case MODE_RADIO:
                printf("│ Station: %.1f FM %s                     │\n",
                       radio_stations[stereo.current_station].frequency,
                       stereo.is_playing ? "♪" : " ");
                printf("│ %s                              │\n",
                       radio_stations[stereo.current_station].name);
                break;
            case MODE_USB:
                printf("│ Track: %d/%d %s                        │\n",
                       stereo.current_track + 1, 
                       get_playlist_size(),
                       stereo.is_playing ? "♪" : "⏸");
                if (get_playlist_size() > 0) {
                    printf("│ %s                              │\n",
                           get_current_track_name());
                }
                break;
            case MODE_BLUETOOTH:
                printf("│ Bluetooth %s                           │\n",
                       stereo.is_playing ? "Connected ♪" : "Ready");
                break;
            case MODE_AUX:
                printf("│ AUX Input %s                           │\n",
                       stereo.is_playing ? "Active ♪" : "Ready");
                break;
        }
        
        // Audio settings
        printf("│ Bass: %+2d | Treble: %+2d | Balance: %+2d    │\n",
               stereo.bass, stereo.treble, stereo.balance);
    }
    printf("└─────────────────────────────────────────────┘\n");
}

void display_controls() {
    printf("\n┌─── Controls ─────────────────────────────────┐\n");
    printf("│ [P] Power    [+/-] Volume   [M] Mode         │\n");
    printf("│ [N] Next     [B] Previous   [Space] Play     │\n");
    printf("│ [S] Scan     [1-5] Presets  [E] EQ Settings  │\n");
    printf("│ [Q] Quit                                     │\n");
    printf("└─────────────────────────────────────────────┘\n");
    printf("Command: ");
    fflush(stdout);
}

char get_input() {
#ifdef _WIN32
    return get_char_platform();
#else
    struct termios old_termios, new_termios;
    char ch;
    
    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    
    // Disable canonical mode and echo
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    
    ch = getchar();
    
    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    
    return ch;
#endif
}

void handle_input(char input) {
    switch (input) {
        case 'p':
        case 'P':
            toggle_power();
            break;
        case '+':
        case '=':
            adjust_volume(1);
            break;
        case '-':
        case '_':
            adjust_volume(-1);
            break;
        case 'm':
        case 'M':
            next_mode();
            break;
        case 'n':
        case 'N':
            next_track();
            break;
        case 'b':
        case 'B':
            previous_track();
            break;
        case ' ':
            toggle_play();
            break;
        case 's':
        case 'S':
            scan_stations();
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
            select_preset(input - '1');
            break;
        case 'e':
        case 'E':
            show_eq_menu();
            break;
        case 'q':
        case 'Q':
            printf("\nShutting down car stereo...\n");
            exit(0);
            break;
        default:
            printf("\nInvalid command!\n");
            sleep(1);
            break;
    }
}

int main() {
    printf("Initializing Linux Car Stereo System...\n");
    
    // Initialize components
    init_radio();
    init_playlist();
    
    printf("System ready!\n");
    sleep(1);
    
    while (1) {
        clear_screen();
        display_header();
        display_status();
        display_controls();
        
        char input = get_input();
        handle_input(input);
        
        usleep(100000); // Small delay for smooth operation
    }
    
    return 0;
}
