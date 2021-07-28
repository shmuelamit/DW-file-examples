build:
	gcc -Wall fsop.c -o bin/fsop \
		-Wl,--rpath="." \
		-Wl,--dynamic-linker="ld-2.23.so"

run:
	gcc -Wall fsop.c -o bin/fsop \
		-Wl,--rpath="." \
		-Wl,--dynamic-linker="ld-2.23.so" \
		-ldl
	./bin/fsop