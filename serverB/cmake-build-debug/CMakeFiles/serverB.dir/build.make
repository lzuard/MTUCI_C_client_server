# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "/Users/izuard/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/212.5284.51/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/izuard/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/212.5284.51/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/izuard/inform_ptushkin/serverB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/izuard/inform_ptushkin/serverB/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/serverB.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/serverB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/serverB.dir/flags.make

CMakeFiles/serverB.dir/main.c.o: CMakeFiles/serverB.dir/flags.make
CMakeFiles/serverB.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/izuard/inform_ptushkin/serverB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/serverB.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serverB.dir/main.c.o -c /Users/izuard/inform_ptushkin/serverB/main.c

CMakeFiles/serverB.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serverB.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/izuard/inform_ptushkin/serverB/main.c > CMakeFiles/serverB.dir/main.c.i

CMakeFiles/serverB.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serverB.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/izuard/inform_ptushkin/serverB/main.c -o CMakeFiles/serverB.dir/main.c.s

# Object files for target serverB
serverB_OBJECTS = \
"CMakeFiles/serverB.dir/main.c.o"

# External object files for target serverB
serverB_EXTERNAL_OBJECTS =

serverB: CMakeFiles/serverB.dir/main.c.o
serverB: CMakeFiles/serverB.dir/build.make
serverB: CMakeFiles/serverB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/izuard/inform_ptushkin/serverB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable serverB"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serverB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/serverB.dir/build: serverB
.PHONY : CMakeFiles/serverB.dir/build

CMakeFiles/serverB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/serverB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/serverB.dir/clean

CMakeFiles/serverB.dir/depend:
	cd /Users/izuard/inform_ptushkin/serverB/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/izuard/inform_ptushkin/serverB /Users/izuard/inform_ptushkin/serverB /Users/izuard/inform_ptushkin/serverB/cmake-build-debug /Users/izuard/inform_ptushkin/serverB/cmake-build-debug /Users/izuard/inform_ptushkin/serverB/cmake-build-debug/CMakeFiles/serverB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/serverB.dir/depend
