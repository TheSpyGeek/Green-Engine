# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/thespygeek/Projects/green-engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thespygeek/Projects/green-engine/src

# Include any dependencies generated for this target.
include thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/depend.make

# Include the progress variables for this target.
include thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/progress.make

# Include the compile flags for this target's objects.
include thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/flags.make

thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o: thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/flags.make
thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o: ../thirdparty/glm/test/gtc/gtc_epsilon.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thespygeek/Projects/green-engine/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o"
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o -c /home/thespygeek/Projects/green-engine/thirdparty/glm/test/gtc/gtc_epsilon.cpp

thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.i"
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thespygeek/Projects/green-engine/thirdparty/glm/test/gtc/gtc_epsilon.cpp > CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.i

thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.s"
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thespygeek/Projects/green-engine/thirdparty/glm/test/gtc/gtc_epsilon.cpp -o CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.s

thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o.requires:

.PHONY : thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o.requires

thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o.provides: thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o.requires
	$(MAKE) -f thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/build.make thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o.provides.build
.PHONY : thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o.provides

thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o.provides.build: thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o


# Object files for target test-gtc_epsilon
test__gtc_epsilon_OBJECTS = \
"CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o"

# External object files for target test-gtc_epsilon
test__gtc_epsilon_EXTERNAL_OBJECTS =

thirdparty/glm/test/gtc/test-gtc_epsilon: thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o
thirdparty/glm/test/gtc/test-gtc_epsilon: thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/build.make
thirdparty/glm/test/gtc/test-gtc_epsilon: thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/thespygeek/Projects/green-engine/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-gtc_epsilon"
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-gtc_epsilon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/build: thirdparty/glm/test/gtc/test-gtc_epsilon

.PHONY : thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/build

thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/requires: thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/gtc_epsilon.cpp.o.requires

.PHONY : thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/requires

thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/clean:
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtc && $(CMAKE_COMMAND) -P CMakeFiles/test-gtc_epsilon.dir/cmake_clean.cmake
.PHONY : thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/clean

thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/depend:
	cd /home/thespygeek/Projects/green-engine/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thespygeek/Projects/green-engine /home/thespygeek/Projects/green-engine/thirdparty/glm/test/gtc /home/thespygeek/Projects/green-engine/src /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtc /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thirdparty/glm/test/gtc/CMakeFiles/test-gtc_epsilon.dir/depend

