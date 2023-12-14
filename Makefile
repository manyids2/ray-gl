init:
	mkdir -p build;
	cd build && cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1;
	cd build && make -j 6;

run:
	cd build && make -j 1;
	./build/ray-gl;

clean:
	rm -r ./build;
