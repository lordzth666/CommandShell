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
include CMakeFiles/csh.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/csh.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/csh.dir/flags.make

CMakeFiles/csh.dir/application/csh.cpp.o: CMakeFiles/csh.dir/flags.make
CMakeFiles/csh.dir/application/csh.cpp.o: ../application/csh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/usr/data/Repo/CommandShell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/csh.dir/application/csh.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/csh.dir/application/csh.cpp.o -c /usr/data/Repo/CommandShell/application/csh.cpp

CMakeFiles/csh.dir/application/csh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/csh.dir/application/csh.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/data/Repo/CommandShell/application/csh.cpp > CMakeFiles/csh.dir/application/csh.cpp.i

CMakeFiles/csh.dir/application/csh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/csh.dir/application/csh.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/data/Repo/CommandShell/application/csh.cpp -o CMakeFiles/csh.dir/application/csh.cpp.s

CMakeFiles/csh.dir/application/csh.cpp.o.requires:

.PHONY : CMakeFiles/csh.dir/application/csh.cpp.o.requires

CMakeFiles/csh.dir/application/csh.cpp.o.provides: CMakeFiles/csh.dir/application/csh.cpp.o.requires
	$(MAKE) -f CMakeFiles/csh.dir/build.make CMakeFiles/csh.dir/application/csh.cpp.o.provides.build
.PHONY : CMakeFiles/csh.dir/application/csh.cpp.o.provides

CMakeFiles/csh.dir/application/csh.cpp.o.provides.build: CMakeFiles/csh.dir/application/csh.cpp.o


# Object files for target csh
csh_OBJECTS = \
"CMakeFiles/csh.dir/application/csh.cpp.o"

# External object files for target csh
csh_EXTERNAL_OBJECTS =

csh: CMakeFiles/csh.dir/application/csh.cpp.o
csh: CMakeFiles/csh.dir/build.make
csh: libcshell.a
csh: CMakeFiles/csh.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/usr/data/Repo/CommandShell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable csh"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/csh.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/csh.dir/build: csh

.PHONY : CMakeFiles/csh.dir/build

CMakeFiles/csh.dir/requires: CMakeFiles/csh.dir/application/csh.cpp.o.requires

.PHONY : CMakeFiles/csh.dir/requires

CMakeFiles/csh.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/csh.dir/cmake_clean.cmake
.PHONY : CMakeFiles/csh.dir/clean

CMakeFiles/csh.dir/depend:
	cd /usr/data/Repo/CommandShell/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr/data/Repo/CommandShell /usr/data/Repo/CommandShell /usr/data/Repo/CommandShell/build /usr/data/Repo/CommandShell/build /usr/data/Repo/CommandShell/build/CMakeFiles/csh.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/csh.dir/depend
