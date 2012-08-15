main:
	g++ -g -o first -fstack-protector-all firstexample.cpp #-finstrument-functions

pre:
	gcc firstexample.cpp -E >> out.cpp 

clean:
	rm -f first out.cpp

test:
	time ./first
