# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Chandravanshi/Documents/Codes/01Knapsack

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Chandravanshi/Documents/Codes/01Knapsack/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/01Knapsack.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/01Knapsack.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/01Knapsack.dir/flags.make

CMakeFiles/01Knapsack.dir/main.cpp.o: CMakeFiles/01Knapsack.dir/flags.make
CMakeFiles/01Knapsack.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Chandravanshi/Documents/Codes/01Knapsack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/01Knapsack.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/01Knapsack.dir/main.cpp.o -c /Users/Chandravanshi/Documents/Codes/01Knapsack/main.cpp

CMakeFiles/01Knapsack.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/01Knapsack.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Chandravanshi/Documents/Codes/01Knapsack/main.cpp > CMakeFiles/01Knapsack.dir/main.cpp.i

CMakeFiles/01Knapsack.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/01Knapsack.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Chandravanshi/Documents/Codes/01Knapsack/main.cpp -o CMakeFiles/01Knapsack.dir/main.cpp.s

# Object files for target 01Knapsack
01Knapsack_OBJECTS = \
"CMakeFiles/01Knapsack.dir/main.cpp.o"

# External object files for target 01Knapsack
01Knapsack_EXTERNAL_OBJECTS =

01Knapsack: CMakeFiles/01Knapsack.dir/main.cpp.o
01Knapsack: CMakeFiles/01Knapsack.dir/build.make
01Knapsack: CMakeFiles/01Knapsack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Chandravanshi/Documents/Codes/01Knapsack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 01Knapsack"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/01Knapsack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/01Knapsack.dir/build: 01Knapsack

.PHONY : CMakeFiles/01Knapsack.dir/build

CMakeFiles/01Knapsack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/01Knapsack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/01Knapsack.dir/clean

CMakeFiles/01Knapsack.dir/depend:
	cd /Users/Chandravanshi/Documents/Codes/01Knapsack/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Chandravanshi/Documents/Codes/01Knapsack /Users/Chandravanshi/Documents/Codes/01Knapsack /Users/Chandravanshi/Documents/Codes/01Knapsack/cmake-build-debug /Users/Chandravanshi/Documents/Codes/01Knapsack/cmake-build-debug /Users/Chandravanshi/Documents/Codes/01Knapsack/cmake-build-debug/CMakeFiles/01Knapsack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/01Knapsack.dir/depend

