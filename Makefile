.PHONY: build

all: setup cmake

setup:
	git submodule update --init --recursive

cmake:
	cmake -B build -S . -G Ninja ../

c: b rc

s: b rs

b:
	ninja -C build

rc:
	./bin/Client

rs:
	./bin/Server
