all:
	make unprotected_heap

#ld_preload:
	#-DRUNTIME -shared -o
#	gcc -g -c -fPIC watcher.c -D_GNU_SOURCE -o watchman.o	
#	gcc -g -shared -o watchman.so watchman.o

unprotected_heap:
	g++ -I./ -g -o unprotected_heap.bin -fstack-protector-all tests/paid_unprotected_heap.cpp 

clean:
	rm -f *.bin *.o *.so *_expanded.cpp 
