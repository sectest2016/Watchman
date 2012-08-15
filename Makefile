main:
	g++ -g -o benchmark -fstack-protector-all benchmark.cpp #-finstrument-functions
	g++ -g -o security_check -fstack-protector-all benchmark.cpp #-finstrument-functions

pre:
	gcc security_check.cpp -E >> out.cpp 

clean:
	rm -f security_check benchmark out.cpp
