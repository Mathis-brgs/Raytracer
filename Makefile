.PHONY: build run test clean

build:
	cmake -S . -B build -G Ninja
	cmake --build build

run: build
	./build/raytracer

test: build
	ctest --test-dir build --output-on-failure

clean:
	rm -rf build
