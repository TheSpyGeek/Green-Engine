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
include thirdparty/glm/glm/CMakeFiles/glm_shared.dir/depend.make

# Include the progress variables for this target.
include thirdparty/glm/glm/CMakeFiles/glm_shared.dir/progress.make

# Include the compile flags for this target's objects.
include thirdparty/glm/glm/CMakeFiles/glm_shared.dir/flags.make

thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.o: thirdparty/glm/glm/CMakeFiles/glm_shared.dir/flags.make
thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.o: ../thirdparty/glm/glm/detail/glm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thespygeek/Projects/green-engine/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.o"
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/glm && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glm_shared.dir/detail/glm.cpp.o -c /home/thespygeek/Projects/green-engine/thirdparty/glm/glm/detail/glm.cpp

thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glm_shared.dir/detail/glm.cpp.i"
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/glm && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thespygeek/Projects/green-engine/thirdparty/glm/glm/detail/glm.cpp > CMakeFiles/glm_shared.dir/detail/glm.cpp.i

thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glm_shared.dir/detail/glm.cpp.s"
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/glm && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thespygeek/Projects/green-engine/thirdparty/glm/glm/detail/glm.cpp -o CMakeFiles/glm_shared.dir/detail/glm.cpp.s

thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.o.requires:

.PHONY : thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.o.requires

thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.o.provides: thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.o.requires
	$(MAKE) -f thirdparty/glm/glm/CMakeFiles/glm_shared.dir/build.make thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.o.provides.build
.PHONY : thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.o.provides

thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.o.provides.build: thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.o


# Object files for target glm_shared
glm_shared_OBJECTS = \
"CMakeFiles/glm_shared.dir/detail/glm.cpp.o"

# External object files for target glm_shared
glm_shared_EXTERNAL_OBJECTS =

thirdparty/glm/glm/libglm_shared.so: thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.o
thirdparty/glm/glm/libglm_shared.so: thirdparty/glm/glm/CMakeFiles/glm_shared.dir/build.make
thirdparty/glm/glm/libglm_shared.so: thirdparty/glm/glm/CMakeFiles/glm_shared.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/thespygeek/Projects/green-engine/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libglm_shared.so"
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/glm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glm_shared.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
thirdparty/glm/glm/CMakeFiles/glm_shared.dir/build: thirdparty/glm/glm/libglm_shared.so

.PHONY : thirdparty/glm/glm/CMakeFiles/glm_shared.dir/build

thirdparty/glm/glm/CMakeFiles/glm_shared.dir/requires: thirdparty/glm/glm/CMakeFiles/glm_shared.dir/detail/glm.cpp.o.requires

.PHONY : thirdparty/glm/glm/CMakeFiles/glm_shared.dir/requires

thirdparty/glm/glm/CMakeFiles/glm_shared.dir/clean:
	cd /home/thespygeek/Projects/green-engine/src/thirdparty/glm/glm && $(CMAKE_COMMAND) -P CMakeFiles/glm_shared.dir/cmake_clean.cmake
.PHONY : thirdparty/glm/glm/CMakeFiles/glm_shared.dir/clean

thirdparty/glm/glm/CMakeFiles/glm_shared.dir/depend:
	cd /home/thespygeek/Projects/green-engine/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thespygeek/Projects/green-engine /home/thespygeek/Projects/green-engine/thirdparty/glm/glm /home/thespygeek/Projects/green-engine/src /home/thespygeek/Projects/green-engine/src/thirdparty/glm/glm /home/thespygeek/Projects/green-engine/src/thirdparty/glm/glm/CMakeFiles/glm_shared.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thirdparty/glm/glm/CMakeFiles/glm_shared.dir/depend

