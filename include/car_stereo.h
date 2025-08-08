#ifndef CAR_STEREO_H
#define CAR_STEREO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_VOLUME 30
#define MIN_VOLUME 0
#define MAX_STATIONS 10
#define MAX_TRACKS 50
#define MAX_NAME_LEN 64

// Audio modes
typedef enum {
    MODE_RADIO = 0,
    MODE_USB,
    MODE_BLUETOOTH,
    MODE_AUX
} AudioMode;

// Radio station structure
typedef struct {
    float frequency;
    char name[MAX_NAME_LEN];
} RadioStation;

// Music track structure
typedef struct {
    char filename[MAX_NAME_LEN];
    char title[MAX_NAME_LEN];
    char artist[MAX_NAME_LEN];
} MusicTrack;

// Main stereo structure
typedef struct {
    int power_on;
    int volume;
    AudioMode current_mode;
    int current_station;
    int current_track;
    int is_playing;
    int bass;        // -10 to +10
    int treble;      // -10 to +10
    int balance;     // -10 to +10 (L to R)
} CarStereo;

// Global variables
extern CarStereo stereo;
extern RadioStation radio_stations[MAX_STATIONS];
extern MusicTrack playlist[MAX_TRACKS];

// Function prototypes

// Power and basic controls
void toggle_power(void);
void adjust_volume(int change);
void next_mode(void);
const char* get_mode_name(AudioMode mode);

// Audio playback
void toggle_play(void);
void next_track(void);
void previous_track(void);

// Radio functions
void init_radio(void);
void scan_stations(void);
void select_preset(int preset);

// USB/Playlist functions
void init_playlist(void);
int get_playlist_size(void);
const char* get_current_track_name(void);
void load_track(int track_index);

// Audio processing
void apply_audio_effects(void);
void show_eq_menu(void);
void adjust_bass(int change);
void adjust_treble(int change);
void adjust_balance(int change);

// Display functions
void display_track_info(void);
void display_radio_info(void);
void show_system_info(void);

#endif // CAR_STEREO_H
