# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/ming_frame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/ming_frame/Build/release

# Include any dependencies generated for this target.
include src/CMakeFiles/config.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/config.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/config.dir/flags.make

src/CMakeFiles/config.dir/config.cpp.o: src/CMakeFiles/config.dir/flags.make
src/CMakeFiles/config.dir/config.cpp.o: ../../src/config.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/ming_frame/Build/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/config.dir/config.cpp.o"
	cd /root/ming_frame/Build/release/src && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/config.dir/config.cpp.o -c /root/ming_frame/src/config.cpp

src/CMakeFiles/config.dir/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/config.dir/config.cpp.i"
	cd /root/ming_frame/Build/release/src && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/ming_frame/src/config.cpp > CMakeFiles/config.dir/config.cpp.i

src/CMakeFiles/config.dir/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/config.dir/config.cpp.s"
	cd /root/ming_frame/Build/release/src && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/ming_frame/src/config.cpp -o CMakeFiles/config.dir/config.cpp.s

src/CMakeFiles/config.dir/config.cpp.o.requires:
.PHONY : src/CMakeFiles/config.dir/config.cpp.o.requires

src/CMakeFiles/config.dir/config.cpp.o.provides: src/CMakeFiles/config.dir/config.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/config.dir/build.make src/CMakeFiles/config.dir/config.cpp.o.provides.build
.PHONY : src/CMakeFiles/config.dir/config.cpp.o.provides

src/CMakeFiles/config.dir/config.cpp.o.provides.build: src/CMakeFiles/config.dir/config.cpp.o

# Object files for target config
config_OBJECTS = \
"CMakeFiles/config.dir/config.cpp.o"

# External object files for target config
config_EXTERNAL_OBJECTS =

lib/libconfig.a: src/CMakeFiles/config.dir/config.cpp.o
lib/libconfig.a: src/CMakeFiles/config.dir/build.make
lib/libconfig.a: src/CMakeFiles/config.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../lib/libconfig.a"
	cd /root/ming_frame/Build/release/src && $(CMAKE_COMMAND) -P CMakeFiles/config.dir/cmake_clean_target.cmake
	cd /root/ming_frame/Build/release/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/config.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/config.dir/build: lib/libconfig.a
.PHONY : src/CMakeFiles/config.dir/build

src/CMakeFiles/config.dir/requires: src/CMakeFiles/config.dir/config.cpp.o.requires
.PHONY : src/CMakeFiles/config.dir/requires

src/CMakeFiles/config.dir/clean:
	cd /root/ming_frame/Build/release/src && $(CMAKE_COMMAND) -P CMakeFiles/config.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/config.dir/clean

src/CMakeFiles/config.dir/depend:
	cd /root/ming_frame/Build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ming_frame /root/ming_frame/src /root/ming_frame/Build/release /root/ming_frame/Build/release/src /root/ming_frame/Build/release/src/CMakeFiles/config.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/config.dir/depend

