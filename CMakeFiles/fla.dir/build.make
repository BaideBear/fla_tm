# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /snap/cmake/1437/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1437/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/形式语言与自动机/project-2024

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/形式语言与自动机/project-2024

# Include any dependencies generated for this target.
include CMakeFiles/fla.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/fla.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/fla.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fla.dir/flags.make

CMakeFiles/fla.dir/codegen:
.PHONY : CMakeFiles/fla.dir/codegen

CMakeFiles/fla.dir/fla-project/main.cpp.o: CMakeFiles/fla.dir/flags.make
CMakeFiles/fla.dir/fla-project/main.cpp.o: fla-project/main.cpp
CMakeFiles/fla.dir/fla-project/main.cpp.o: CMakeFiles/fla.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/d/形式语言与自动机/project-2024/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fla.dir/fla-project/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fla.dir/fla-project/main.cpp.o -MF CMakeFiles/fla.dir/fla-project/main.cpp.o.d -o CMakeFiles/fla.dir/fla-project/main.cpp.o -c /mnt/d/形式语言与自动机/project-2024/fla-project/main.cpp

CMakeFiles/fla.dir/fla-project/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fla.dir/fla-project/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/形式语言与自动机/project-2024/fla-project/main.cpp > CMakeFiles/fla.dir/fla-project/main.cpp.i

CMakeFiles/fla.dir/fla-project/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fla.dir/fla-project/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/形式语言与自动机/project-2024/fla-project/main.cpp -o CMakeFiles/fla.dir/fla-project/main.cpp.s

# Object files for target fla
fla_OBJECTS = \
"CMakeFiles/fla.dir/fla-project/main.cpp.o"

# External object files for target fla
fla_EXTERNAL_OBJECTS =

bin/fla: CMakeFiles/fla.dir/fla-project/main.cpp.o
bin/fla: CMakeFiles/fla.dir/build.make
bin/fla: CMakeFiles/fla.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/d/形式语言与自动机/project-2024/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/fla"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fla.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fla.dir/build: bin/fla
.PHONY : CMakeFiles/fla.dir/build

CMakeFiles/fla.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fla.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fla.dir/clean

CMakeFiles/fla.dir/depend:
	cd /mnt/d/形式语言与自动机/project-2024 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/形式语言与自动机/project-2024 /mnt/d/形式语言与自动机/project-2024 /mnt/d/形式语言与自动机/project-2024 /mnt/d/形式语言与自动机/project-2024 /mnt/d/形式语言与自动机/project-2024/CMakeFiles/fla.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/fla.dir/depend

