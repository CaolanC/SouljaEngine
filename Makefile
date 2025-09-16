bootstrap:
	git submodule update --init
	cd build && cmake ../ -D CMAKE_CPP_COMPILER=/usr/bin/g++ && make

bootstrap_ubuntu_mint: linux_mint_sdl_dep bootstrap

linux_mint_sdl_dep:
	sudo apt-get install build-essential git make \
	pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
	libaudio-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
	libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev \
	libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
	libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev
.PHONY: build 
build:
	make -C build all

bclient:
	make -C build SouljaClient

bserver:
	make -C build Soulja/

bshared:
	make -C build SouljaSharedLib

bsharedf:
	make -C build SouljaSharedLib/fast

bclientf:
	make -C build SouljaClient/fast

bserverf:
	make -C build Soulja/fast

# build and run client
brc: bclient bshared rclient

# build and run server
brs: bserver rserver

bsl: bshared

# build fast and run client
brcf: bclientf bclientf rclient bsharedf

# build fast and run server
brsf: bserverf rserver bsharedf

rsb: rsandbox

rsandbox:
	./bin/SouljaTestSandbox

rclient:
	./bin/SouljaClient

rserver:
	./bin/Soulja

run:
	./bin/Soulja

client:
	./bin/SouljaClient ${CLIENT_ARGS}

c:
	make -C build Client
	./bin/Client
