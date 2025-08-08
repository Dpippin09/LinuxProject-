#include "car_stereo.h"
#include <unistd.h>

// Global playlist array
MusicTrack playlist[MAX_TRACKS];
static int playlist_count = 0;

void init_playlist() {
    // Initialize sample music tracks
    playlist[0] = (MusicTrack){"track01.mp3", "Highway Dreams", "The Rockers"};
    playlist[1] = (MusicTrack){"track02.mp3", "City Lights", "Urban Sound"};
    playlist[2] = (MusicTrack){"track03.mp3", "Summer Breeze", "Chill Vibes"};
    playlist[3] = (MusicTrack){"track04.mp3", "Thunder Road", "Classic Band"};
    playlist[4] = (MusicTrack){"track05.mp3", "Digital Love", "Electronic Mix"};
    playlist[5] = (MusicTrack){"track06.mp3", "Country Mile", "Acoustic Soul"};
    playlist[6] = (MusicTrack){"track07.mp3", "Jazz Cafe", "Smooth Jazz Trio"};
    playlist[7] = (MusicTrack){"track08.mp3", "Rock Anthem", "Metal Gods"};
    playlist[8] = (MusicTrack){"track09.mp3", "Pop Star", "Dance Floor"};
    playlist[9] = (MusicTrack){"track10.mp3", "Blues Highway", "Old School Blues"};
    
    playlist_count = 10;
    printf("💾 Playlist initialized with %d tracks\n", playlist_count);
}

int get_playlist_size() {
    return playlist_count;
}

const char* get_current_track_name() {
    if (playlist_count == 0 || stereo.current_track >= playlist_count) {
        return "No track selected";
    }
    
    static char track_info[128];
    snprintf(track_info, sizeof(track_info), "%s - %s", 
             playlist[stereo.current_track].artist,
             playlist[stereo.current_track].title);
    
    return track_info;
}

void load_track(int track_index) {
    if (track_index < 0 || track_index >= playlist_count) {
        printf("❌ Invalid track index\n");
        return;
    }
    
    printf("💿 Loading: %s - %s\n", 
           playlist[track_index].artist,
           playlist[track_index].title);
    
    // Simulate loading time
    usleep(500000);
    
    printf("✅ Track loaded successfully\n");
}

void display_track_info() {
    if (stereo.current_mode != MODE_USB || playlist_count == 0) return;
    
    MusicTrack *current = &playlist[stereo.current_track];
    
    printf("\n┌─── Track Information ────────────────────────┐\n");
    printf("│ Title:  %-35s │\n", current->title);
    printf("│ Artist: %-35s │\n", current->artist);
    printf("│ File:   %-35s │\n", current->filename);
    printf("│ Track:  %d of %d                            │\n", 
           stereo.current_track + 1, playlist_count);
    
    // Simulate playback progress
    int progress = rand() % 100;
    printf("│ Progress: [");
    for (int i = 0; i < 30; i++) {
        if (i < (progress * 30 / 100)) {
            printf("█");
        } else {
            printf("░");
        }
    }
    printf("] %d%% │\n", progress);
    
    printf("└─────────────────────────────────────────────┘\n");
}

void add_track_to_playlist(const char* filename, const char* title, const char* artist) {
    if (playlist_count >= MAX_TRACKS) {
        printf("❌ Playlist is full\n");
        return;
    }
    
    strncpy(playlist[playlist_count].filename, filename, MAX_NAME_LEN - 1);
    strncpy(playlist[playlist_count].title, title, MAX_NAME_LEN - 1);
    strncpy(playlist[playlist_count].artist, artist, MAX_NAME_LEN - 1);
    
    playlist[playlist_count].filename[MAX_NAME_LEN - 1] = '\0';
    playlist[playlist_count].title[MAX_NAME_LEN - 1] = '\0';
    playlist[playlist_count].artist[MAX_NAME_LEN - 1] = '\0';
    
    playlist_count++;
    
    printf("✅ Added to playlist: %s - %s\n", artist, title);
}

void shuffle_playlist() {
    if (playlist_count <= 1) return;
    
    for (int i = playlist_count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        MusicTrack temp = playlist[i];
        playlist[i] = playlist[j];
        playlist[j] = temp;
    }
    
    stereo.current_track = 0;
    printf("🔀 Playlist shuffled\n");
}
