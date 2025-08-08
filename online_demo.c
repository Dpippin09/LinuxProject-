#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simplified Car Stereo Demo for Online Compilers
// Copy and paste this into: https://repl.it/languages/c or https://onlinegdb.com

typedef enum {
    MODE_RADIO = 0,
    MODE_USB,
    MODE_BLUETOOTH,
    MODE_AUX
} AudioMode;

typedef struct {
    int power_on;
    int volume;
    AudioMode current_mode;
    int current_station;
    int is_playing;
} CarStereo;

CarStereo stereo = {1, 15, MODE_RADIO, 0, 1};

const char* stations[] = {
    "88.5 FM - Rock FM",
    "92.1 FM - Pop Hits", 
    "95.7 FM - Classic Rock",
    "98.3 FM - Jazz Lounge",
    "101.1 FM - Hip Hop"
};

const char* tracks[] = {
    "Highway Dreams - The Rockers",
    "City Lights - Urban Sound",
    "Summer Breeze - Chill Vibes",
    "Thunder Road - Classic Band",
    "Digital Love - Electronic Mix"
};

const char* get_mode_name(AudioMode mode) {
    switch(mode) {
        case MODE_RADIO: return "RADIO";
        case MODE_USB: return "USB";
        case MODE_BLUETOOTH: return "BLUETOOTH";
        case MODE_AUX: return "AUX";
        default: return "UNKNOWN";
    }
}

void show_interface() {
    printf("\n╔═══════════════════════════════════════════════╗\n");
    printf("║              LINUX CAR STEREO                ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
    
    printf("\n┌─── Status ───────────────────────────────────┐\n");
    printf("│ Power: %s | Volume: %02d | Mode: %s    │\n", 
           stereo.power_on ? "ON " : "OFF", 
           stereo.volume,
           get_mode_name(stereo.current_mode));
    
    if (stereo.current_mode == MODE_RADIO) {
        printf("│ %s %s                     │\n",
               stations[stereo.current_station],
               stereo.is_playing ? "♪" : " ");
    } else if (stereo.current_mode == MODE_USB) {
        printf("│ %s %s                     │\n",
               tracks[stereo.current_station],
               stereo.is_playing ? "♪" : "⏸");
    }
    
    printf("└─────────────────────────────────────────────┘\n");
    
    // Volume indicator
    printf("\nVolume: [");
    for (int i = 0; i < 20; i++) {
        if (i < (stereo.volume * 20 / 30)) {
            printf("█");
        } else {
            printf("░");
        }
    }
    printf("] %d/30\n", stereo.volume);
}

void demo_interactions() {
    printf("\n🎵 DEMO: Car Stereo Interactions\n");
    printf("================================\n");
    
    // Show initial state
    show_interface();
    
    // Demo volume change
    printf("\n🔊 Increasing volume...\n");
    stereo.volume = 20;
    show_interface();
    
    // Demo mode switch
    printf("\n📻 Switching to USB mode...\n");
    stereo.current_mode = MODE_USB;
    show_interface();
    
    // Demo station/track change
    printf("\n⏭️ Next track...\n");
    stereo.current_station = 1;
    show_interface();
    
    // Demo pause
    printf("\n⏸️ Pausing playback...\n");
    stereo.is_playing = 0;
    show_interface();
    
    printf("\n✨ This is what the full car stereo looks like!\n");
    printf("   In the complete version, you can:\n");
    printf("   • Control with keyboard (P, +/-, M, Space, etc.)\n");
    printf("   • Access 10 radio stations\n");
    printf("   • Play 10 music tracks\n");
    printf("   • Use 3-band equalizer\n");
    printf("   • Switch between 4 audio modes\n");
}

int main() {
    printf("🚗🎵 Linux Car Stereo - Online Demo\n");
    printf("===================================\n");
    
    demo_interactions();
    
    printf("\n🌐 Try the full version:\n");
    printf("   1. Install WSL or MinGW on Windows\n");
    printf("   2. Clone: https://github.com/Dpippin09/LinuxProject-\n");
    printf("   3. Build and run the complete interactive version!\n");
    
    return 0;
}
