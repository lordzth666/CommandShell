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
CMAKE_SOURCE_DIR = /usr/data/Repo/CommandShell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /usr/data/Repo/CommandShell/build

# Include any dependencies generated for this target.
include CMakeFiles/performance.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/performance.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/performance.dir/flags.make

CMakeFiles/performance.dir/application/performance.cpp.o: CMakeFiles/performance.dir/flags.make
CMakeFiles/performance.dir/application/performance.cpp.o: ../application/performance.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/usr/data/Repo/CommandShell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/performance.dir/application/performance.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/performance.dir/application/performance.cpp.o -c /usr/data/Repo/CommandShell/application/performance.cpp

CMakeFiles/performance.dir/application/performance.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/performance.dir/application/performance.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/data/Repo/CommandShell/application/performance.cpp > CMakeFiles/performance.dir/application/performance.cpp.i

CMakeFiles/performance.dir/application/performance.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/performance.dir/application/performance.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/data/Repo/CommandShell/application/performance.cpp -o CMakeFiles/performance.dir/application/performance.cpp.s

CMakeFiles/performance.dir/application/performance.cpp.o.requires:

.PHONY : CMakeFiles/performance.dir/application/performance.cpp.o.requires

CMakeFiles/performance.dir/application/performance.cpp.o.provides: CMakeFiles/performance.dir/application/performance.cpp.o.requires
	$(MAKE) -f CMakeFiles/performance.dir/build.make CMakeFiles/performance.dir/application/performance.cpp.o.provides.build
.PHONY : CMakeFiles/performance.dir/application/performance.cpp.o.provides

CMakeFiles/performance.dir/application/performance.cpp.o.provides.build: CMakeFiles/performance.dir/application/performance.cpp.o


# Object files for target performance
performance_OBJECTS = \
"CMakeFiles/performance.dir/application/performance.cpp.o"

# External object files for target performance
performance_EXTERNAL_OBJECTS =

performance: CMakeFiles/performance.dir/application/performance.cpp.o
performance: CMakeFiles/performance.dir/build.make
performance: libcshell.a
performance: CMakeFiles/performance.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/usr/data/Repo/CommandShell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable performance"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/performance.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/performance.dir/build: performance

.PHONY : CMakeFiles/performance.dir/build

CMakeFiles/performance.dir/requires: CMakeFiles/performance.dir/application/performance.cpp.o.requires

.PHONY : CMakeFiles/performance.dir/requires

CMakeFiles/performance.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/performance.dir/cmake_clean.cmake
.PHONY : CMakeFiles/performance.dir/clean

CMakeFiles/performance.dir/depend:
	cd /usr/data/Repo/CommandShell/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr/data/Repo/CommandShell /usr/data/Repo/CommandShell /usr/data/Repo/CommandShell/build /usr/data/Repo/CommandShell/build /usr/data/Repo/CommandShell/build/CMakeFiles/performance.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/performance.dir/depend

