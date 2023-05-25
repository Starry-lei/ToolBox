# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/Pangolin"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin"

# Include any dependencies generated for this target.
include tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/compiler_depend.make

# Include the progress variables for this target.
include tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/progress.make

# Include the compile flags for this target's objects.
include tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/flags.make

tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/main-print.cpp.o: tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/flags.make
tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/main-print.cpp.o: /home/lei/Documents/Research/Guided\ research/nldso_photometricLoss/thirdparty/Pangolin/tools/VideoJson/main-print.cpp
tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/main-print.cpp.o: tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/main-print.cpp.o"
	cd "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin/tools/VideoJson" && ccache /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/main-print.cpp.o -MF CMakeFiles/VideoJsonPrint.dir/main-print.cpp.o.d -o CMakeFiles/VideoJsonPrint.dir/main-print.cpp.o -c "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/Pangolin/tools/VideoJson/main-print.cpp"

tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/main-print.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VideoJsonPrint.dir/main-print.cpp.i"
	cd "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin/tools/VideoJson" && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/Pangolin/tools/VideoJson/main-print.cpp" > CMakeFiles/VideoJsonPrint.dir/main-print.cpp.i

tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/main-print.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VideoJsonPrint.dir/main-print.cpp.s"
	cd "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin/tools/VideoJson" && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/Pangolin/tools/VideoJson/main-print.cpp" -o CMakeFiles/VideoJsonPrint.dir/main-print.cpp.s

# Object files for target VideoJsonPrint
VideoJsonPrint_OBJECTS = \
"CMakeFiles/VideoJsonPrint.dir/main-print.cpp.o"

# External object files for target VideoJsonPrint
VideoJsonPrint_EXTERNAL_OBJECTS =

tools/VideoJson/VideoJsonPrint: tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/main-print.cpp.o
tools/VideoJson/VideoJsonPrint: tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/build.make
tools/VideoJson/VideoJsonPrint: src/libpangolin.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libOpenGL.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libGLX.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libGLU.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libGLEW.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libEGL.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libSM.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libICE.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libX11.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libXext.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libOpenGL.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libGLX.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libGLU.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libGLEW.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libEGL.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libSM.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libICE.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libX11.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libXext.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libdc1394.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libpng.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libz.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libjpeg.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libtiff.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/libIlmImf.so
tools/VideoJson/VideoJsonPrint: /usr/lib/x86_64-linux-gnu/liblz4.so
tools/VideoJson/VideoJsonPrint: tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VideoJsonPrint"
	cd "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin/tools/VideoJson" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VideoJsonPrint.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/build: tools/VideoJson/VideoJsonPrint
.PHONY : tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/build

tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/clean:
	cd "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin/tools/VideoJson" && $(CMAKE_COMMAND) -P CMakeFiles/VideoJsonPrint.dir/cmake_clean.cmake
.PHONY : tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/clean

tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/depend:
	cd "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/Pangolin" "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/Pangolin/tools/VideoJson" "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin" "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin/tools/VideoJson" "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin/tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : tools/VideoJson/CMakeFiles/VideoJsonPrint.dir/depend

