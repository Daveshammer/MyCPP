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
CMAKE_SOURCE_DIR = /home/djf/MyCPP/CMAKE/shared_in_static

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/djf/MyCPP/CMAKE/shared_in_static/build

# Include any dependencies generated for this target.
include sort/CMakeFiles/sort.dir/depend.make

# Include the progress variables for this target.
include sort/CMakeFiles/sort.dir/progress.make

# Include the compile flags for this target's objects.
include sort/CMakeFiles/sort.dir/flags.make

sort/CMakeFiles/sort.dir/quick_sort.cpp.o: sort/CMakeFiles/sort.dir/flags.make
sort/CMakeFiles/sort.dir/quick_sort.cpp.o: ../sort/quick_sort.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/djf/MyCPP/CMAKE/shared_in_static/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sort/CMakeFiles/sort.dir/quick_sort.cpp.o"
	cd /home/djf/MyCPP/CMAKE/shared_in_static/build/sort && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sort.dir/quick_sort.cpp.o -c /home/djf/MyCPP/CMAKE/shared_in_static/sort/quick_sort.cpp

sort/CMakeFiles/sort.dir/quick_sort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sort.dir/quick_sort.cpp.i"
	cd /home/djf/MyCPP/CMAKE/shared_in_static/build/sort && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/djf/MyCPP/CMAKE/shared_in_static/sort/quick_sort.cpp > CMakeFiles/sort.dir/quick_sort.cpp.i

sort/CMakeFiles/sort.dir/quick_sort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sort.dir/quick_sort.cpp.s"
	cd /home/djf/MyCPP/CMAKE/shared_in_static/build/sort && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/djf/MyCPP/CMAKE/shared_in_static/sort/quick_sort.cpp -o CMakeFiles/sort.dir/quick_sort.cpp.s

sort/CMakeFiles/sort.dir/select_sort.cpp.o: sort/CMakeFiles/sort.dir/flags.make
sort/CMakeFiles/sort.dir/select_sort.cpp.o: ../sort/select_sort.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/djf/MyCPP/CMAKE/shared_in_static/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object sort/CMakeFiles/sort.dir/select_sort.cpp.o"
	cd /home/djf/MyCPP/CMAKE/shared_in_static/build/sort && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sort.dir/select_sort.cpp.o -c /home/djf/MyCPP/CMAKE/shared_in_static/sort/select_sort.cpp

sort/CMakeFiles/sort.dir/select_sort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sort.dir/select_sort.cpp.i"
	cd /home/djf/MyCPP/CMAKE/shared_in_static/build/sort && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/djf/MyCPP/CMAKE/shared_in_static/sort/select_sort.cpp > CMakeFiles/sort.dir/select_sort.cpp.i

sort/CMakeFiles/sort.dir/select_sort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sort.dir/select_sort.cpp.s"
	cd /home/djf/MyCPP/CMAKE/shared_in_static/build/sort && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/djf/MyCPP/CMAKE/shared_in_static/sort/select_sort.cpp -o CMakeFiles/sort.dir/select_sort.cpp.s

# Object files for target sort
sort_OBJECTS = \
"CMakeFiles/sort.dir/quick_sort.cpp.o" \
"CMakeFiles/sort.dir/select_sort.cpp.o"

# External object files for target sort
sort_EXTERNAL_OBJECTS =

sort/libsort.a: sort/CMakeFiles/sort.dir/quick_sort.cpp.o
sort/libsort.a: sort/CMakeFiles/sort.dir/select_sort.cpp.o
sort/libsort.a: sort/CMakeFiles/sort.dir/build.make
sort/libsort.a: sort/CMakeFiles/sort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/djf/MyCPP/CMAKE/shared_in_static/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libsort.a"
	cd /home/djf/MyCPP/CMAKE/shared_in_static/build/sort && $(CMAKE_COMMAND) -P CMakeFiles/sort.dir/cmake_clean_target.cmake
	cd /home/djf/MyCPP/CMAKE/shared_in_static/build/sort && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sort.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sort/CMakeFiles/sort.dir/build: sort/libsort.a

.PHONY : sort/CMakeFiles/sort.dir/build

sort/CMakeFiles/sort.dir/clean:
	cd /home/djf/MyCPP/CMAKE/shared_in_static/build/sort && $(CMAKE_COMMAND) -P CMakeFiles/sort.dir/cmake_clean.cmake
.PHONY : sort/CMakeFiles/sort.dir/clean

sort/CMakeFiles/sort.dir/depend:
	cd /home/djf/MyCPP/CMAKE/shared_in_static/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/djf/MyCPP/CMAKE/shared_in_static /home/djf/MyCPP/CMAKE/shared_in_static/sort /home/djf/MyCPP/CMAKE/shared_in_static/build /home/djf/MyCPP/CMAKE/shared_in_static/build/sort /home/djf/MyCPP/CMAKE/shared_in_static/build/sort/CMakeFiles/sort.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sort/CMakeFiles/sort.dir/depend

