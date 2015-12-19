all :
	-(ls build || mkdir build) > /dev/null 2>&1 && cd build && cmake .. && make && cd ..

clean :
	-rm -rf build > /dev/null 2 >&1
