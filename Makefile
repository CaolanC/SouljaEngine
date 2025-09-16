bootstrap:
	git submodule update --init
	cmake -B build -S . -G Ninja ../

cmake:
	cmake -B build -S . -G Ninja ../

.PHONY: build

build:
	ninja -C build

c:
	./bin/Client
