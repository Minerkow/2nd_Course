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
CMAKE_SOURCE_DIR = /home/bibi/Desktop/Programm/TetsVulkan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bibi/Desktop/Programm/TetsVulkan/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TetsVulkan.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TetsVulkan.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TetsVulkan.dir/flags.make

CMakeFiles/TetsVulkan.dir/main.cpp.o: CMakeFiles/TetsVulkan.dir/flags.make
CMakeFiles/TetsVulkan.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bibi/Desktop/Programm/TetsVulkan/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TetsVulkan.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TetsVulkan.dir/main.cpp.o -c /home/bibi/Desktop/Programm/TetsVulkan/main.cpp

CMakeFiles/TetsVulkan.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TetsVulkan.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bibi/Desktop/Programm/TetsVulkan/main.cpp > CMakeFiles/TetsVulkan.dir/main.cpp.i

CMakeFiles/TetsVulkan.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TetsVulkan.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bibi/Desktop/Programm/TetsVulkan/main.cpp -o CMakeFiles/TetsVulkan.dir/main.cpp.s

# Object files for target TetsVulkan
TetsVulkan_OBJECTS = \
"CMakeFiles/TetsVulkan.dir/main.cpp.o"

# External object files for target TetsVulkan
TetsVulkan_EXTERNAL_OBJECTS =

TetsVulkan: CMakeFiles/TetsVulkan.dir/main.cpp.o
TetsVulkan: CMakeFiles/TetsVulkan.dir/build.make
TetsVulkan: CMakeFiles/TetsVulkan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bibi/Desktop/Programm/TetsVulkan/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TetsVulkan"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TetsVulkan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TetsVulkan.dir/build: TetsVulkan

.PHONY : CMakeFiles/TetsVulkan.dir/build

CMakeFiles/TetsVulkan.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TetsVulkan.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TetsVulkan.dir/clean

CMakeFiles/TetsVulkan.dir/depend:
	cd /home/bibi/Desktop/Programm/TetsVulkan/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bibi/Desktop/Programm/TetsVulkan /home/bibi/Desktop/Programm/TetsVulkan /home/bibi/Desktop/Programm/TetsVulkan/cmake-build-debug /home/bibi/Desktop/Programm/TetsVulkan/cmake-build-debug /home/bibi/Desktop/Programm/TetsVulkan/cmake-build-debug/CMakeFiles/TetsVulkan.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TetsVulkan.dir/depend

