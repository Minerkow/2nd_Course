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
include CMakeFiles/testTriangle.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testTriangle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testTriangle.dir/flags.make

CMakeFiles/testTriangle.dir/Test/test_triangle.cpp.o: CMakeFiles/testTriangle.dir/flags.make
CMakeFiles/testTriangle.dir/Test/test_triangle.cpp.o: ../Test/test_triangle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testTriangle.dir/Test/test_triangle.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testTriangle.dir/Test/test_triangle.cpp.o -c /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Test/test_triangle.cpp

CMakeFiles/testTriangle.dir/Test/test_triangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testTriangle.dir/Test/test_triangle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Test/test_triangle.cpp > CMakeFiles/testTriangle.dir/Test/test_triangle.cpp.i

CMakeFiles/testTriangle.dir/Test/test_triangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testTriangle.dir/Test/test_triangle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Test/test_triangle.cpp -o CMakeFiles/testTriangle.dir/Test/test_triangle.cpp.s

CMakeFiles/testTriangle.dir/Test/test_intersection.cpp.o: CMakeFiles/testTriangle.dir/flags.make
CMakeFiles/testTriangle.dir/Test/test_intersection.cpp.o: ../Test/test_intersection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testTriangle.dir/Test/test_intersection.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testTriangle.dir/Test/test_intersection.cpp.o -c /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Test/test_intersection.cpp

CMakeFiles/testTriangle.dir/Test/test_intersection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testTriangle.dir/Test/test_intersection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Test/test_intersection.cpp > CMakeFiles/testTriangle.dir/Test/test_intersection.cpp.i

CMakeFiles/testTriangle.dir/Test/test_intersection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testTriangle.dir/Test/test_intersection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Test/test_intersection.cpp -o CMakeFiles/testTriangle.dir/Test/test_intersection.cpp.s

CMakeFiles/testTriangle.dir/Triangle.cpp.o: CMakeFiles/testTriangle.dir/flags.make
CMakeFiles/testTriangle.dir/Triangle.cpp.o: ../Triangle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/testTriangle.dir/Triangle.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testTriangle.dir/Triangle.cpp.o -c /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Triangle.cpp

CMakeFiles/testTriangle.dir/Triangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testTriangle.dir/Triangle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Triangle.cpp > CMakeFiles/testTriangle.dir/Triangle.cpp.i

CMakeFiles/testTriangle.dir/Triangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testTriangle.dir/Triangle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Triangle.cpp -o CMakeFiles/testTriangle.dir/Triangle.cpp.s

CMakeFiles/testTriangle.dir/IntersectionTriangles.cpp.o: CMakeFiles/testTriangle.dir/flags.make
CMakeFiles/testTriangle.dir/IntersectionTriangles.cpp.o: ../IntersectionTriangles.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/testTriangle.dir/IntersectionTriangles.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testTriangle.dir/IntersectionTriangles.cpp.o -c /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/IntersectionTriangles.cpp

CMakeFiles/testTriangle.dir/IntersectionTriangles.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testTriangle.dir/IntersectionTriangles.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/IntersectionTriangles.cpp > CMakeFiles/testTriangle.dir/IntersectionTriangles.cpp.i

CMakeFiles/testTriangle.dir/IntersectionTriangles.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testTriangle.dir/IntersectionTriangles.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/IntersectionTriangles.cpp -o CMakeFiles/testTriangle.dir/IntersectionTriangles.cpp.s

CMakeFiles/testTriangle.dir/Test/test_generator.cpp.o: CMakeFiles/testTriangle.dir/flags.make
CMakeFiles/testTriangle.dir/Test/test_generator.cpp.o: ../Test/test_generator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/testTriangle.dir/Test/test_generator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testTriangle.dir/Test/test_generator.cpp.o -c /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Test/test_generator.cpp

CMakeFiles/testTriangle.dir/Test/test_generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testTriangle.dir/Test/test_generator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Test/test_generator.cpp > CMakeFiles/testTriangle.dir/Test/test_generator.cpp.i

CMakeFiles/testTriangle.dir/Test/test_generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testTriangle.dir/Test/test_generator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/Test/test_generator.cpp -o CMakeFiles/testTriangle.dir/Test/test_generator.cpp.s

# Object files for target testTriangle
testTriangle_OBJECTS = \
"CMakeFiles/testTriangle.dir/Test/test_triangle.cpp.o" \
"CMakeFiles/testTriangle.dir/Test/test_intersection.cpp.o" \
"CMakeFiles/testTriangle.dir/Triangle.cpp.o" \
"CMakeFiles/testTriangle.dir/IntersectionTriangles.cpp.o" \
"CMakeFiles/testTriangle.dir/Test/test_generator.cpp.o"

# External object files for target testTriangle
testTriangle_EXTERNAL_OBJECTS =

testTriangle: CMakeFiles/testTriangle.dir/Test/test_triangle.cpp.o
testTriangle: CMakeFiles/testTriangle.dir/Test/test_intersection.cpp.o
testTriangle: CMakeFiles/testTriangle.dir/Triangle.cpp.o
testTriangle: CMakeFiles/testTriangle.dir/IntersectionTriangles.cpp.o
testTriangle: CMakeFiles/testTriangle.dir/Test/test_generator.cpp.o
testTriangle: CMakeFiles/testTriangle.dir/build.make
testTriangle: /usr/lib/x86_64-linux-gnu/libgtest.a
testTriangle: CMakeFiles/testTriangle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable testTriangle"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testTriangle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testTriangle.dir/build: testTriangle

.PHONY : CMakeFiles/testTriangle.dir/build

CMakeFiles/testTriangle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testTriangle.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testTriangle.dir/clean

CMakeFiles/testTriangle.dir/depend:
	cd /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bibi/Desktop/Programm/Semestr_2_C++/triangle /home/bibi/Desktop/Programm/Semestr_2_C++/triangle /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug /home/bibi/Desktop/Programm/Semestr_2_C++/triangle/cmake-build-debug/CMakeFiles/testTriangle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testTriangle.dir/depend

