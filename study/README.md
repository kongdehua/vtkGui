## Using and understanding the Valgrind core

This chapter describe Valgrind core services, command-line options and behaviours. That means it is relevant regardless of what particular tool you are using. The information should be sufficient for you to make effective day-to-day use of Valgrind.

	A point to terminology: most references to "Valgrind" in this chapter refer to the Valgrind core services.

### 2.1. What Valgrind does with your program

Valgrind is designed to be non-intrusive as possible. It works directly with existing executables. You don't need to recompile, relink, or otherwise modify the program to be checked.

You invoke Valgrind like this:
	
	valgrind [valgrind-options] your-prog [your-prog-options]
