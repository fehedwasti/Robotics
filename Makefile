# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.9.3_1/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.9.3_1/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(CMAKE_COMMAND) -E cmake_progress_start "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/CMakeFiles" "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/CMakeFiles/progress.marks"
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(MAKE) -f CMakeFiles/Makefile2 applications/all
	$(CMAKE_COMMAND) -E cmake_progress_start "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/CMakeFiles" 0
.PHONY : all

# The main clean target
clean:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(MAKE) -f CMakeFiles/Makefile2 applications/clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(MAKE) -f CMakeFiles/Makefile2 applications/preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(MAKE) -f CMakeFiles/Makefile2 applications/preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

# Convenience name for target.
applications/CMakeFiles/spinLeftRight.dir/rule:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(MAKE) -f CMakeFiles/Makefile2 applications/CMakeFiles/spinLeftRight.dir/rule
.PHONY : applications/CMakeFiles/spinLeftRight.dir/rule

# Convenience name for target.
spinLeftRight: applications/CMakeFiles/spinLeftRight.dir/rule

.PHONY : spinLeftRight

# fast build rule for target.
spinLeftRight/fast:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(MAKE) -f applications/CMakeFiles/spinLeftRight.dir/build.make applications/CMakeFiles/spinLeftRight.dir/build
.PHONY : spinLeftRight/fast

spinLeftRight.o: spinLeftRight.c.o

.PHONY : spinLeftRight.o

# target to build an object file
spinLeftRight.c.o:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(MAKE) -f applications/CMakeFiles/spinLeftRight.dir/build.make applications/CMakeFiles/spinLeftRight.dir/spinLeftRight.c.o
.PHONY : spinLeftRight.c.o

spinLeftRight.i: spinLeftRight.c.i

.PHONY : spinLeftRight.i

# target to preprocess a source file
spinLeftRight.c.i:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(MAKE) -f applications/CMakeFiles/spinLeftRight.dir/build.make applications/CMakeFiles/spinLeftRight.dir/spinLeftRight.c.i
.PHONY : spinLeftRight.c.i

spinLeftRight.s: spinLeftRight.c.s

.PHONY : spinLeftRight.s

# target to generate assembly for a file
spinLeftRight.c.s:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(MAKE) -f applications/CMakeFiles/spinLeftRight.dir/build.make applications/CMakeFiles/spinLeftRight.dir/spinLeftRight.c.s
.PHONY : spinLeftRight.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... spinLeftRight"
	@echo "... spinLeftRight.o"
	@echo "... spinLeftRight.i"
	@echo "... spinLeftRight.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	cd "/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client" && $(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
