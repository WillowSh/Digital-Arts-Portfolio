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
include CMakeFiles/balboa_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/balboa_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/balboa_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/balboa_lib.dir/flags.make

CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.o: CMakeFiles/balboa_lib.dir/flags.make
CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.o: /Users/shanjiang/balboa_public/src/3rdparty/glad.c
CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.o: CMakeFiles/balboa_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shanjiang/balboa_public/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.o -MF CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.o.d -o CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.o -c /Users/shanjiang/balboa_public/src/3rdparty/glad.c

CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/shanjiang/balboa_public/src/3rdparty/glad.c > CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.i

CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/shanjiang/balboa_public/src/3rdparty/glad.c -o CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.s

CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.o: CMakeFiles/balboa_lib.dir/flags.make
CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.o: /Users/shanjiang/balboa_public/src/3rdparty/tinyply.cpp
CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.o: CMakeFiles/balboa_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shanjiang/balboa_public/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.o -MF CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.o.d -o CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.o -c /Users/shanjiang/balboa_public/src/3rdparty/tinyply.cpp

CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shanjiang/balboa_public/src/3rdparty/tinyply.cpp > CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.i

CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shanjiang/balboa_public/src/3rdparty/tinyply.cpp -o CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.s

CMakeFiles/balboa_lib.dir/src/hw1.cpp.o: CMakeFiles/balboa_lib.dir/flags.make
CMakeFiles/balboa_lib.dir/src/hw1.cpp.o: /Users/shanjiang/balboa_public/src/hw1.cpp
CMakeFiles/balboa_lib.dir/src/hw1.cpp.o: CMakeFiles/balboa_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shanjiang/balboa_public/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/balboa_lib.dir/src/hw1.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/balboa_lib.dir/src/hw1.cpp.o -MF CMakeFiles/balboa_lib.dir/src/hw1.cpp.o.d -o CMakeFiles/balboa_lib.dir/src/hw1.cpp.o -c /Users/shanjiang/balboa_public/src/hw1.cpp

CMakeFiles/balboa_lib.dir/src/hw1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/balboa_lib.dir/src/hw1.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shanjiang/balboa_public/src/hw1.cpp > CMakeFiles/balboa_lib.dir/src/hw1.cpp.i

CMakeFiles/balboa_lib.dir/src/hw1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/balboa_lib.dir/src/hw1.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shanjiang/balboa_public/src/hw1.cpp -o CMakeFiles/balboa_lib.dir/src/hw1.cpp.s

CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.o: CMakeFiles/balboa_lib.dir/flags.make
CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.o: /Users/shanjiang/balboa_public/src/hw1_scenes.cpp
CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.o: CMakeFiles/balboa_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shanjiang/balboa_public/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.o -MF CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.o.d -o CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.o -c /Users/shanjiang/balboa_public/src/hw1_scenes.cpp

CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shanjiang/balboa_public/src/hw1_scenes.cpp > CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.i

CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shanjiang/balboa_public/src/hw1_scenes.cpp -o CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.s

CMakeFiles/balboa_lib.dir/src/hw2.cpp.o: CMakeFiles/balboa_lib.dir/flags.make
CMakeFiles/balboa_lib.dir/src/hw2.cpp.o: /Users/shanjiang/balboa_public/src/hw2.cpp
CMakeFiles/balboa_lib.dir/src/hw2.cpp.o: CMakeFiles/balboa_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shanjiang/balboa_public/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/balboa_lib.dir/src/hw2.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/balboa_lib.dir/src/hw2.cpp.o -MF CMakeFiles/balboa_lib.dir/src/hw2.cpp.o.d -o CMakeFiles/balboa_lib.dir/src/hw2.cpp.o -c /Users/shanjiang/balboa_public/src/hw2.cpp

CMakeFiles/balboa_lib.dir/src/hw2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/balboa_lib.dir/src/hw2.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shanjiang/balboa_public/src/hw2.cpp > CMakeFiles/balboa_lib.dir/src/hw2.cpp.i

CMakeFiles/balboa_lib.dir/src/hw2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/balboa_lib.dir/src/hw2.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shanjiang/balboa_public/src/hw2.cpp -o CMakeFiles/balboa_lib.dir/src/hw2.cpp.s

CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.o: CMakeFiles/balboa_lib.dir/flags.make
CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.o: /Users/shanjiang/balboa_public/src/hw2_scenes.cpp
CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.o: CMakeFiles/balboa_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shanjiang/balboa_public/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.o -MF CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.o.d -o CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.o -c /Users/shanjiang/balboa_public/src/hw2_scenes.cpp

CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shanjiang/balboa_public/src/hw2_scenes.cpp > CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.i

CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shanjiang/balboa_public/src/hw2_scenes.cpp -o CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.s

CMakeFiles/balboa_lib.dir/src/hw3.cpp.o: CMakeFiles/balboa_lib.dir/flags.make
CMakeFiles/balboa_lib.dir/src/hw3.cpp.o: /Users/shanjiang/balboa_public/src/hw3.cpp
CMakeFiles/balboa_lib.dir/src/hw3.cpp.o: CMakeFiles/balboa_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shanjiang/balboa_public/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/balboa_lib.dir/src/hw3.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/balboa_lib.dir/src/hw3.cpp.o -MF CMakeFiles/balboa_lib.dir/src/hw3.cpp.o.d -o CMakeFiles/balboa_lib.dir/src/hw3.cpp.o -c /Users/shanjiang/balboa_public/src/hw3.cpp

CMakeFiles/balboa_lib.dir/src/hw3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/balboa_lib.dir/src/hw3.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shanjiang/balboa_public/src/hw3.cpp > CMakeFiles/balboa_lib.dir/src/hw3.cpp.i

