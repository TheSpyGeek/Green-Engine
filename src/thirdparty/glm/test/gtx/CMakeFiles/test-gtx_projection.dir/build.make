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
include thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/depend.make

# Include the progress variables for this target.
include thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/progress.make

# Include the compile flags for this target's objects.
include thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/flags.make

thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o: thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/flags.make
thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o: ../thirdparty/glm/test/gtx/gtx_projection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thespygeek/Projects/green-engine/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o"
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtx && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o -c /home/thespygeek/Projects/green-engine/thirdparty/glm/test/gtx/gtx_projection.cpp

thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.i"
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thespygeek/Projects/green-engine/thirdparty/glm/test/gtx/gtx_projection.cpp > CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.i

thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.s"
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thespygeek/Projects/green-engine/thirdparty/glm/test/gtx/gtx_projection.cpp -o CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.s

thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o.requires:

.PHONY : thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o.requires

thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o.provides: thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o.requires
	$(MAKE) -f thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/build.make thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o.provides.build
.PHONY : thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o.provides

thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o.provides.build: thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o


# Object files for target test-gtx_projection
test__gtx_projection_OBJECTS = \
"CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o"

# External object files for target test-gtx_projection
test__gtx_projection_EXTERNAL_OBJECTS =

thirdparty/glm/test/gtx/test-gtx_projection: thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o
thirdparty/glm/test/gtx/test-gtx_projection: thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/build.make
thirdparty/glm/test/gtx/test-gtx_projection: thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/thespygeek/Projects/green-engine/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-gtx_projection"
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtx && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-gtx_projection.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/build: thirdparty/glm/test/gtx/test-gtx_projection

.PHONY : thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/build

thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/requires: thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/gtx_projection.cpp.o.requires

.PHONY : thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/requires

thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/clean:
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtx && $(CMAKE_COMMAND) -P CMakeFiles/test-gtx_projection.dir/cmake_clean.cmake
.PHONY : thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/clean

thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/depend:
	cd /home/thespygeek/Projects/green-engine/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thespygeek/Projects/green-engine /home/thespygeek/Projects/green-engine/thirdparty/glm/test/gtx /home/thespygeek/Projects/green-engine/src /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtx /home/thespygeek/Projects/green-engine/src/thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thirdparty/glm/test/gtx/CMakeFiles/test-gtx_projection.dir/depend

