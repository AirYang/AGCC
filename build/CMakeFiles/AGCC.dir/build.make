# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yangguang/Documents/code/complier/AGCC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yangguang/Documents/code/complier/AGCC/build

# Include any dependencies generated for this target.
include CMakeFiles/AGCC.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AGCC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AGCC.dir/flags.make

CMakeFiles/AGCC.dir/src/main.cpp.o: CMakeFiles/AGCC.dir/flags.make
CMakeFiles/AGCC.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangguang/Documents/code/complier/AGCC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AGCC.dir/src/main.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AGCC.dir/src/main.cpp.o -c /home/yangguang/Documents/code/complier/AGCC/src/main.cpp

CMakeFiles/AGCC.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AGCC.dir/src/main.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangguang/Documents/code/complier/AGCC/src/main.cpp > CMakeFiles/AGCC.dir/src/main.cpp.i

CMakeFiles/AGCC.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AGCC.dir/src/main.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangguang/Documents/code/complier/AGCC/src/main.cpp -o CMakeFiles/AGCC.dir/src/main.cpp.s

CMakeFiles/AGCC.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/AGCC.dir/src/main.cpp.o.requires

CMakeFiles/AGCC.dir/src/main.cpp.o.provides: CMakeFiles/AGCC.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/AGCC.dir/build.make CMakeFiles/AGCC.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/AGCC.dir/src/main.cpp.o.provides

CMakeFiles/AGCC.dir/src/main.cpp.o.provides.build: CMakeFiles/AGCC.dir/src/main.cpp.o


# Object files for target AGCC
AGCC_OBJECTS = \
"CMakeFiles/AGCC.dir/src/main.cpp.o"

# External object files for target AGCC
AGCC_EXTERNAL_OBJECTS =

AGCC: CMakeFiles/AGCC.dir/src/main.cpp.o
AGCC: CMakeFiles/AGCC.dir/build.make
AGCC: CMakeFiles/AGCC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yangguang/Documents/code/complier/AGCC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AGCC"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AGCC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AGCC.dir/build: AGCC

.PHONY : CMakeFiles/AGCC.dir/build

CMakeFiles/AGCC.dir/requires: CMakeFiles/AGCC.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/AGCC.dir/requires

CMakeFiles/AGCC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AGCC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AGCC.dir/clean

CMakeFiles/AGCC.dir/depend:
	cd /home/yangguang/Documents/code/complier/AGCC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yangguang/Documents/code/complier/AGCC /home/yangguang/Documents/code/complier/AGCC /home/yangguang/Documents/code/complier/AGCC/build /home/yangguang/Documents/code/complier/AGCC/build /home/yangguang/Documents/code/complier/AGCC/build/CMakeFiles/AGCC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AGCC.dir/depend
