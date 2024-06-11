CFLAGS=-Wall -Wextra



all: retren tester

retren: build/obj build/bin ./engine
	gcc -c ./engine/main.c -o build/obj/engine.o $(CFLAGS) -I./engine/include
	ar rcs ./build/bin/libretren.a build/obj/engine.o

tester: build/bin ./src retren
	gcc ./src/main.c -o build/bin/tester $(CFLAGS) -I./engine/include -L./build/bin/ -lretren

build/obj build/bin: build
	mkdir -p $@

build:
	mkdir -p $@
