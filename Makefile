ROOT = $(realpath $(shell dirname $(firstword $(MAKEFILE_LIST))))

CLIENT_ARGS = --assets_folder ${ROOT}/assets

bootstrap:
	git submodule update --init
	cd build && cmake ../ && make

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
brcf: bclientf bclientf rclient

# build fast and run server
brsf: bserverf rserver bsharedf

rclient:
	./bin/SouljaClient ${CLIENT_ARGS}

rserver:
	./bin/Soulja

run:
	./bin/Soulja

client:
	./bin/SouljaClient ${CLIENT_ARGS}
