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
CMAKE_COMMAND = /home/bibi/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.6948.80/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/bibi/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.6948.80/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bibi/Desktop/Programm/Semestr_2_C++/triangle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/triangle.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/triangle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/triangle.dir/flags.make

CMakeFiles/triangle.dir/main.cpp.o: CMakeFiles/triangle.dir/flags.make
CMakeFiles/triangle.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/triangle.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/triangle.dir/main.cpp.o -c /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/main.cpp

CMakeFiles/triangle.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangle.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/main.cpp > CMakeFiles/triangle.dir/main.cpp.i

CMakeFiles/triangle.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangle.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/main.cpp -o CMakeFiles/triangle.dir/main.cpp.s

CMakeFiles/triangle.dir/Triangle.cpp.o: CMakeFiles/triangle.dir/flags.make
CMakeFiles/triangle.dir/Triangle.cpp.o: ../Triangle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/triangle.dir/Triangle.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/triangle.dir/Triangle.cpp.o -c /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Triangle.cpp

CMakeFiles/triangle.dir/Triangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangle.dir/Triangle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Triangle.cpp > CMakeFiles/triangle.dir/Triangle.cpp.i

CMakeFiles/triangle.dir/Triangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangle.dir/Triangle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Triangle.cpp -o CMakeFiles/triangle.dir/Triangle.cpp.s

# Object files for target triangle
triangle_OBJECTS = \
"CMakeFiles/triangle.dir/main.cpp.o" \
"CMakeFiles/triangle.dir/Triangle.cpp.o"

# External object files for target triangle
triangle_EXTERNAL_OBJECTS =

triangle: CMakeFiles/triangle.dir/main.cpp.o
triangle: CMakeFiles/triangle.dir/Triangle.cpp.o
triangle: CMakeFiles/triangle.dir/build.make
triangle: CMakeFiles/triangle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable triangle"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/triangle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/triangle.dir/build: triangle

.PHONY : CMakeFiles/triangle.dir/build

CMakeFiles/triangle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/triangle.dir/cmake_clean.cmake
.PHONY : CMakeFiles/triangle.dir/clean

CMakeFiles/triangle.dir/depend:
	cd /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bibi/Desktop/Programm/Semestr_2_C++/triangle /home/bibi/Desktop/Programm/Semestr_2_C++/triangle /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug/CMakeFiles/triangle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/triangle.dir/depend
