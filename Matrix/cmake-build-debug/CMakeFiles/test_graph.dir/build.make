# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /home/minerkow/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/minerkow/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/minerkow/Рабочий стол/2nd_Course/Matrix"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/minerkow/Рабочий стол/2nd_Course/Matrix/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/test_graph.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_graph.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_graph.dir/flags.make

CMakeFiles/test_graph.dir/test/test_graph.o: CMakeFiles/test_graph.dir/flags.make
CMakeFiles/test_graph.dir/test/test_graph.o: ../test/test_graph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/minerkow/Рабочий стол/2nd_Course/Matrix/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_graph.dir/test/test_graph.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_graph.dir/test/test_graph.o -c "/home/minerkow/Рабочий стол/2nd_Course/Matrix/test/test_graph.cpp"

CMakeFiles/test_graph.dir/test/test_graph.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_graph.dir/test/test_graph.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/minerkow/Рабочий стол/2nd_Course/Matrix/test/test_graph.cpp" > CMakeFiles/test_graph.dir/test/test_graph.i

CMakeFiles/test_graph.dir/test/test_graph.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_graph.dir/test/test_graph.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/minerkow/Рабочий стол/2nd_Course/Matrix/test/test_graph.cpp" -o CMakeFiles/test_graph.dir/test/test_graph.s

# Object files for target test_graph
test_graph_OBJECTS = \
"CMakeFiles/test_graph.dir/test/test_graph.o"

# External object files for target test_graph
test_graph_EXTERNAL_OBJECTS =

test_graph: CMakeFiles/test_graph.dir/test/test_graph.o
test_graph: CMakeFiles/test_graph.dir/build.make
test_graph: /usr/lib/x86_64-linux-gnu/libgtest.a
test_graph: CMakeFiles/test_graph.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/minerkow/Рабочий стол/2nd_Course/Matrix/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_graph"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_graph.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_graph.dir/build: test_graph

.PHONY : CMakeFiles/test_graph.dir/build

CMakeFiles/test_graph.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_graph.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_graph.dir/clean

CMakeFiles/test_graph.dir/depend:
	cd "/home/minerkow/Рабочий стол/2nd_Course/Matrix/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/minerkow/Рабочий стол/2nd_Course/Matrix" "/home/minerkow/Рабочий стол/2nd_Course/Matrix" "/home/minerkow/Рабочий стол/2nd_Course/Matrix/cmake-build-debug" "/home/minerkow/Рабочий стол/2nd_Course/Matrix/cmake-build-debug" "/home/minerkow/Рабочий стол/2nd_Course/Matrix/cmake-build-debug/CMakeFiles/test_graph.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/test_graph.dir/depend

