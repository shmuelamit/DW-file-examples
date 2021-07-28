build:
	gcc -Wall fsop.c -o bin/fsop \
		-Wl,--rpath="." \
		-Wl,--dynamic-linker="ld-2.27.so"

run:
	gcc -Wall fsop.c -o bin/fsop \
		-Wl,--rpath="." \
		-Wl,--dynamic-linker="ld-2.27.so" \
		-ldl
	./bin/fsop