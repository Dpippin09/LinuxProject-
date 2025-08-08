#include "car_stereo.h"
#include <unistd.h>

// Global radio stations array
RadioStation radio_stations[MAX_STATIONS];

void init_radio() {
    // Initialize popular FM stations
    radio_stations[0] = (RadioStation){88.5, "Rock FM"};
    radio_stations[1] = (RadioStation){92.1, "Pop Hits"};
    radio_stations[2] = (RadioStation){95.7, "Classic Rock"};
    radio_stations[3] = (RadioStation){98.3, "Jazz Lounge"};
    radio_stations[4] = (RadioStation){101.1, "Hip Hop"};
    radio_stations[5] = (RadioStation){104.7, "Country"};
    radio_stations[6] = (RadioStation){107.3, "Electronic"};
    radio_stations[7] = (RadioStation){89.9, "News Radio"};
    radio_stations[8] = (RadioStation){93.5, "Oldies"};
    radio_stations[9] = (RadioStation){106.1, "Alternative"};
    
    printf("📻 Radio initialized with %d stations\n", MAX_STATIONS);
}

void scan_stations() {
    if (!stereo.power_on || stereo.current_mode != MODE_RADIO) return;
    
    printf("\n🔍 Scanning stations...\n");
    
    for (int i = 0; i < MAX_STATIONS; i++) {
        printf("📡 %.1f FM - %s", 
               radio_stations[i].frequency, 
               radio_stations[i].name);
        
        // Simulate signal strength
        int signal_strength = rand() % 5 + 1;
        printf(" [");
        for (int j = 0; j < 5; j++) {
            if (j < signal_strength) {
                printf("▓");
            } else {
                printf("░");
            }
        }
        printf("]\n");
        
        usleep(500000); // 0.5 second delay for each station
    }
    
    printf("\nScan complete! Press 1-5 for presets or N/B for navigation\n");
    sleep(2);
}

void select_preset(int preset) {
    if (!stereo.power_on) return;
    
    if (stereo.current_mode == MODE_RADIO) {
        if (preset < MAX_STATIONS) {
            stereo.current_station = preset;
            printf("\n📻 Preset %d: %.1f FM - %s\n", 
                   preset + 1,
                   radio_stations[preset].frequency,
                   radio_stations[preset].name);
            
            if (!stereo.is_playing) {
                stereo.is_playing = 1;
                printf("▶️  Auto-playing preset station\n");
            }
        } else {
            printf("\n❌ Invalid preset number\n");
        }
    } else if (stereo.current_mode == MODE_USB) {
        if (preset < get_playlist_size()) {
            stereo.current_track = preset;
            printf("\n🎵 Track %d: %s\n", 
                   preset + 1,
                   get_current_track_name());
            
            if (stereo.is_playing) {
                load_track(preset);
            }
        } else {
            printf("\n❌ Invalid track number\n");
        }
    } else {
        printf("\n❌ Presets not available in this mode\n");
    }
    
    sleep(1);
}

void display_radio_info() {
    if (stereo.current_mode != MODE_RADIO) return;
    
    printf("\n┌─── Radio Information ────────────────────────┐\n");
    printf("│ Current: %.1f FM - %s                 │\n",
           radio_stations[stereo.current_station].frequency,
           radio_stations[stereo.current_station].name);
    printf("│ Signal: [▓▓▓▓░] Strong                       │\n");
    printf("│ Stereo: Yes | RDS: Available                │\n");
    printf("└─────────────────────────────────────────────┘\n");
}
