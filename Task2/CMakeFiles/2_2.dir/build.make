# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.9.3_1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.9.3_1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client"

# Include any dependencies generated for this target.
include applications/Task2/CMakeFiles/2_2.dir/depend.make

# Include the progress variables for this target.
include applications/Task2/CMakeFiles/2_2.dir/progress.make

# Include the compile flags for this target's objects.
include applications/Task2/CMakeFiles/2_2.dir/flags.make

applications/Task2/CMakeFiles/2_2.dir/2_2.c.o: applications/Task2/CMakeFiles/2_2.dir/flags.make
applications/Task2/CMakeFiles/2_2.dir/2_2.c.o: applications/Task2/2_2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object applications/Task2/CMakeFiles/2_2.dir/2_2.c.o"
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task2" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/2_2.dir/2_2.c.o   -c "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task2/2_2.c"

applications/Task2/CMakeFiles/2_2.dir/2_2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/2_2.dir/2_2.c.i"
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task2" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task2/2_2.c" > CMakeFiles/2_2.dir/2_2.c.i

applications/Task2/CMakeFiles/2_2.dir/2_2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/2_2.dir/2_2.c.s"
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task2" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task2/2_2.c" -o CMakeFiles/2_2.dir/2_2.c.s

applications/Task2/CMakeFiles/2_2.dir/2_2.c.o.requires:

.PHONY : applications/Task2/CMakeFiles/2_2.dir/2_2.c.o.requires

applications/Task2/CMakeFiles/2_2.dir/2_2.c.o.provides: applications/Task2/CMakeFiles/2_2.dir/2_2.c.o.requires
	$(MAKE) -f applications/Task2/CMakeFiles/2_2.dir/build.make applications/Task2/CMakeFiles/2_2.dir/2_2.c.o.provides.build
.PHONY : applications/Task2/CMakeFiles/2_2.dir/2_2.c.o.provides

applications/Task2/CMakeFiles/2_2.dir/2_2.c.o.provides.build: applications/Task2/CMakeFiles/2_2.dir/2_2.c.o


# Object files for target 2_2
2_2_OBJECTS = \
"CMakeFiles/2_2.dir/2_2.c.o"

# External object files for target 2_2
2_2_EXTERNAL_OBJECTS =

applications/Task2/2_2: applications/Task2/CMakeFiles/2_2.dir/2_2.c.o
applications/Task2/2_2: applications/Task2/CMakeFiles/2_2.dir/build.make
applications/Task2/2_2: src/libclient.a
applications/Task2/2_2: applications/Task2/CMakeFiles/2_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 2_2"
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task2" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
applications/Task2/CMakeFiles/2_2.dir/build: applications/Task2/2_2

.PHONY : applications/Task2/CMakeFiles/2_2.dir/build

applications/Task2/CMakeFiles/2_2.dir/requires: applications/Task2/CMakeFiles/2_2.dir/2_2.c.o.requires

.PHONY : applications/Task2/CMakeFiles/2_2.dir/requires

applications/Task2/CMakeFiles/2_2.dir/clean:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task2" && $(CMAKE_COMMAND) -P CMakeFiles/2_2.dir/cmake_clean.cmake
.PHONY : applications/Task2/CMakeFiles/2_2.dir/clean

applications/Task2/CMakeFiles/2_2.dir/depend:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task2" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task2" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task2/CMakeFiles/2_2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : applications/Task2/CMakeFiles/2_2.dir/depend

