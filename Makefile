bootstrap:
	cd build && cmake ../ && make

.PHONY: build 
build:
	make -C build all

bclient:
	make -C build SouljaClient

bserver:
	make -C build Soulja/

bclientf:
	make -C build SouljaClient/fast

bserverf:
	make -C build Soulja/fast

# build and run client
brc: bclientf rclient

# build and run server
brs: bserverf rserver

rclient:
	./bin/SouljaClient

rserver:
	./bin/Soulja

run:
	./bin/Soulja

client:
	./bin/SouljaClient
