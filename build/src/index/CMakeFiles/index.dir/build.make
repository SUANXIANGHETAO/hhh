# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/huanghanghua/src/db2023/db2023/rmdb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/huanghanghua/src/db2023/db2023/rmdb/build

# Include any dependencies generated for this target.
include src/index/CMakeFiles/index.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/index/CMakeFiles/index.dir/compiler_depend.make

# Include the progress variables for this target.
include src/index/CMakeFiles/index.dir/progress.make

# Include the compile flags for this target's objects.
include src/index/CMakeFiles/index.dir/flags.make

src/index/CMakeFiles/index.dir/ix_index_handle.cpp.o: src/index/CMakeFiles/index.dir/flags.make
src/index/CMakeFiles/index.dir/ix_index_handle.cpp.o: ../src/index/ix_index_handle.cpp
src/index/CMakeFiles/index.dir/ix_index_handle.cpp.o: src/index/CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huanghanghua/src/db2023/db2023/rmdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/index/CMakeFiles/index.dir/ix_index_handle.cpp.o"
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/index/CMakeFiles/index.dir/ix_index_handle.cpp.o -MF CMakeFiles/index.dir/ix_index_handle.cpp.o.d -o CMakeFiles/index.dir/ix_index_handle.cpp.o -c /home/huanghanghua/src/db2023/db2023/rmdb/src/index/ix_index_handle.cpp

src/index/CMakeFiles/index.dir/ix_index_handle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/index.dir/ix_index_handle.cpp.i"
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/huanghanghua/src/db2023/db2023/rmdb/src/index/ix_index_handle.cpp > CMakeFiles/index.dir/ix_index_handle.cpp.i

src/index/CMakeFiles/index.dir/ix_index_handle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/index.dir/ix_index_handle.cpp.s"
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/huanghanghua/src/db2023/db2023/rmdb/src/index/ix_index_handle.cpp -o CMakeFiles/index.dir/ix_index_handle.cpp.s

src/index/CMakeFiles/index.dir/ix_scan.cpp.o: src/index/CMakeFiles/index.dir/flags.make
src/index/CMakeFiles/index.dir/ix_scan.cpp.o: ../src/index/ix_scan.cpp
src/index/CMakeFiles/index.dir/ix_scan.cpp.o: src/index/CMakeFiles/index.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huanghanghua/src/db2023/db2023/rmdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/index/CMakeFiles/index.dir/ix_scan.cpp.o"
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/index/CMakeFiles/index.dir/ix_scan.cpp.o -MF CMakeFiles/index.dir/ix_scan.cpp.o.d -o CMakeFiles/index.dir/ix_scan.cpp.o -c /home/huanghanghua/src/db2023/db2023/rmdb/src/index/ix_scan.cpp

src/index/CMakeFiles/index.dir/ix_scan.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/index.dir/ix_scan.cpp.i"
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/huanghanghua/src/db2023/db2023/rmdb/src/index/ix_scan.cpp > CMakeFiles/index.dir/ix_scan.cpp.i

src/index/CMakeFiles/index.dir/ix_scan.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/index.dir/ix_scan.cpp.s"
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/huanghanghua/src/db2023/db2023/rmdb/src/index/ix_scan.cpp -o CMakeFiles/index.dir/ix_scan.cpp.s

# Object files for target index
index_OBJECTS = \
"CMakeFiles/index.dir/ix_index_handle.cpp.o" \
"CMakeFiles/index.dir/ix_scan.cpp.o"

# External object files for target index
index_EXTERNAL_OBJECTS =

lib/libindex.a: src/index/CMakeFiles/index.dir/ix_index_handle.cpp.o
lib/libindex.a: src/index/CMakeFiles/index.dir/ix_scan.cpp.o
lib/libindex.a: src/index/CMakeFiles/index.dir/build.make
lib/libindex.a: src/index/CMakeFiles/index.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/huanghanghua/src/db2023/db2023/rmdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library ../../lib/libindex.a"
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/index && $(CMAKE_COMMAND) -P CMakeFiles/index.dir/cmake_clean_target.cmake
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/index && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/index.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/index/CMakeFiles/index.dir/build: lib/libindex.a
.PHONY : src/index/CMakeFiles/index.dir/build

src/index/CMakeFiles/index.dir/clean:
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/index && $(CMAKE_COMMAND) -P CMakeFiles/index.dir/cmake_clean.cmake
.PHONY : src/index/CMakeFiles/index.dir/clean

src/index/CMakeFiles/index.dir/depend:
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/huanghanghua/src/db2023/db2023/rmdb /home/huanghanghua/src/db2023/db2023/rmdb/src/index /home/huanghanghua/src/db2023/db2023/rmdb/build /home/huanghanghua/src/db2023/db2023/rmdb/build/src/index /home/huanghanghua/src/db2023/db2023/rmdb/build/src/index/CMakeFiles/index.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/index/CMakeFiles/index.dir/depend

