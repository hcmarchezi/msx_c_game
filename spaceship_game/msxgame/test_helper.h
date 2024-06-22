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

void* vpoke_vwrite_data;
unsigned int vpoke_vwrite_mem_start;
unsigned int vpoke_vwrite_mem_count;

void init_vpoke_vwrite_func() {
	vpoke_vwrite_data = 0;
	vpoke_vwrite_mem_start = 0;
	vpoke_vwrite_mem_count = 0;
}

void vpoke_vwrite_func(void* data, unsigned int mem_start, unsigned int mem_count) {
	vpoke_vwrite_data = data;
	vpoke_vwrite_mem_start = mem_start;
	vpoke_vwrite_mem_count = mem_count;
}

#endif
