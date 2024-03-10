#ifndef test_helper_h
#define test_helper_h

#define SCREEN_CHAR_SIZE 768

int vpoke_idx;
int vpoke_mem[SCREEN_CHAR_SIZE];
int vpoke_val[SCREEN_CHAR_SIZE];

int init_vpoke_func() {
	vpoke_idx = 0;
	for (unsigned int idx =0; idx < SCREEN_CHAR_SIZE; idx++) {
		vpoke_mem[idx] = 0;
		vpoke_val[idx] = 0;
	}
}

int vpoke_func(int mem, int val) {
	vpoke_mem[vpoke_idx] = mem;
	vpoke_val[vpoke_idx] = val;
	vpoke_idx++;	
}

#endif
