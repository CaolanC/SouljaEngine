bootstrap:
	cd build && cmake ../ && make

.PHONY: build 
build:
	make -C build all

bclient:
	make -C build SouljaClient

bserver:
	make -C build Soulja

# build and run client
brc: bclient rclient

# build and run server
brs: bserver rserver

rclient:
	./bin/SouljaClient

rserver:
	./bin/Soulja

run:
	./bin/Soulja

client:
	./bin/SouljaClient
