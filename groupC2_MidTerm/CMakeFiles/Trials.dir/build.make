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
include applications/groupC2_MidTerm/CMakeFiles/Trials.dir/depend.make

# Include the progress variables for this target.
include applications/groupC2_MidTerm/CMakeFiles/Trials.dir/progress.make

# Include the compile flags for this target's objects.
include applications/groupC2_MidTerm/CMakeFiles/Trials.dir/flags.make

applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.o: applications/groupC2_MidTerm/CMakeFiles/Trials.dir/flags.make
applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.o: applications/groupC2_MidTerm/tunnel.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.o"
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/groupC2_MidTerm" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Trials.dir/tunnel.c.o   -c "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/groupC2_MidTerm/tunnel.c"

applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Trials.dir/tunnel.c.i"
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/groupC2_MidTerm" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/groupC2_MidTerm/tunnel.c" > CMakeFiles/Trials.dir/tunnel.c.i

applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Trials.dir/tunnel.c.s"
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/groupC2_MidTerm" && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/groupC2_MidTerm/tunnel.c" -o CMakeFiles/Trials.dir/tunnel.c.s

applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.o.requires:

.PHONY : applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.o.requires

applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.o.provides: applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.o.requires
	$(MAKE) -f applications/groupC2_MidTerm/CMakeFiles/Trials.dir/build.make applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.o.provides.build
.PHONY : applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.o.provides

applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.o.provides.build: applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.o


# Object files for target Trials
Trials_OBJECTS = \
"CMakeFiles/Trials.dir/tunnel.c.o"

# External object files for target Trials
Trials_EXTERNAL_OBJECTS =

applications/groupC2_MidTerm/Trials: applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.o
applications/groupC2_MidTerm/Trials: applications/groupC2_MidTerm/CMakeFiles/Trials.dir/build.make
applications/groupC2_MidTerm/Trials: src/libclient.a
applications/groupC2_MidTerm/Trials: applications/groupC2_MidTerm/CMakeFiles/Trials.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Trials"
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/groupC2_MidTerm" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Trials.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
applications/groupC2_MidTerm/CMakeFiles/Trials.dir/build: applications/groupC2_MidTerm/Trials

.PHONY : applications/groupC2_MidTerm/CMakeFiles/Trials.dir/build

applications/groupC2_MidTerm/CMakeFiles/Trials.dir/requires: applications/groupC2_MidTerm/CMakeFiles/Trials.dir/tunnel.c.o.requires

.PHONY : applications/groupC2_MidTerm/CMakeFiles/Trials.dir/requires

applications/groupC2_MidTerm/CMakeFiles/Trials.dir/clean:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/groupC2_MidTerm" && $(CMAKE_COMMAND) -P CMakeFiles/Trials.dir/cmake_clean.cmake
.PHONY : applications/groupC2_MidTerm/CMakeFiles/Trials.dir/clean

applications/groupC2_MidTerm/CMakeFiles/Trials.dir/depend:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/groupC2_MidTerm" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/groupC2_MidTerm" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/groupC2_MidTerm/CMakeFiles/Trials.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : applications/groupC2_MidTerm/CMakeFiles/Trials.dir/depend
