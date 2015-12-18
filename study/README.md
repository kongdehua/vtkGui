## Using and understanding the Valgrind core

This chapter describe Valgrind core services, command-line options and behaviours. That means it is relevant regardless of what particular tool you are using. The information should be sufficient for you to make effective day-to-day use of Valgrind.

	A point to terminology: most references to "Valgrind" in this chapter refer to the Valgrind core services.

### 2.1. What Valgrind does with your program

Valgrind is designed to be non-intrusive as possible. It works directly with existing executables. You don't need to recompile, relink, or otherwise modify the program to be checked.

You invoke Valgrind like this:
	
	valgrind [valgrind-options] your-prog [your-prog-options]

The most important option is *--tool* which dictate which Valgrind tool to run. For example, if want to run the command **`ls -l`** using the memory-checking tool Memcheck issue this command:

	valgrind --tool=memcheck ls -l

However, Memcheck is the default, so if you want to use it you can omit the --tool option.

Regardless of which tool is in use, Valgrind takes control of your program before it starts. Debugging information is read from the executable and associated libraries, so that error message and other outputs can be phrased in terms of source code locations, when appropriate.

Your program is then run on a synthetic CPU provided by the Valgrind core. As new code is executed for the first time, the core hands the code to the selected tool. The tool adds its own instrumentation code to this and hands the result back to the core, which coordinates the continued execution of this instrumented code.

The amount of instrumentation code added varies widely between tools. At one end of the scale, Memcheck adds code to check every memory access and every value computed, making it run 10-50 times slower than natively. At the other end of the spectrum, the minimal tool, called Nulgrind, adds no instrumentation at all adn causes in total "only" about a 4 times slowdown.

Valgrind simulates every single instruction your program executes. Because of this, the active tool checks, or profiles, not only the code in your application but also in all supporting dynamically-linked libraries, including the C library, graphical libraries, and so on.

If you're using an error-detection tool, Valgrind may detect errors in system libraries, for example the GNU C or X11 libraries, which you have to use. You might not be interested in these errors, since you probably have no control over that code. Therefore, Valgrind allows you to selectively suppress errors, by recording them in a suppressions file which is read when Valgrind starts up. The build mechanism selects default suppressions which give reasionable behavious for the OS and libraries detected on your machine. To make it easier to write suppressions, you can use the --gen-suppressions=yes option. This tells Valgrind to print out a suppression for each reported error, which you can then copy into a suppressions file.

Different error-checking tools report different kinds of errors. The suppression mechanism therefore allows you to say which tool or tools each suppression applies to.

### 2.2. Getting started

First off, consider whether it might be beneficial to recompile your application and supporting libraries with debugging info enabled (the -g option). Without debugging info, the best Valgrind tools will be able to do is guess wich function a particular piece of code belongs to, which makes both error messages and profiling output nearly useless. With -g, you'll get message which point directly to the relevant source code lines.

Another option you might like to consider, if you are working with C++, is -fno-inline. That makes it easier to see the function-call chain, which can help reduce confusion when navigating around large C++ apps. For example, debugging OpenOffice.org with Memcheck is a bit easier when using this option. You don't have to do this, but doing so help Valgrind produce more accurate and less confusing error reports. Chances are you're set up like this already, if you intended to debug your program with GNU GDB, or some other debugger. Alternatively, the Valgrind option --read-inline-info=yes instructs Valgrind to read the debug information describing inlining information. With this, function call chain will be properly shown, even when your application is compiled with inlining.

If you are planning to use Memcheck: On rare occasions, compiler optimisations (at -O2 and above, and sometimes -O1) have been observed to generate code which fools Memcheck into wrongly reporting uninitialised value errors, or missing uninitialised value errors. We have looked in detail into fixing this, and unfortunately the result is that doing so would give a further significant slowdown in what is already a slow tool. So the best solution is to turn off optimisation altogether. Since this often makes things unmanageably slow, a reasonable compromise is to use -O. This gets you the majority of the benefits of higher optimisation levels whilst keeping relatively small the chances of false positives or false negatives from Memcheck. Also, you should compile your code with -Wall because it can identify some or all of the probelms that Valgrind can miss at the higher optimisation levels. 

### 2.3. The Commentary

Valgrind tools write a commentary, a stream of text, detailing error reports and other significant events. All lines in the commentary have following form:

	===12345== some-message-from-Valgrind

The 12345 is the process ID. This scheme makes it easy to distinguish program output from valgrind commentary, and also easy to differntiate commentaries from different processes which have become meged together, for whatever reason.

By default, Valgrind tools write only essential messages to the commentary, so as to avoid flooding you with information of secondary importance. If you want more information about what is happening, re-run, passing the -v option to Valgrind. 

You candirect the commentary to three different places:

1. The default: send it to a file descriptor, which is by default 2 (stderr). So, if you give the core no options, it will write commentary to the standard error stream. If you want to send it to some other descriptor, for example number 9,you can specify --log-fd=9.

This is simplest and most common arrangement, but can cause probelms when Valgrinding entire trees of processes which expect specific file descriptors, particularly stdin/stdout/stderr, to be available for their own use.

2. A less intrusive option is to write the commentary to a file, which you specify by --log-file=filename. There are special format specifiers that can be used to use a process ID or an environment variable name in the log file name. These are useful/necessary if your program invokes multiple processes (especially for MPI programs). 

3. The least instrusive option is to send the commentary to a socket. //don't need.

Here is an important point about the relationship between the commentary and profiling output from tools. The commentary contains a mix of messages from the Valgrand core and the selected tool. If the tool reports errors, it will report them to the commentary. However, if the tool does profiling, the profile data will be written to a file of some kind, depending on the tool, and indepedent of what `--log-*` options are in force. The commentary is intended to be a low-bandwidth, human-readable channel. Profiling data, on the other hand, is usually voluminous and not meaningful without further processing, which is why we have chosen this arrangement.

### 2.4. Reporting of errors

When an error-checking tool detects something bad happen in the program, an error message is written to the commentary. Here's an example from Memcheck:

	==25832== Invalid read of size 4
	==25832== at 0x8048724: BandMatrix::ReSize(int, int, int) (bogon.cpp:45)
	==25832== by 0x80487AF: main (bogon.cpp:66)
	==25832== Address 0xBFFFF74C is not stack’d, malloc’d or free’d

This message says that the program did an illegal 4-byte read of address 0xBFFFF74C, which as far as Memcheck can tell, is not a valid stack address, nore corresponds to any current heap blocks or recently freed heap blocks. The read is happening at line 54 of bogon.cpp, called from lin 66 of the same file, etc. For errors associated with identified heap block, for example reading freed memory, Valgrind reports not only the locaion where the error happened, but also where the associated heap block was allocated/freed.

### 2.5. Suppressing errors

The error-checking tools detect numberous problems in the system libraries, such as the C libraries, which come preinstalled with your OS. You can't easily fix these, but you don't want to see these errors. So Valgrind reads a list of errors to suppress at startup. A default suppression file is created by the ./configure script when the system is built.

You can modify and add to the suppressions file at your leisure, or, better, write your own. Multiple suppression files are allowed. This is useful if part of your project contains errors your can't or don't want to fix, yet you don't want to continuously be reminded of them.

***Note***: By far the easiest way to add suppressions is to use the *--gen-suppressions=yes* option described in Core Command-line Options. 

