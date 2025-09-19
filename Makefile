.PHONY: build

all: setup cmake

setup:
	git submodule update --init --recursive

cmake:
	cmake -B build -S . -G Ninja ../

c: bc rc

bc:
	ninja -C build

rc:
	./bin/Client
