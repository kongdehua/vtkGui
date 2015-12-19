all : 
	-(ls build > /dev/null 2>&1 || mkdir build) && cd build && cmake .. && make && cd ..

clean:
	-(ls build > /dev/null 2>&1 && rm -rf build) || echo  
	-(ls tags  > /dev/null 2>&1 && rm -rf tags) || echo
