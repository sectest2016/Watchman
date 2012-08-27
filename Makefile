all:
	make benchmark
	make adjacent_buffer
	make char_pointer_arg

adjacent_buffer:
	g++ -I./ -g -o adjacent_buffer.bin -fstack-protector-all tests/paid_adjacent_buffer.cpp #-finstrument-functions
	gcc -I./ tests/paid_adjacent_buffer.cpp -E >> adjacent_buffer_expanded.cpp 

char_pointer_arg:
	g++ -I./ -g -o char_pointer_arg.bin -fstack-protector-all tests/char_pointer_arg.cpp #-finstrument-functions
	gcc -I./ tests/char_pointer_arg.cpp -E >> char_pointer_arg_expanded.cpp 

heap:
	g++ -I./ -g -o heap.bin -fstack-protector-all tests/paid_heap.cpp -finstrument-functions
	gcc -I./ tests/paid_heap.cpp -E >> heap_expanded.cpp

benchmark:
	g++ -I./ -g -o benchmark.bin -fstack-protector-all tests/benchmark.cpp #-finstrument-functions
	gcc -I./ tests/benchmark.cpp -E >> benchmark_expanded.cpp 

clean:
	rm -f *.bin *_expanded.cpp
