# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/benls/tmp/tmp.9sU1gCiDE9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/benls/tmp/tmp.9sU1gCiDE9/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Levv8Emulator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Levv8Emulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Levv8Emulator.dir/flags.make

CMakeFiles/Levv8Emulator.dir/main.c.o: CMakeFiles/Levv8Emulator.dir/flags.make
CMakeFiles/Levv8Emulator.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/benls/tmp/tmp.9sU1gCiDE9/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Levv8Emulator.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Levv8Emulator.dir/main.c.o   -c /home/benls/tmp/tmp.9sU1gCiDE9/main.c

CMakeFiles/Levv8Emulator.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Levv8Emulator.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/benls/tmp/tmp.9sU1gCiDE9/main.c > CMakeFiles/Levv8Emulator.dir/main.c.i

CMakeFiles/Levv8Emulator.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Levv8Emulator.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/benls/tmp/tmp.9sU1gCiDE9/main.c -o CMakeFiles/Levv8Emulator.dir/main.c.s

# Object files for target Levv8Emulator
Levv8Emulator_OBJECTS = \
"CMakeFiles/Levv8Emulator.dir/main.c.o"

# External object files for target Levv8Emulator
Levv8Emulator_EXTERNAL_OBJECTS =

Levv8Emulator: CMakeFiles/Levv8Emulator.dir/main.c.o
Levv8Emulator: CMakeFiles/Levv8Emulator.dir/build.make
Levv8Emulator: CMakeFiles/Levv8Emulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/benls/tmp/tmp.9sU1gCiDE9/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Levv8Emulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Levv8Emulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Levv8Emulator.dir/build: Levv8Emulator

.PHONY : CMakeFiles/Levv8Emulator.dir/build

CMakeFiles/Levv8Emulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Levv8Emulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Levv8Emulator.dir/clean

CMakeFiles/Levv8Emulator.dir/depend:
	cd /home/benls/tmp/tmp.9sU1gCiDE9/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benls/tmp/tmp.9sU1gCiDE9 /home/benls/tmp/tmp.9sU1gCiDE9 /home/benls/tmp/tmp.9sU1gCiDE9/cmake-build-debug /home/benls/tmp/tmp.9sU1gCiDE9/cmake-build-debug /home/benls/tmp/tmp.9sU1gCiDE9/cmake-build-debug/CMakeFiles/Levv8Emulator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Levv8Emulator.dir/depend
