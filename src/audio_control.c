#include "car_stereo.h"
#include "platform.h"

void toggle_power() {
    stereo.power_on = !stereo.power_on;
    if (!stereo.power_on) {
        stereo.is_playing = 0;
        printf("\n🔌 Stereo powered OFF\n");
    } else {
        printf("\n🔌 Stereo powered ON\n");
    }
    sleep_sec_platform(1);
}

void adjust_volume(int change) {
    if (!stereo.power_on) return;
    
    stereo.volume += change;
    
    if (stereo.volume > MAX_VOLUME) stereo.volume = MAX_VOLUME;
    if (stereo.volume < MIN_VOLUME) stereo.volume = MIN_VOLUME;
    
    printf("\n🔊 Volume: %d\n", stereo.volume);
    
    // Visual volume indicator
    printf("Volume: [");
    for (int i = 0; i < 20; i++) {
        if (i < (stereo.volume * 20 / MAX_VOLUME)) {
            printf("█");
        } else {
            printf("░");
        }
    }
    printf("]\n");
    
    sleep(1);
}

void next_mode() {
    if (!stereo.power_on) return;
    
    stereo.current_mode = (stereo.current_mode + 1) % 4;
    stereo.is_playing = 0; // Stop playback when changing modes
    
    printf("\n📻 Mode: %s\n", get_mode_name(stereo.current_mode));
    
    switch (stereo.current_mode) {
        case MODE_RADIO:
            printf("📡 Switching to FM Radio\n");
            break;
        case MODE_USB:
            printf("💾 Switching to USB Mode\n");
            break;
        case MODE_BLUETOOTH:
            printf("📱 Switching to Bluetooth\n");
            break;
        case MODE_AUX:
            printf("🔌 Switching to AUX Input\n");
            break;
    }
    
    sleep(1);
}

const char* get_mode_name(AudioMode mode) {
    switch (mode) {
        case MODE_RADIO: return "RADIO";
        case MODE_USB: return "USB";
        case MODE_BLUETOOTH: return "BLUETOOTH";
        case MODE_AUX: return "AUX";
        default: return "UNKNOWN";
    }
}

void toggle_play() {
    if (!stereo.power_on) return;
    
    stereo.is_playing = !stereo.is_playing;
    
    if (stereo.is_playing) {
        printf("\n▶️  Playing");
        switch (stereo.current_mode) {
            case MODE_RADIO:
                printf(" - %.1f FM", radio_stations[stereo.current_station].frequency);
                break;
            case MODE_USB:
                if (get_playlist_size() > 0) {
                    printf(" - %s", get_current_track_name());
                }
                break;
            case MODE_BLUETOOTH:
                printf(" - Bluetooth Audio");
                break;
            case MODE_AUX:
                printf(" - AUX Input");
                break;
        }
        printf("\n");
    } else {
        printf("\n⏸️  Paused\n");
    }
    
    sleep(1);
}

void next_track() {
    if (!stereo.power_on) return;
    
    switch (stereo.current_mode) {
        case MODE_RADIO:
            stereo.current_station = (stereo.current_station + 1) % MAX_STATIONS;
            printf("\n📻 Station: %.1f FM - %s\n", 
                   radio_stations[stereo.current_station].frequency,
                   radio_stations[stereo.current_station].name);
            break;
        case MODE_USB:
            if (get_playlist_size() > 0) {
                stereo.current_track = (stereo.current_track + 1) % get_playlist_size();
                printf("\n⏭️  Next Track: %s\n", get_current_track_name());
                if (stereo.is_playing) {
                    load_track(stereo.current_track);
                }
            } else {
                printf("\n❌ No tracks available\n");
            }
            break;
        case MODE_BLUETOOTH:
            printf("\n⏭️  Bluetooth: Next track command sent\n");
            break;
        case MODE_AUX:
            printf("\n⏭️  AUX: Manual track control\n");
            break;
    }
    
    sleep(1);
}

void previous_track() {
    if (!stereo.power_on) return;
    
    switch (stereo.current_mode) {
        case MODE_RADIO:
            stereo.current_station = (stereo.current_station - 1 + MAX_STATIONS) % MAX_STATIONS;
            printf("\n📻 Station: %.1f FM - %s\n", 
                   radio_stations[stereo.current_station].frequency,
                   radio_stations[stereo.current_station].name);
            break;
        case MODE_USB:
            if (get_playlist_size() > 0) {
                stereo.current_track = (stereo.current_track - 1 + get_playlist_size()) % get_playlist_size();
                printf("\n⏮️  Previous Track: %s\n", get_current_track_name());
                if (stereo.is_playing) {
                    load_track(stereo.current_track);
                }
            } else {
                printf("\n❌ No tracks available\n");
            }
            break;
        case MODE_BLUETOOTH:
            printf("\n⏮️  Bluetooth: Previous track command sent\n");
            break;
        case MODE_AUX:
            printf("\n⏮️  AUX: Manual track control\n");
            break;
    }
    
    sleep(1);
}
