CFLAGS=-Wall -Wextra
CWD=$(shell pwd)


all: retren tests

retren: build/bin build/obj ./engine glfw
	env PKG_CONFIG_PATH=$(CWD)/glfw/build/src gcc $(shell pkg-config --cflags glfw3) -c $(CWD)/engine/main.c -o $(CWD)/build/obj/retren.o $(CFLAGS) -I$(CWD)/engine/include -I$(CWD)/CLog -I$(CWD)/glfw/include -DCLOG_NO_CDECL -fPIC -I$(CWD)/glad/include
	env PKG_CONFIG_PATH=$(CWD)/glfw/build/src gcc $(shell pkg-config --cflags glfw3) -c $(CWD)/glad/src/glad.c -o $(CWD)/build/obj/glad.o -I$(CWD)/glad/include -fPIC
#	TODO: Find a way to make this static
	env PKG_CONFIG_PATH=$(CWD)/glfw/build/src gcc $(shell pkg-config --cflags glfw3) -shared -o $(CWD)/build/bin/libretren.so $(CWD)/build/obj/retren.o $(CWD)/build/obj/glad.o -L$(CWD)/glfw/build/src $(shell pkg-config --static --libs glfw3)

tests: build/bin ./src retren
	@echo
	@echo Compiling Tests
#	TODO: Replace RPATH with a dynamic library path
	gcc $(CWD)/src/main.c -o $(CWD)/build/bin/tester $(CFLAGS) -I$(CWD)/engine/include -L$(CWD)/build/bin/ -lretren -fPIC -Wl,--rpath=$(CWD)/build/bin
	g++ $(CWD)/src/test.cpp -o $(CWD)/build/bin/cpptest $(CFLAGS) -I$(CWD)/engine/include -L$(CWD)/build/bin -lretren -fPIC -Wl,--rpath=$(CWD)/build/bin

glfw:
	cmake -B $(CWD)/glfw/build -S ./glfw -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_INSTALL=OFF -DGLFW_USE_WAYLAND=1
	cmake --build $(CWD)/glfw/build

build/bin build/obj: build
	mkdir -p $@

build:
	mkdir -p $@
