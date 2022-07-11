
## std::endl  and  '\n'

> cppreference.com

fea:Inserts a newline character into the output sequence os and flushes it as if by calling os.put(os.widen('\n')) followed by os.flush().

notes:
This manipulator may be used to produce a line of output immediately, e.g. when displaying output from a long-running process, logging activity of multiple threads or logging activity of a program that may crash unexpectedly. An explicit flush of std::cout is also necessary before a call to std::system, if the spawned process performs any screen I/O. In most other usual interactive I/O scenarios, std::endl is redundant when used with std::cout because any input from std::cin, output to std::cerr, or program termination forces a call to std::cout.flush(). Use of std::endl in place of '\n', encouraged by some sources, may significantly degrade output performance.

In many implementations, standard output is line-buffered, and writing '\n' causes a flush anyway, unless std::ios::sync_with_stdio(false) was executed. In those situations, unnecessary endl only degrades the performance of file output, not standard output.

## .cc and .cpp

> https://stackoverflow.com/questions/18590135/what-is-the-difference-between-cc-and-cpp-file-suffix

Historically, the suffix for a C++ source file was .C. This caused a few problems the first time C++ was ported to a system where case wasn't significant in the filename.

Different users adopted different solutions: .cc, .cpp, .cxx and possibly others. Today, outside of the Unix world, it's mostly .cpp. Unix seems to use .cc more often.

For headers, the situation is even more confusing: for whatever reasons, the earliest C++ authors decided not to distinguish between headers for C and for C++, and used .h.

This doesn't cause any problems if there is no C in the project, but when you start having to deal with both, it's usually a good idea to distinguish between the headers which can be used in C (.h) and those which cannot (.hh or .hpp).

In addition, in C++, a lot of users (including myself) prefer keeping the template sources and the inline functions in a separate file. Which, while strictly speaking a header file, tends to get yet another set of conventions (.inl, .tcc and probably a lot of others).

In the case of headers it makes absolutely no difference to the compiler.

In the case of source files different endings will cause the compiler to assume a different language. But this can normally be overridden, and I used .cc with VC++ long before VC++ recognized it as C++.


## Input/Output Stream Library
> https://cplusplus.com/reference/

Input/Output Stream Library
Provides functionality to use an abstraction called streams specially designed to perform input and output operations on sequences of character, like files or strings.
This functionality is provided through several related classes, as shown in the following relationship map, with the corresponding header file names on top:

![](pic/Screenshot%20from%202022-07-04%2017-04-30.png)