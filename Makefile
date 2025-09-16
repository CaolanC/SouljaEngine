.PHONY: build

bootstrap:
	cmake -B build -S . -G Ninja ../

cmake:
	cmake -B build -S . -G Ninja ../

c: bc rc

bc:
	ninja -C build

rc:
	./bin/Client
