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
include src/system/CMakeFiles/system.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/system/CMakeFiles/system.dir/compiler_depend.make

# Include the progress variables for this target.
include src/system/CMakeFiles/system.dir/progress.make

# Include the compile flags for this target's objects.
include src/system/CMakeFiles/system.dir/flags.make

src/system/CMakeFiles/system.dir/sm_manager.cpp.o: src/system/CMakeFiles/system.dir/flags.make
src/system/CMakeFiles/system.dir/sm_manager.cpp.o: ../src/system/sm_manager.cpp
src/system/CMakeFiles/system.dir/sm_manager.cpp.o: src/system/CMakeFiles/system.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/huanghanghua/src/db2023/db2023/rmdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/system/CMakeFiles/system.dir/sm_manager.cpp.o"
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/system && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/system/CMakeFiles/system.dir/sm_manager.cpp.o -MF CMakeFiles/system.dir/sm_manager.cpp.o.d -o CMakeFiles/system.dir/sm_manager.cpp.o -c /home/huanghanghua/src/db2023/db2023/rmdb/src/system/sm_manager.cpp

src/system/CMakeFiles/system.dir/sm_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/system.dir/sm_manager.cpp.i"
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/system && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/huanghanghua/src/db2023/db2023/rmdb/src/system/sm_manager.cpp > CMakeFiles/system.dir/sm_manager.cpp.i

src/system/CMakeFiles/system.dir/sm_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/system.dir/sm_manager.cpp.s"
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/system && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/huanghanghua/src/db2023/db2023/rmdb/src/system/sm_manager.cpp -o CMakeFiles/system.dir/sm_manager.cpp.s

# Object files for target system
system_OBJECTS = \
"CMakeFiles/system.dir/sm_manager.cpp.o"

# External object files for target system
system_EXTERNAL_OBJECTS =

lib/libsystem.a: src/system/CMakeFiles/system.dir/sm_manager.cpp.o
lib/libsystem.a: src/system/CMakeFiles/system.dir/build.make
lib/libsystem.a: src/system/CMakeFiles/system.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/huanghanghua/src/db2023/db2023/rmdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../lib/libsystem.a"
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/system && $(CMAKE_COMMAND) -P CMakeFiles/system.dir/cmake_clean_target.cmake
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/system && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/system.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/system/CMakeFiles/system.dir/build: lib/libsystem.a
.PHONY : src/system/CMakeFiles/system.dir/build

src/system/CMakeFiles/system.dir/clean:
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build/src/system && $(CMAKE_COMMAND) -P CMakeFiles/system.dir/cmake_clean.cmake
.PHONY : src/system/CMakeFiles/system.dir/clean

src/system/CMakeFiles/system.dir/depend:
	cd /home/huanghanghua/src/db2023/db2023/rmdb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/huanghanghua/src/db2023/db2023/rmdb /home/huanghanghua/src/db2023/db2023/rmdb/src/system /home/huanghanghua/src/db2023/db2023/rmdb/build /home/huanghanghua/src/db2023/db2023/rmdb/build/src/system /home/huanghanghua/src/db2023/db2023/rmdb/build/src/system/CMakeFiles/system.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/system/CMakeFiles/system.dir/depend

