#include "ship_music_track.h"


char track_1_channel_0_notes[] = "DFAFDFAFDFAFDFAFCFAFCFAFCFAFCFAF";
char track_1_channel_1_notes[] = "AAAAAAFDAAAAAAFACCCCCCFFCCCCCCFF";
unsigned int track_1_note_count = 32;

unsigned int track_1_channel_0_tones[32];
unsigned int track_1_channel_1_tones[32];

void create_music_track_1(music_tones* tones) {
    map_notes_to_tones(3, track_1_channel_0_notes, track_1_note_count, track_1_channel_0_tones);
    map_notes_to_tones(4, track_1_channel_1_notes, track_1_note_count, track_1_channel_1_tones);
    create_music_tones(tones, track_1_channel_0_tones, track_1_channel_1_tones, track_1_note_count);
}

char track_2_channel_0_notes[] = "CCCCCCCCFFFFFFFFGGGGGGGGFFFFFFFF";
char track_2_channel_1_notes[] = "CEGECEGECFAFCFAFDGBGDGBGCFAFCFAF";
unsigned int track_2_note_count = 32;

unsigned int track_2_channel_0_tones[32];
unsigned int track_2_channel_1_tones[32];

void create_music_track_2(music_tones* tones) {
    map_notes_to_tones(3, track_2_channel_0_notes, track_2_note_count, track_2_channel_0_tones);
    map_notes_to_tones(4, track_2_channel_1_notes, track_2_note_count, track_2_channel_1_tones);
    create_music_tones(tones, track_2_channel_0_tones, track_2_channel_1_tones, track_2_note_count);
}


char track_3_channel_0_notes[] = "CCCCCCCCFFFFFFFFGGGGGGGGAAAAAAAA";
char track_3_channel_1_notes[] = "CGCCGCGCFAFFAFAFDGDDGDGDEAEEAEAE";
unsigned int track_3_note_count = 32;

unsigned int track_3_channel_0_tones[32];
unsigned int track_3_channel_1_tones[32];

void create_music_track_3(music_tones* tones) {
    map_notes_to_tones(3, track_3_channel_0_notes, track_3_note_count, track_3_channel_0_tones);
    map_notes_to_tones(4, track_3_channel_1_notes, track_3_note_count, track_3_channel_1_tones);
    create_music_tones(tones, track_3_channel_0_tones, track_3_channel_1_tones, track_3_note_count);
}

