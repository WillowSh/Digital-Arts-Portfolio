# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/shanjiang/balboa_public

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/shanjiang/balboa_public/build

# Include any dependencies generated for this target.
include CMakeFiles/balboa.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/balboa.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/balboa.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/balboa.dir/flags.make

CMakeFiles/balboa.dir/src/main.cpp.o: CMakeFiles/balboa.dir/flags.make
CMakeFiles/balboa.dir/src/main.cpp.o: /Users/shanjiang/balboa_public/src/main.cpp
CMakeFiles/balboa.dir/src/main.cpp.o: CMakeFiles/balboa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shanjiang/balboa_public/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/balboa.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/balboa.dir/src/main.cpp.o -MF CMakeFiles/balboa.dir/src/main.cpp.o.d -o CMakeFiles/balboa.dir/src/main.cpp.o -c /Users/shanjiang/balboa_public/src/main.cpp

CMakeFiles/balboa.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/balboa.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shanjiang/balboa_public/src/main.cpp > CMakeFiles/balboa.dir/src/main.cpp.i

CMakeFiles/balboa.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/balboa.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shanjiang/balboa_public/src/main.cpp -o CMakeFiles/balboa.dir/src/main.cpp.s

# Object files for target balboa
balboa_OBJECTS = \
"CMakeFiles/balboa.dir/src/main.cpp.o"

# External object files for target balboa
balboa_EXTERNAL_OBJECTS =

balboa: CMakeFiles/balboa.dir/src/main.cpp.o
balboa: CMakeFiles/balboa.dir/build.make
balboa: libbalboa_lib.a
balboa: src/3rdparty/glfw/src/libglfw3.a
balboa: /Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
balboa: CMakeFiles/balboa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/shanjiang/balboa_public/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable balboa"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/balboa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/balboa.dir/build: balboa
.PHONY : CMakeFiles/balboa.dir/build

CMakeFiles/balboa.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/balboa.dir/cmake_clean.cmake
.PHONY : CMakeFiles/balboa.dir/clean

CMakeFiles/balboa.dir/depend:
	cd /Users/shanjiang/balboa_public/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/shanjiang/balboa_public /Users/shanjiang/balboa_public /Users/shanjiang/balboa_public/build /Users/shanjiang/balboa_public/build /Users/shanjiang/balboa_public/build/CMakeFiles/balboa.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/balboa.dir/depend

