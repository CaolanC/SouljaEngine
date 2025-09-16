.PHONY: build

bootstrap:
	git submodule update --init
	cmake -B build -S . -G Ninja ../

cmake:
	cmake -B build -S . -G Ninja ../

c: bc rc

bc:
	ninja -C build

rc:
	./bin/Client
