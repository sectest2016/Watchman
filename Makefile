all:
	make benchmark
	make adjacent_buffer
	make char_pointer_arg

adjacent_buffer:
	g++ -g -o adjacent_buffer.bin -fstack-protector-all adjacent_buffer.cpp #-finstrument-functions
	gcc adjacent_buffer.cpp -E >> adjacent_buffer_expanded.cpp 

char_pointer_arg:
	g++ -g -o char_pointer_arg.bin -fstack-protector-all char_pointer_arg.cpp #-finstrument-functions
	gcc char_pointer_arg.cpp -E >> char_pointer_arg_expanded.cpp 

benchmark:
	g++ -g -o benchmark.bin -fstack-protector-all benchmark.cpp #-finstrument-functions
	gcc benchmark.cpp -E >> benchmark_expanded.cpp 

clean:
	rm -f *.bin *_expanded.cpp
