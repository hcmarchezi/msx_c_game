#include<time.h>

// typedef struct {
// 	unsigned int  psg_channel;
// 	unsigned int* tones;
// 	unsigned int* delays;
// 	unsigned int  size;
// 	unsigned int  idx;
// 	clock_t clock_counter;
// } channel_track;

// music_channel_track* create_channel_track(
// 	unsigned int  psg_channel, 
// 	unsigned int* tones, unsigned int* delays, 
// 	unsigned int  size,  unsigned int idx,
// 	void (*set_psg)(unsigned int, unsigned int));

// unsigned char should_play_channel_track_note(channel_track* channel, clock_t clock_counter);

// void play_channel_track_note(channel_track* channel);



typedef struct {
	int tone;  // frequency (or so)
	int delay; // 64, 32, 16, 8, 4
} music_note;

typedef struct {
	music_note** channel_0;
	music_note** channel_1;
	int channel_0_count;
	int channel_1_count;
	int channel_0_idx;
	int channel_1_idx;
	clock_t channel_0_clock_counter; // limit in MSX is 0xFFFF
	clock_t channel_1_clock_counter; // limit 0xFFFF
} music_track;


music_note* c_music_note(int tone, int delay);

music_track* create_music_track(
	music_note** channel_0_notes, int channel_0_count, 
	music_note** channel_1_notes, int channel_1_count);

char should_play_note_channel_0(music_track* music);

char should_play_note_channel_1(music_track* music);

music_note* play_next_note_channel_0(music_track* music);

music_note* play_next_note_channel_1(music_track* music);


void dec_channel_0_clock_counter(music_track* music);

void dec_channel_1_clock_counter(music_track* music);

// clock_t start = clock();
//
// ... game loop ...
//
// clock_t end = clock()
//
// play_music_track(music, end - start, &command);
// if (command.is_channel_0_cmd) { psg_tone(command.channel_0); }
// if (command.is_channel_1_cmd) { psg_tone(command.channel_1); }