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
CMAKE_COMMAND = /opt/cmake-3.13.0/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.13.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/djf/MyCPP/CMAKE/library

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/djf/MyCPP/CMAKE/library/build

# Include any dependencies generated for this target.
include CMakeFiles/calc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/calc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/calc.dir/flags.make

CMakeFiles/calc.dir/src/add.cpp.o: CMakeFiles/calc.dir/flags.make
CMakeFiles/calc.dir/src/add.cpp.o: ../src/add.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/djf/MyCPP/CMAKE/library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/calc.dir/src/add.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/calc.dir/src/add.cpp.o -c /home/djf/MyCPP/CMAKE/library/src/add.cpp

CMakeFiles/calc.dir/src/add.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/src/add.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/djf/MyCPP/CMAKE/library/src/add.cpp > CMakeFiles/calc.dir/src/add.cpp.i

CMakeFiles/calc.dir/src/add.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/src/add.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/djf/MyCPP/CMAKE/library/src/add.cpp -o CMakeFiles/calc.dir/src/add.cpp.s

CMakeFiles/calc.dir/src/div.cpp.o: CMakeFiles/calc.dir/flags.make
CMakeFiles/calc.dir/src/div.cpp.o: ../src/div.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/djf/MyCPP/CMAKE/library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/calc.dir/src/div.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/calc.dir/src/div.cpp.o -c /home/djf/MyCPP/CMAKE/library/src/div.cpp

CMakeFiles/calc.dir/src/div.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/src/div.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/djf/MyCPP/CMAKE/library/src/div.cpp > CMakeFiles/calc.dir/src/div.cpp.i

CMakeFiles/calc.dir/src/div.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/src/div.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/djf/MyCPP/CMAKE/library/src/div.cpp -o CMakeFiles/calc.dir/src/div.cpp.s

CMakeFiles/calc.dir/src/mult.cpp.o: CMakeFiles/calc.dir/flags.make
CMakeFiles/calc.dir/src/mult.cpp.o: ../src/mult.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/djf/MyCPP/CMAKE/library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/calc.dir/src/mult.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/calc.dir/src/mult.cpp.o -c /home/djf/MyCPP/CMAKE/library/src/mult.cpp

CMakeFiles/calc.dir/src/mult.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/src/mult.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/djf/MyCPP/CMAKE/library/src/mult.cpp > CMakeFiles/calc.dir/src/mult.cpp.i

CMakeFiles/calc.dir/src/mult.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/src/mult.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/djf/MyCPP/CMAKE/library/src/mult.cpp -o CMakeFiles/calc.dir/src/mult.cpp.s

CMakeFiles/calc.dir/src/sub.cpp.o: CMakeFiles/calc.dir/flags.make
CMakeFiles/calc.dir/src/sub.cpp.o: ../src/sub.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/djf/MyCPP/CMAKE/library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/calc.dir/src/sub.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/calc.dir/src/sub.cpp.o -c /home/djf/MyCPP/CMAKE/library/src/sub.cpp

CMakeFiles/calc.dir/src/sub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/src/sub.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/djf/MyCPP/CMAKE/library/src/sub.cpp > CMakeFiles/calc.dir/src/sub.cpp.i

CMakeFiles/calc.dir/src/sub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/src/sub.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/djf/MyCPP/CMAKE/library/src/sub.cpp -o CMakeFiles/calc.dir/src/sub.cpp.s

# Object files for target calc
calc_OBJECTS = \
"CMakeFiles/calc.dir/src/add.cpp.o" \
"CMakeFiles/calc.dir/src/div.cpp.o" \
"CMakeFiles/calc.dir/src/mult.cpp.o" \
"CMakeFiles/calc.dir/src/sub.cpp.o"

# External object files for target calc
calc_EXTERNAL_OBJECTS =

../lib/libcalc.so: CMakeFiles/calc.dir/src/add.cpp.o
../lib/libcalc.so: CMakeFiles/calc.dir/src/div.cpp.o
../lib/libcalc.so: CMakeFiles/calc.dir/src/mult.cpp.o
../lib/libcalc.so: CMakeFiles/calc.dir/src/sub.cpp.o
../lib/libcalc.so: CMakeFiles/calc.dir/build.make
../lib/libcalc.so: CMakeFiles/calc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/djf/MyCPP/CMAKE/library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library ../lib/libcalc.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/calc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/calc.dir/build: ../lib/libcalc.so

.PHONY : CMakeFiles/calc.dir/build

CMakeFiles/calc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/calc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/calc.dir/clean

CMakeFiles/calc.dir/depend:
	cd /home/djf/MyCPP/CMAKE/library/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/djf/MyCPP/CMAKE/library /home/djf/MyCPP/CMAKE/library /home/djf/MyCPP/CMAKE/library/build /home/djf/MyCPP/CMAKE/library/build /home/djf/MyCPP/CMAKE/library/build/CMakeFiles/calc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/calc.dir/depend

