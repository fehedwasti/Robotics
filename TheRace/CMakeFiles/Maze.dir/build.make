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
include applications/TheRace/CMakeFiles/maze.dir/depend.make

# Include the progress variables for this target.
include applications/TheRace/CMakeFiles/maze.dir/progress.make

# Include the compile flags for this target's objects.
include applications/TheRace/CMakeFiles/maze.dir/flags.make

applications/TheRace/CMakeFiles/maze.dir/maze.c.o: applications/TheRace/CMakeFiles/maze.dir/flags.make
applications/TheRace/CMakeFiles/maze.dir/maze.c.o: applications/TheRace/maze.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object applications/TheRace/CMakeFiles/maze.dir/maze.c.o"
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/TheRace" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/maze.dir/maze.c.o   -c "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/TheRace/maze.c"

applications/TheRace/CMakeFiles/maze.dir/maze.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/maze.dir/maze.c.i"
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/TheRace" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/TheRace/maze.c" > CMakeFiles/maze.dir/maze.c.i

applications/TheRace/CMakeFiles/maze.dir/maze.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/maze.dir/maze.c.s"
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/TheRace" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/TheRace/maze.c" -o CMakeFiles/maze.dir/maze.c.s

applications/TheRace/CMakeFiles/maze.dir/maze.c.o.requires:

.PHONY : applications/TheRace/CMakeFiles/maze.dir/maze.c.o.requires

applications/TheRace/CMakeFiles/maze.dir/maze.c.o.provides: applications/TheRace/CMakeFiles/maze.dir/maze.c.o.requires
	$(MAKE) -f applications/TheRace/CMakeFiles/maze.dir/build.make applications/TheRace/CMakeFiles/maze.dir/maze.c.o.provides.build
.PHONY : applications/TheRace/CMakeFiles/maze.dir/maze.c.o.provides

applications/TheRace/CMakeFiles/maze.dir/maze.c.o.provides.build: applications/TheRace/CMakeFiles/maze.dir/maze.c.o


# Object files for target maze
maze_OBJECTS = \
"CMakeFiles/maze.dir/maze.c.o"

# External object files for target maze
maze_EXTERNAL_OBJECTS =

applications/TheRace/maze: applications/TheRace/CMakeFiles/maze.dir/maze.c.o
applications/TheRace/maze: applications/TheRace/CMakeFiles/maze.dir/build.make
applications/TheRace/maze: src/libclient.a
applications/TheRace/maze: applications/TheRace/CMakeFiles/maze.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable maze"
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/TheRace" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/maze.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
applications/TheRace/CMakeFiles/maze.dir/build: applications/TheRace/maze

.PHONY : applications/TheRace/CMakeFiles/maze.dir/build

applications/TheRace/CMakeFiles/maze.dir/requires: applications/TheRace/CMakeFiles/maze.dir/maze.c.o.requires

.PHONY : applications/TheRace/CMakeFiles/maze.dir/requires

applications/TheRace/CMakeFiles/maze.dir/clean:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/TheRace" && $(CMAKE_COMMAND) -P CMakeFiles/maze.dir/cmake_clean.cmake
.PHONY : applications/TheRace/CMakeFiles/maze.dir/clean

applications/TheRace/CMakeFiles/maze.dir/depend:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/TheRace" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/TheRace" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/TheRace/CMakeFiles/maze.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : applications/TheRace/CMakeFiles/maze.dir/depend

