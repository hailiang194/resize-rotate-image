# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/hailiang194/Documents/opencv-tutorial/resize-rotate-image/bicubic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hailiang194/Documents/opencv-tutorial/resize-rotate-image/bicubic/build

# Include any dependencies generated for this target.
include CMakeFiles/lagrange.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lagrange.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lagrange.dir/flags.make

CMakeFiles/lagrange.dir/src/lagrange.cpp.o: CMakeFiles/lagrange.dir/flags.make
CMakeFiles/lagrange.dir/src/lagrange.cpp.o: ../src/lagrange.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hailiang194/Documents/opencv-tutorial/resize-rotate-image/bicubic/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lagrange.dir/src/lagrange.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lagrange.dir/src/lagrange.cpp.o -c /home/hailiang194/Documents/opencv-tutorial/resize-rotate-image/bicubic/src/lagrange.cpp

CMakeFiles/lagrange.dir/src/lagrange.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lagrange.dir/src/lagrange.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hailiang194/Documents/opencv-tutorial/resize-rotate-image/bicubic/src/lagrange.cpp > CMakeFiles/lagrange.dir/src/lagrange.cpp.i

CMakeFiles/lagrange.dir/src/lagrange.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lagrange.dir/src/lagrange.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hailiang194/Documents/opencv-tutorial/resize-rotate-image/bicubic/src/lagrange.cpp -o CMakeFiles/lagrange.dir/src/lagrange.cpp.s

# Object files for target lagrange
lagrange_OBJECTS = \
"CMakeFiles/lagrange.dir/src/lagrange.cpp.o"

# External object files for target lagrange
lagrange_EXTERNAL_OBJECTS =

liblagrange.a: CMakeFiles/lagrange.dir/src/lagrange.cpp.o
liblagrange.a: CMakeFiles/lagrange.dir/build.make
liblagrange.a: CMakeFiles/lagrange.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hailiang194/Documents/opencv-tutorial/resize-rotate-image/bicubic/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblagrange.a"
	$(CMAKE_COMMAND) -P CMakeFiles/lagrange.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lagrange.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lagrange.dir/build: liblagrange.a

.PHONY : CMakeFiles/lagrange.dir/build

CMakeFiles/lagrange.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lagrange.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lagrange.dir/clean

CMakeFiles/lagrange.dir/depend:
	cd /home/hailiang194/Documents/opencv-tutorial/resize-rotate-image/bicubic/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hailiang194/Documents/opencv-tutorial/resize-rotate-image/bicubic /home/hailiang194/Documents/opencv-tutorial/resize-rotate-image/bicubic /home/hailiang194/Documents/opencv-tutorial/resize-rotate-image/bicubic/build /home/hailiang194/Documents/opencv-tutorial/resize-rotate-image/bicubic/build /home/hailiang194/Documents/opencv-tutorial/resize-rotate-image/bicubic/build/CMakeFiles/lagrange.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lagrange.dir/depend

