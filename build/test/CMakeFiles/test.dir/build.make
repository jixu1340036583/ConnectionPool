# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jixu/Mycode/ShiLei/ConnectionPool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jixu/Mycode/ShiLei/ConnectionPool/build

# Include any dependencies generated for this target.
include test/CMakeFiles/test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test.dir/flags.make

test/CMakeFiles/test.dir/main.cpp.o: test/CMakeFiles/test.dir/flags.make
test/CMakeFiles/test.dir/main.cpp.o: ../test/main.cpp
test/CMakeFiles/test.dir/main.cpp.o: test/CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jixu/Mycode/ShiLei/ConnectionPool/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test.dir/main.cpp.o"
	cd /home/jixu/Mycode/ShiLei/ConnectionPool/build/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/test.dir/main.cpp.o -MF CMakeFiles/test.dir/main.cpp.o.d -o CMakeFiles/test.dir/main.cpp.o -c /home/jixu/Mycode/ShiLei/ConnectionPool/test/main.cpp

test/CMakeFiles/test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/main.cpp.i"
	cd /home/jixu/Mycode/ShiLei/ConnectionPool/build/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jixu/Mycode/ShiLei/ConnectionPool/test/main.cpp > CMakeFiles/test.dir/main.cpp.i

test/CMakeFiles/test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/main.cpp.s"
	cd /home/jixu/Mycode/ShiLei/ConnectionPool/build/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jixu/Mycode/ShiLei/ConnectionPool/test/main.cpp -o CMakeFiles/test.dir/main.cpp.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/main.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

../bin/test: test/CMakeFiles/test.dir/main.cpp.o
../bin/test: test/CMakeFiles/test.dir/build.make
../bin/test: ../lib/libConnectionPool.so
../bin/test: test/CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jixu/Mycode/ShiLei/ConnectionPool/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/test"
	cd /home/jixu/Mycode/ShiLei/ConnectionPool/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test.dir/build: ../bin/test
.PHONY : test/CMakeFiles/test.dir/build

test/CMakeFiles/test.dir/clean:
	cd /home/jixu/Mycode/ShiLei/ConnectionPool/build/test && $(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test.dir/clean

test/CMakeFiles/test.dir/depend:
	cd /home/jixu/Mycode/ShiLei/ConnectionPool/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jixu/Mycode/ShiLei/ConnectionPool /home/jixu/Mycode/ShiLei/ConnectionPool/test /home/jixu/Mycode/ShiLei/ConnectionPool/build /home/jixu/Mycode/ShiLei/ConnectionPool/build/test /home/jixu/Mycode/ShiLei/ConnectionPool/build/test/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test.dir/depend

