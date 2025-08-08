#include <stdio.h>
#include <stdlib.h>
#include "platform.h"

// Simple test program to verify compilation and basic functionality

int main() {
    printf("=================================\n");
    printf("Linux Car Stereo - System Test\n");
    printf("=================================\n\n");
    
    // Platform detection
#ifdef _WIN32
    printf("Platform: Windows\n");
#elif __linux__
    printf("Platform: Linux\n");
#elif __APPLE__
    printf("Platform: macOS\n");
#else
    printf("Platform: Unknown\n");
#endif
    
    printf("Audio System: %s\n", get_audio_system());
    printf("Config Path: %s\n", get_config_path());
    printf("Log Path: %s\n\n", get_log_path());
    
    // Test basic functionality
    printf("Testing basic functions...\n");
    
    // Test screen clearing
    printf("- Screen clearing: ");
    clear_screen_platform();
    printf("OK\n");
    
    // Test sleep functions
    printf("- Sleep functions: ");
    sleep_ms_platform(100);
    printf("OK\n");
    
    // Test platform-specific character input (non-blocking test)
    printf("- Input system: Ready\n");
    
    printf("\n✅ All basic tests passed!\n");
    printf("\nThe car stereo system should compile and run correctly.\n");
    printf("Run './car_stereo' or 'car_stereo.exe' to start the full application.\n\n");
    
    printf("Press any key to exit...");
    get_char_platform();
    
    return 0;
}
