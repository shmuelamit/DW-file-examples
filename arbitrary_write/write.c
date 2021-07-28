#include <stdio.h>

#define _IO_CURRENTLY_PUTTING 0x800
#define _IO_IS_APPENDING 0x1000
 
int main() {
	struct _IO_FILE *fp = fopen("lorem_ipsum.txt", "w");
	char buf1[] = "Hello world!\n";
	char buf2[] = "Cyber cyber cyber!\n";
 
	fp->_fileno = 1;
	fp->_flags |= _IO_CURRENTLY_PUTTING | _IO_IS_APPENDING;
	fp->_IO_write_base = buf2;
	fp->_IO_write_ptr = buf2 + sizeof(buf2);
	fp->_IO_write_end = buf2 + sizeof(buf2);
 
	fwrite(buf1, sizeof(buf1), 1, fp);
}
