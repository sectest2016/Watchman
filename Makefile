all:
	make benchmark
	make adjacent_buffer
	make char_pointer_arg

all-ld:
	make ld_preload
	make unprotected_heap

adjacent_buffer:
	g++ -I./ -g -o adjacent_buffer.bin -fstack-protector-all tests/adjacent_buffer.cpp #-finstrument-functions
	gcc -I./ tests/adjacent_buffer.cpp -E >> adjacent_buffer_expanded.cpp 

char_pointer_arg:
	g++ -I./ -g -o paid_char_pointer_arg.bin -fstack-protector-all tests/paid_char_pointer_arg.cpp #-finstrument-functions
	gcc -I./ tests/paid_char_pointer_arg.cpp -E >> char_pointer_arg_expanded.cpp 

heap:
	g++ -I./ -g -o heap.bin -fstack-protector-all tests/paid_heap.cpp -finstrument-functions
	gcc -I./ tests/paid_heap.cpp -E >> heap_expanded.cpp

benchmark:
	g++ -I./ -g -o benchmark.bin -fstack-protector-all tests/benchmark.cpp #-finstrument-functions
	gcc -I./ tests/benchmark.cpp -E >> benchmark_expanded.cpp 

ld_preload:
	#-DRUNTIME -shared -o
	gcc -c -fPIC paid_secure_heap_ld_preload.c -D_GNU_SOURCE -o nightwatchman.o	
	gcc -shared -o nightwatchman.so nightwatchman.o

	#g++ -c -fPIC testLibrary.cpp -o testLibrary.o
	#g++ -shared -o testLibrary.so testLibrary.o
	
	#gcc -ldl -O2 -Wall -shared -Wl paid_secure_heap_ld_preload.c -D_GNU_SOURCE -fPIC -o nightwatchman.so 
	#LIBS=-ldl
	#gcc -ldl -O2 -Wall -fPIC -D_GNU_SOURCE -shared -Wl,--no-as-needed paid_secure_heap_ld_preload.c -o nightwatchman.so 

unprotected_heap:
	g++ -I./ -g -o unprotected_heap.bin -fstack-protector-all tests/paid_unprotected_heap.cpp -finstrument-functions

clean:
	rm -f *.bin *.o *.so *_expanded.cpp benchmark
