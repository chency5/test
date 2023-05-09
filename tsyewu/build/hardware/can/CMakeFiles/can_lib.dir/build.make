# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/forlinx/shell/tsyewu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/forlinx/shell/tsyewu/build

# Include any dependencies generated for this target.
include hardware/can/CMakeFiles/can_lib.dir/depend.make

# Include the progress variables for this target.
include hardware/can/CMakeFiles/can_lib.dir/progress.make

# Include the compile flags for this target's objects.
include hardware/can/CMakeFiles/can_lib.dir/flags.make

hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.o: hardware/can/CMakeFiles/can_lib.dir/flags.make
hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.o: ../hardware/can/src/can_device.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forlinx/shell/tsyewu/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.o"
	cd /home/forlinx/shell/tsyewu/build/hardware/can && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/can_lib.dir/src/can_device.c.o   -c /home/forlinx/shell/tsyewu/hardware/can/src/can_device.c

hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/can_lib.dir/src/can_device.c.i"
	cd /home/forlinx/shell/tsyewu/build/hardware/can && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forlinx/shell/tsyewu/hardware/can/src/can_device.c > CMakeFiles/can_lib.dir/src/can_device.c.i

hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/can_lib.dir/src/can_device.c.s"
	cd /home/forlinx/shell/tsyewu/build/hardware/can && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forlinx/shell/tsyewu/hardware/can/src/can_device.c -o CMakeFiles/can_lib.dir/src/can_device.c.s

hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.o.requires:

.PHONY : hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.o.requires

hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.o.provides: hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.o.requires
	$(MAKE) -f hardware/can/CMakeFiles/can_lib.dir/build.make hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.o.provides.build
.PHONY : hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.o.provides

hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.o.provides.build: hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.o


# Object files for target can_lib
can_lib_OBJECTS = \
"CMakeFiles/can_lib.dir/src/can_device.c.o"

# External object files for target can_lib
can_lib_EXTERNAL_OBJECTS =

lib/libcan_lib.a: hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.o
lib/libcan_lib.a: hardware/can/CMakeFiles/can_lib.dir/build.make
lib/libcan_lib.a: hardware/can/CMakeFiles/can_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/forlinx/shell/tsyewu/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library ../../lib/libcan_lib.a"
	cd /home/forlinx/shell/tsyewu/build/hardware/can && $(CMAKE_COMMAND) -P CMakeFiles/can_lib.dir/cmake_clean_target.cmake
	cd /home/forlinx/shell/tsyewu/build/hardware/can && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/can_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
hardware/can/CMakeFiles/can_lib.dir/build: lib/libcan_lib.a

.PHONY : hardware/can/CMakeFiles/can_lib.dir/build

hardware/can/CMakeFiles/can_lib.dir/requires: hardware/can/CMakeFiles/can_lib.dir/src/can_device.c.o.requires

.PHONY : hardware/can/CMakeFiles/can_lib.dir/requires

hardware/can/CMakeFiles/can_lib.dir/clean:
	cd /home/forlinx/shell/tsyewu/build/hardware/can && $(CMAKE_COMMAND) -P CMakeFiles/can_lib.dir/cmake_clean.cmake
.PHONY : hardware/can/CMakeFiles/can_lib.dir/clean

hardware/can/CMakeFiles/can_lib.dir/depend:
	cd /home/forlinx/shell/tsyewu/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/forlinx/shell/tsyewu /home/forlinx/shell/tsyewu/hardware/can /home/forlinx/shell/tsyewu/build /home/forlinx/shell/tsyewu/build/hardware/can /home/forlinx/shell/tsyewu/build/hardware/can/CMakeFiles/can_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : hardware/can/CMakeFiles/can_lib.dir/depend