CMakeFiles/balboa_lib.dir/src/hw3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/balboa_lib.dir/src/hw3.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shanjiang/balboa_public/src/hw3.cpp -o CMakeFiles/balboa_lib.dir/src/hw3.cpp.s

CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.o: CMakeFiles/balboa_lib.dir/flags.make
CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.o: /Users/shanjiang/balboa_public/src/hw3_scenes.cpp
CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.o: CMakeFiles/balboa_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shanjiang/balboa_public/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.o -MF CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.o.d -o CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.o -c /Users/shanjiang/balboa_public/src/hw3_scenes.cpp

CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shanjiang/balboa_public/src/hw3_scenes.cpp > CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.i

CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shanjiang/balboa_public/src/hw3_scenes.cpp -o CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.s

CMakeFiles/balboa_lib.dir/src/image.cpp.o: CMakeFiles/balboa_lib.dir/flags.make
CMakeFiles/balboa_lib.dir/src/image.cpp.o: /Users/shanjiang/balboa_public/src/image.cpp
CMakeFiles/balboa_lib.dir/src/image.cpp.o: CMakeFiles/balboa_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shanjiang/balboa_public/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/balboa_lib.dir/src/image.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/balboa_lib.dir/src/image.cpp.o -MF CMakeFiles/balboa_lib.dir/src/image.cpp.o.d -o CMakeFiles/balboa_lib.dir/src/image.cpp.o -c /Users/shanjiang/balboa_public/src/image.cpp

CMakeFiles/balboa_lib.dir/src/image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/balboa_lib.dir/src/image.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shanjiang/balboa_public/src/image.cpp > CMakeFiles/balboa_lib.dir/src/image.cpp.i

CMakeFiles/balboa_lib.dir/src/image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/balboa_lib.dir/src/image.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shanjiang/balboa_public/src/image.cpp -o CMakeFiles/balboa_lib.dir/src/image.cpp.s

CMakeFiles/balboa_lib.dir/src/change.cpp.o: CMakeFiles/balboa_lib.dir/flags.make
CMakeFiles/balboa_lib.dir/src/change.cpp.o: /Users/shanjiang/balboa_public/src/change.cpp
CMakeFiles/balboa_lib.dir/src/change.cpp.o: CMakeFiles/balboa_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/shanjiang/balboa_public/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/balboa_lib.dir/src/change.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/balboa_lib.dir/src/change.cpp.o -MF CMakeFiles/balboa_lib.dir/src/change.cpp.o.d -o CMakeFiles/balboa_lib.dir/src/change.cpp.o -c /Users/shanjiang/balboa_public/src/change.cpp

CMakeFiles/balboa_lib.dir/src/change.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/balboa_lib.dir/src/change.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shanjiang/balboa_public/src/change.cpp > CMakeFiles/balboa_lib.dir/src/change.cpp.i

CMakeFiles/balboa_lib.dir/src/change.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/balboa_lib.dir/src/change.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shanjiang/balboa_public/src/change.cpp -o CMakeFiles/balboa_lib.dir/src/change.cpp.s

# Object files for target balboa_lib
balboa_lib_OBJECTS = \
"CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.o" \
"CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.o" \
"CMakeFiles/balboa_lib.dir/src/hw1.cpp.o" \
"CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.o" \
"CMakeFiles/balboa_lib.dir/src/hw2.cpp.o" \
"CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.o" \
"CMakeFiles/balboa_lib.dir/src/hw3.cpp.o" \
"CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.o" \
"CMakeFiles/balboa_lib.dir/src/image.cpp.o" \
"CMakeFiles/balboa_lib.dir/src/change.cpp.o"

# External object files for target balboa_lib
balboa_lib_EXTERNAL_OBJECTS =

libbalboa_lib.a: CMakeFiles/balboa_lib.dir/src/3rdparty/glad.c.o
libbalboa_lib.a: CMakeFiles/balboa_lib.dir/src/3rdparty/tinyply.cpp.o
libbalboa_lib.a: CMakeFiles/balboa_lib.dir/src/hw1.cpp.o
libbalboa_lib.a: CMakeFiles/balboa_lib.dir/src/hw1_scenes.cpp.o
libbalboa_lib.a: CMakeFiles/balboa_lib.dir/src/hw2.cpp.o
libbalboa_lib.a: CMakeFiles/balboa_lib.dir/src/hw2_scenes.cpp.o
libbalboa_lib.a: CMakeFiles/balboa_lib.dir/src/hw3.cpp.o
libbalboa_lib.a: CMakeFiles/balboa_lib.dir/src/hw3_scenes.cpp.o
libbalboa_lib.a: CMakeFiles/balboa_lib.dir/src/image.cpp.o
libbalboa_lib.a: CMakeFiles/balboa_lib.dir/src/change.cpp.o
libbalboa_lib.a: CMakeFiles/balboa_lib.dir/build.make
libbalboa_lib.a: CMakeFiles/balboa_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/shanjiang/balboa_public/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX static library libbalboa_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/balboa_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/balboa_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/balboa_lib.dir/build: libbalboa_lib.a
.PHONY : CMakeFiles/balboa_lib.dir/build

CMakeFiles/balboa_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/balboa_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/balboa_lib.dir/clean

CMakeFiles/balboa_lib.dir/depend:
	cd /Users/shanjiang/balboa_public/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/shanjiang/balboa_public /Users/shanjiang/balboa_public /Users/shanjiang/balboa_public/build /Users/shanjiang/balboa_public/build /Users/shanjiang/balboa_public/build/CMakeFiles/balboa_lib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/balboa_lib.dir/depend

