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
CMAKE_SOURCE_DIR = /home/djf/MyCPP/CMAKE/static_in_static

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/djf/MyCPP/CMAKE/static_in_static/build

# Include any dependencies generated for this target.
include calc/CMakeFiles/calc.dir/depend.make

# Include the progress variables for this target.
include calc/CMakeFiles/calc.dir/progress.make

# Include the compile flags for this target's objects.
include calc/CMakeFiles/calc.dir/flags.make

calc/CMakeFiles/calc.dir/add.cpp.o: calc/CMakeFiles/calc.dir/flags.make
calc/CMakeFiles/calc.dir/add.cpp.o: ../calc/add.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/djf/MyCPP/CMAKE/static_in_static/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object calc/CMakeFiles/calc.dir/add.cpp.o"
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/calc.dir/add.cpp.o -c /home/djf/MyCPP/CMAKE/static_in_static/calc/add.cpp

calc/CMakeFiles/calc.dir/add.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/add.cpp.i"
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/djf/MyCPP/CMAKE/static_in_static/calc/add.cpp > CMakeFiles/calc.dir/add.cpp.i

calc/CMakeFiles/calc.dir/add.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/add.cpp.s"
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/djf/MyCPP/CMAKE/static_in_static/calc/add.cpp -o CMakeFiles/calc.dir/add.cpp.s

calc/CMakeFiles/calc.dir/div.cpp.o: calc/CMakeFiles/calc.dir/flags.make
calc/CMakeFiles/calc.dir/div.cpp.o: ../calc/div.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/djf/MyCPP/CMAKE/static_in_static/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object calc/CMakeFiles/calc.dir/div.cpp.o"
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/calc.dir/div.cpp.o -c /home/djf/MyCPP/CMAKE/static_in_static/calc/div.cpp

calc/CMakeFiles/calc.dir/div.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/div.cpp.i"
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/djf/MyCPP/CMAKE/static_in_static/calc/div.cpp > CMakeFiles/calc.dir/div.cpp.i

calc/CMakeFiles/calc.dir/div.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/div.cpp.s"
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/djf/MyCPP/CMAKE/static_in_static/calc/div.cpp -o CMakeFiles/calc.dir/div.cpp.s

calc/CMakeFiles/calc.dir/mult.cpp.o: calc/CMakeFiles/calc.dir/flags.make
calc/CMakeFiles/calc.dir/mult.cpp.o: ../calc/mult.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/djf/MyCPP/CMAKE/static_in_static/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object calc/CMakeFiles/calc.dir/mult.cpp.o"
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/calc.dir/mult.cpp.o -c /home/djf/MyCPP/CMAKE/static_in_static/calc/mult.cpp

calc/CMakeFiles/calc.dir/mult.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/mult.cpp.i"
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/djf/MyCPP/CMAKE/static_in_static/calc/mult.cpp > CMakeFiles/calc.dir/mult.cpp.i

calc/CMakeFiles/calc.dir/mult.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/mult.cpp.s"
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/djf/MyCPP/CMAKE/static_in_static/calc/mult.cpp -o CMakeFiles/calc.dir/mult.cpp.s

calc/CMakeFiles/calc.dir/sub.cpp.o: calc/CMakeFiles/calc.dir/flags.make
calc/CMakeFiles/calc.dir/sub.cpp.o: ../calc/sub.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/djf/MyCPP/CMAKE/static_in_static/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object calc/CMakeFiles/calc.dir/sub.cpp.o"
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/calc.dir/sub.cpp.o -c /home/djf/MyCPP/CMAKE/static_in_static/calc/sub.cpp

calc/CMakeFiles/calc.dir/sub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calc.dir/sub.cpp.i"
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/djf/MyCPP/CMAKE/static_in_static/calc/sub.cpp > CMakeFiles/calc.dir/sub.cpp.i

calc/CMakeFiles/calc.dir/sub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calc.dir/sub.cpp.s"
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/djf/MyCPP/CMAKE/static_in_static/calc/sub.cpp -o CMakeFiles/calc.dir/sub.cpp.s

# Object files for target calc
calc_OBJECTS = \
"CMakeFiles/calc.dir/add.cpp.o" \
"CMakeFiles/calc.dir/div.cpp.o" \
"CMakeFiles/calc.dir/mult.cpp.o" \
"CMakeFiles/calc.dir/sub.cpp.o"

# External object files for target calc
calc_EXTERNAL_OBJECTS =

../lib/libcalc.a: calc/CMakeFiles/calc.dir/add.cpp.o
../lib/libcalc.a: calc/CMakeFiles/calc.dir/div.cpp.o
../lib/libcalc.a: calc/CMakeFiles/calc.dir/mult.cpp.o
../lib/libcalc.a: calc/CMakeFiles/calc.dir/sub.cpp.o
../lib/libcalc.a: calc/CMakeFiles/calc.dir/build.make
../lib/libcalc.a: calc/CMakeFiles/calc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/djf/MyCPP/CMAKE/static_in_static/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library ../../lib/libcalc.a"
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && $(CMAKE_COMMAND) -P CMakeFiles/calc.dir/cmake_clean_target.cmake
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/calc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
calc/CMakeFiles/calc.dir/build: ../lib/libcalc.a

.PHONY : calc/CMakeFiles/calc.dir/build

calc/CMakeFiles/calc.dir/clean:
	cd /home/djf/MyCPP/CMAKE/static_in_static/build/calc && $(CMAKE_COMMAND) -P CMakeFiles/calc.dir/cmake_clean.cmake
.PHONY : calc/CMakeFiles/calc.dir/clean

calc/CMakeFiles/calc.dir/depend:
	cd /home/djf/MyCPP/CMAKE/static_in_static/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/djf/MyCPP/CMAKE/static_in_static /home/djf/MyCPP/CMAKE/static_in_static/calc /home/djf/MyCPP/CMAKE/static_in_static/build /home/djf/MyCPP/CMAKE/static_in_static/build/calc /home/djf/MyCPP/CMAKE/static_in_static/build/calc/CMakeFiles/calc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : calc/CMakeFiles/calc.dir/depend
