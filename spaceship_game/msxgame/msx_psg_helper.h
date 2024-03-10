#ifndef MSX_PSG_HELPER_H
#define MSX_PSG_HELPER_H

unsigned int map_note_to_tone(int octave, char note) {
	if (octave == 1) {
		switch (note) {
			case 'C': return 0xD5D;
			case 'D': return 0xBE7;
			case 'E': return 0xA9B;
			case 'F': return 0xA02;
			case 'G': return 0x8EB;
			case 'A': return 0x7F2;
			case 'B': return 0x714;
			default: 
				//printf("ERROR: unknown music note %c", note); 
				return 0;
		}

	} else if (octave == 2) {
		switch (note) {
			case 'C': return 0x6AF;
			case 'D': return 0x5F4;
			case 'E': return 0x54E;
			case 'F': return 0x501;
			case 'G': return 0x476;
			case 'A': return 0x3F9;
			case 'B': return 0x38A;
			default: 
				//printf("ERROR: unknown music note %c", note); 
				return 0;
		}

	} else if (octave == 3) {
		switch (note) {
			case 'C': return 0x357;
			case 'D': return 0x2FA;
			case 'E': return 0x2A7;
			case 'F': return 0x281;
			case 'G': return 0x23B;
			case 'A': return 0x1FD;
			case 'B': return 0x1C5;
			default: 
				//printf("ERROR: unknown music note %c", note); 
				return 0;
		}

	} else if (octave == 4) {
		switch (note) {
			case 'C': return 0x1AC;
			case 'D': return 0x17D;
			case 'E': return 0x153;
			case 'F': return 0x140;
			case 'G': return 0x11D;
			case 'A': return 0x0FE;
			case 'B': return 0x0E3;
			default: 
				//printf("ERROR: unknown music note %c", note); 
				return 0;
		}
	} else if (octave == 5) {
		switch (note) {
			case 'C': return 0x0D6;
			case 'D': return 0x0BE;
			case 'E': return 0x0AA;
			case 'F': return 0x0A0;
			case 'G': return 0x08F;
			case 'A': return 0x07F;
			case 'B': return 0x071;
			default: 
				//printf("ERROR: unknown music note %c", note); 
				return 0;
		}
	} else if (octave == 6) {
		switch (note) {
			case 'C': return 0x06B;
			case 'D': return 0x05F;
			case 'E': return 0x055;
			case 'F': return 0x050;
			case 'G': return 0x047;
			case 'A': return 0x040;
			case 'B': return 0x039;
			default: 
				//printf("ERROR: unknown music note %c", note); 
				return 0;
		}
	} else {
		//printf("ERROR: unknown octave (range 1-6)");
		return 0;
	}

	// C		C#		D		D#		E		F		F#		G		G#		A		A#		B		Octave
	// 0xD5D	0xC9C	0xBE7	0xB3C	0xA9B	0xA02	0x973	0x8EB	0x86B	0x7F2	0x780	0x714	// o1
	// 0x6AF	0x64E	0x5F4	0x59E	0x54E	0x501	0x4BA	0x476	0x436	0x3F9	0x3C0	0x38A	// o2
	// 0x357	0x327	0x2FA	0x2CF	0x2A7	0x281	0x25D	0x23B	0x21B	0x1FD	0x1E0	0x1C5	// o3
	// 0x1AC	0x194	0x17D	0x168	0x153	0x140	0x12E	0x11D	0x10D	0x0FE*	0x0F0	0x0E3	// o4
	// 0x0D6	0x0CA	0x0BE	0x0B4	0x0AA	0x0A0	0x097	0x08F	0x087	0x07F	0x078	0x071	// o5

	// 0x06B	0x065	0x05F	0x05A	0x055	0x050	0x04C	0x047	0x043	0x040	0x03C	0x039	// o6
	// 0x035	0x032	0x030	0x02D	0x02A	0x028	0x026	0x024	0x022	0x020	0x01E	0x01C	// o7
	// 0x01B	0x019	0x018	0x016	0x015	0x014	0x013	0x012	0x011	0x010	0x00F	0x00E	// o8
}

void map_notes_to_tones(int octave, char* notes, unsigned int note_count, unsigned int* tones) {
	for(int index=0; index < note_count; index++) {
		tones[index] = map_note_to_tone(octave, notes[index]);
	}
}

#endif