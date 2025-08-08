#include "car_stereo.h"
#include <unistd.h>

void apply_audio_effects() {
    if (!stereo.power_on) return;
    
    printf("🎚️  Applying audio effects...\n");
    printf("   Bass: %+d dB\n", stereo.bass);
    printf("   Treble: %+d dB\n", stereo.treble);
    printf("   Balance: %+d (L/R)\n", stereo.balance);
    
    // Simulate processing delay
    usleep(300000);
    printf("✅ Audio effects applied\n");
}

void show_eq_menu() {
    if (!stereo.power_on) return;
    
    printf("\n╔═══════════════════════════════════════════════╗\n");
    printf("║                 EQUALIZER                     ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
    
    printf("\nCurrent Settings:\n");
    printf("Bass:    %+2d dB [", stereo.bass);
    for (int i = -10; i <= 10; i++) {
        if (i == stereo.bass) {
            printf("█");
        } else if (abs(i - stereo.bass) <= 1) {
            printf("▓");
        } else {
            printf("░");
        }
    }
    printf("]\n");
    
    printf("Treble:  %+2d dB [", stereo.treble);
    for (int i = -10; i <= 10; i++) {
        if (i == stereo.treble) {
            printf("█");
        } else if (abs(i - stereo.treble) <= 1) {
            printf("▓");
        } else {
            printf("░");
        }
    }
    printf("]\n");
    
    printf("Balance: %+2d    [", stereo.balance);
    for (int i = -10; i <= 10; i++) {
        if (i == stereo.balance) {
            printf("█");
        } else if (abs(i - stereo.balance) <= 1) {
            printf("▓");
        } else {
            printf("░");
        }
    }
    printf("] (L/R)\n");
    
    printf("\nPresets:\n");
    printf("[1] Rock    [2] Pop     [3] Jazz    [4] Classical\n");
    printf("[5] Bass+   [6] Vocal   [7] Flat    [8] Custom\n");
    
    printf("\nControls:\n");
    printf("[Z/X] Bass  [C/V] Treble  [B/N] Balance  [R] Reset  [ESC] Back\n");
    
    char input;
    while ((input = getchar()) != 27) { // ESC key
        switch (input) {
            case 'z': case 'Z':
                adjust_bass(-1);
                break;
            case 'x': case 'X':
                adjust_bass(1);
                break;
            case 'c': case 'C':
                adjust_treble(-1);
                break;
            case 'v': case 'V':
                adjust_treble(1);
                break;
            case 'b': case 'B':
                adjust_balance(-1);
                break;
            case 'n': case 'N':
                adjust_balance(1);
                break;
            case 'r': case 'R':
                stereo.bass = 0;
                stereo.treble = 0;
                stereo.balance = 0;
                printf("🔄 EQ Reset to flat\n");
                break;
            case '1':
                stereo.bass = 5; stereo.treble = 3; stereo.balance = 0;
                printf("🎸 Rock preset applied\n");
                break;
            case '2':
                stereo.bass = 2; stereo.treble = 4; stereo.balance = 0;
                printf("🎤 Pop preset applied\n");
                break;
            case '3':
                stereo.bass = -2; stereo.treble = 2; stereo.balance = 0;
                printf("🎺 Jazz preset applied\n");
                break;
            case '4':
                stereo.bass = -3; stereo.treble = -1; stereo.balance = 0;
                printf("🎼 Classical preset applied\n");
                break;
            case '5':
                stereo.bass = 8; stereo.treble = -2; stereo.balance = 0;
                printf("🔊 Bass+ preset applied\n");
                break;
            case '6':
                stereo.bass = -1; stereo.treble = 6; stereo.balance = 0;
                printf("🎙️  Vocal preset applied\n");
                break;
            case '7':
                stereo.bass = 0; stereo.treble = 0; stereo.balance = 0;
                printf("📊 Flat preset applied\n");
                break;
            default:
                continue;
        }
        
        apply_audio_effects();
        sleep(1);
        show_eq_menu();
        break;
    }
}

void adjust_bass(int change) {
    stereo.bass += change;
    if (stereo.bass > 10) stereo.bass = 10;
    if (stereo.bass < -10) stereo.bass = -10;
    
    printf("🎵 Bass: %+d dB\n", stereo.bass);
    apply_audio_effects();
}

void adjust_treble(int change) {
    stereo.treble += change;
    if (stereo.treble > 10) stereo.treble = 10;
    if (stereo.treble < -10) stereo.treble = -10;
    
    printf("🎵 Treble: %+d dB\n", stereo.treble);
    apply_audio_effects();
}

void adjust_balance(int change) {
    stereo.balance += change;
    if (stereo.balance > 10) stereo.balance = 10;
    if (stereo.balance < -10) stereo.balance = -10;
    
    printf("🎵 Balance: %+d %s\n", abs(stereo.balance), 
           stereo.balance < 0 ? "(Left)" : 
           stereo.balance > 0 ? "(Right)" : "(Center)");
    apply_audio_effects();
}

void show_system_info() {
    printf("\n╔═══════════════════════════════════════════════╗\n");
    printf("║              SYSTEM INFORMATION               ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
    
    printf("\nHardware:\n");
    printf("• CPU: ARM Cortex-A72 (Quad Core)\n");
    printf("• RAM: 4GB DDR4\n");
    printf("• Storage: 32GB eMMC + SD Card Slot\n");
    printf("• Audio: 24-bit/192kHz DAC\n");
    printf("• Display: 7\" Touchscreen (800x480)\n");
    
    printf("\nConnectivity:\n");
    printf("• Bluetooth 5.0\n");
    printf("• Wi-Fi 802.11ac\n");
    printf("• USB 3.0 x2\n");
    printf("• 3.5mm AUX Input\n");
    printf("• FM/AM Radio Tuner\n");
    
    printf("\nSoftware:\n");
    printf("• Linux Kernel 5.15+\n");
    printf("• Custom Car Stereo OS\n");
    printf("• ALSA Audio System\n");
    printf("• PulseAudio Server\n");
    printf("• GStreamer Media Framework\n");
    
    printf("\nFeatures:\n");
    printf("• Multi-source Audio Playback\n");
    printf("• 10-Band Graphic Equalizer\n");
    printf("• Bluetooth Hands-free Calling\n");
    printf("• USB Mass Storage Support\n");
    printf("• Internet Radio Streaming\n");
    
    printf("\nPress any key to continue...\n");
    getchar();
}
