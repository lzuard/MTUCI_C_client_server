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
CMAKE_SOURCE_DIR = /Users/izuard/inform_ptushkin/log_servB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/izuard/inform_ptushkin/log_servB/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/log_servB.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/log_servB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/log_servB.dir/flags.make

CMakeFiles/log_servB.dir/main.c.o: CMakeFiles/log_servB.dir/flags.make
CMakeFiles/log_servB.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/izuard/inform_ptushkin/log_servB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/log_servB.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/log_servB.dir/main.c.o -c /Users/izuard/inform_ptushkin/log_servB/main.c

CMakeFiles/log_servB.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/log_servB.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/izuard/inform_ptushkin/log_servB/main.c > CMakeFiles/log_servB.dir/main.c.i

CMakeFiles/log_servB.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/log_servB.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/izuard/inform_ptushkin/log_servB/main.c -o CMakeFiles/log_servB.dir/main.c.s

# Object files for target log_servB
log_servB_OBJECTS = \
"CMakeFiles/log_servB.dir/main.c.o"

# External object files for target log_servB
log_servB_EXTERNAL_OBJECTS =

log_servB: CMakeFiles/log_servB.dir/main.c.o
log_servB: CMakeFiles/log_servB.dir/build.make
log_servB: CMakeFiles/log_servB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/izuard/inform_ptushkin/log_servB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable log_servB"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/log_servB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/log_servB.dir/build: log_servB
.PHONY : CMakeFiles/log_servB.dir/build

CMakeFiles/log_servB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/log_servB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/log_servB.dir/clean

CMakeFiles/log_servB.dir/depend:
	cd /Users/izuard/inform_ptushkin/log_servB/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/izuard/inform_ptushkin/log_servB /Users/izuard/inform_ptushkin/log_servB /Users/izuard/inform_ptushkin/log_servB/cmake-build-debug /Users/izuard/inform_ptushkin/log_servB/cmake-build-debug /Users/izuard/inform_ptushkin/log_servB/cmake-build-debug/CMakeFiles/log_servB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/log_servB.dir/depend
