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
include tool/public/CMakeFiles/public_lib.dir/depend.make

# Include the progress variables for this target.
include tool/public/CMakeFiles/public_lib.dir/progress.make

# Include the compile flags for this target's objects.
include tool/public/CMakeFiles/public_lib.dir/flags.make

tool/public/CMakeFiles/public_lib.dir/src/crc.c.o: tool/public/CMakeFiles/public_lib.dir/flags.make
tool/public/CMakeFiles/public_lib.dir/src/crc.c.o: ../tool/public/src/crc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forlinx/shell/tsyewu/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tool/public/CMakeFiles/public_lib.dir/src/crc.c.o"
	cd /home/forlinx/shell/tsyewu/build/tool/public && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/public_lib.dir/src/crc.c.o   -c /home/forlinx/shell/tsyewu/tool/public/src/crc.c

tool/public/CMakeFiles/public_lib.dir/src/crc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/public_lib.dir/src/crc.c.i"
	cd /home/forlinx/shell/tsyewu/build/tool/public && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forlinx/shell/tsyewu/tool/public/src/crc.c > CMakeFiles/public_lib.dir/src/crc.c.i

tool/public/CMakeFiles/public_lib.dir/src/crc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/public_lib.dir/src/crc.c.s"
	cd /home/forlinx/shell/tsyewu/build/tool/public && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forlinx/shell/tsyewu/tool/public/src/crc.c -o CMakeFiles/public_lib.dir/src/crc.c.s

tool/public/CMakeFiles/public_lib.dir/src/crc.c.o.requires:

.PHONY : tool/public/CMakeFiles/public_lib.dir/src/crc.c.o.requires

tool/public/CMakeFiles/public_lib.dir/src/crc.c.o.provides: tool/public/CMakeFiles/public_lib.dir/src/crc.c.o.requires
	$(MAKE) -f tool/public/CMakeFiles/public_lib.dir/build.make tool/public/CMakeFiles/public_lib.dir/src/crc.c.o.provides.build
.PHONY : tool/public/CMakeFiles/public_lib.dir/src/crc.c.o.provides

tool/public/CMakeFiles/public_lib.dir/src/crc.c.o.provides.build: tool/public/CMakeFiles/public_lib.dir/src/crc.c.o


tool/public/CMakeFiles/public_lib.dir/src/public.c.o: tool/public/CMakeFiles/public_lib.dir/flags.make
tool/public/CMakeFiles/public_lib.dir/src/public.c.o: ../tool/public/src/public.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forlinx/shell/tsyewu/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tool/public/CMakeFiles/public_lib.dir/src/public.c.o"
	cd /home/forlinx/shell/tsyewu/build/tool/public && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/public_lib.dir/src/public.c.o   -c /home/forlinx/shell/tsyewu/tool/public/src/public.c

tool/public/CMakeFiles/public_lib.dir/src/public.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/public_lib.dir/src/public.c.i"
	cd /home/forlinx/shell/tsyewu/build/tool/public && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forlinx/shell/tsyewu/tool/public/src/public.c > CMakeFiles/public_lib.dir/src/public.c.i

tool/public/CMakeFiles/public_lib.dir/src/public.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/public_lib.dir/src/public.c.s"
	cd /home/forlinx/shell/tsyewu/build/tool/public && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forlinx/shell/tsyewu/tool/public/src/public.c -o CMakeFiles/public_lib.dir/src/public.c.s

tool/public/CMakeFiles/public_lib.dir/src/public.c.o.requires:

.PHONY : tool/public/CMakeFiles/public_lib.dir/src/public.c.o.requires

tool/public/CMakeFiles/public_lib.dir/src/public.c.o.provides: tool/public/CMakeFiles/public_lib.dir/src/public.c.o.requires
	$(MAKE) -f tool/public/CMakeFiles/public_lib.dir/build.make tool/public/CMakeFiles/public_lib.dir/src/public.c.o.provides.build
.PHONY : tool/public/CMakeFiles/public_lib.dir/src/public.c.o.provides

tool/public/CMakeFiles/public_lib.dir/src/public.c.o.provides.build: tool/public/CMakeFiles/public_lib.dir/src/public.c.o


tool/public/CMakeFiles/public_lib.dir/src/type.c.o: tool/public/CMakeFiles/public_lib.dir/flags.make
tool/public/CMakeFiles/public_lib.dir/src/type.c.o: ../tool/public/src/type.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forlinx/shell/tsyewu/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object tool/public/CMakeFiles/public_lib.dir/src/type.c.o"
	cd /home/forlinx/shell/tsyewu/build/tool/public && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/public_lib.dir/src/type.c.o   -c /home/forlinx/shell/tsyewu/tool/public/src/type.c

tool/public/CMakeFiles/public_lib.dir/src/type.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/public_lib.dir/src/type.c.i"
	cd /home/forlinx/shell/tsyewu/build/tool/public && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forlinx/shell/tsyewu/tool/public/src/type.c > CMakeFiles/public_lib.dir/src/type.c.i

tool/public/CMakeFiles/public_lib.dir/src/type.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/public_lib.dir/src/type.c.s"
	cd /home/forlinx/shell/tsyewu/build/tool/public && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forlinx/shell/tsyewu/tool/public/src/type.c -o CMakeFiles/public_lib.dir/src/type.c.s

tool/public/CMakeFiles/public_lib.dir/src/type.c.o.requires:

.PHONY : tool/public/CMakeFiles/public_lib.dir/src/type.c.o.requires

tool/public/CMakeFiles/public_lib.dir/src/type.c.o.provides: tool/public/CMakeFiles/public_lib.dir/src/type.c.o.requires
	$(MAKE) -f tool/public/CMakeFiles/public_lib.dir/build.make tool/public/CMakeFiles/public_lib.dir/src/type.c.o.provides.build
.PHONY : tool/public/CMakeFiles/public_lib.dir/src/type.c.o.provides

tool/public/CMakeFiles/public_lib.dir/src/type.c.o.provides.build: tool/public/CMakeFiles/public_lib.dir/src/type.c.o


tool/public/CMakeFiles/public_lib.dir/src/utily.c.o: tool/public/CMakeFiles/public_lib.dir/flags.make
tool/public/CMakeFiles/public_lib.dir/src/utily.c.o: ../tool/public/src/utily.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/forlinx/shell/tsyewu/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object tool/public/CMakeFiles/public_lib.dir/src/utily.c.o"
	cd /home/forlinx/shell/tsyewu/build/tool/public && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/public_lib.dir/src/utily.c.o   -c /home/forlinx/shell/tsyewu/tool/public/src/utily.c

tool/public/CMakeFiles/public_lib.dir/src/utily.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/public_lib.dir/src/utily.c.i"
	cd /home/forlinx/shell/tsyewu/build/tool/public && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/forlinx/shell/tsyewu/tool/public/src/utily.c > CMakeFiles/public_lib.dir/src/utily.c.i

tool/public/CMakeFiles/public_lib.dir/src/utily.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/public_lib.dir/src/utily.c.s"
	cd /home/forlinx/shell/tsyewu/build/tool/public && /opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc   -march=armv7ve -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/fsl-imx-x11/4.1.15-2.0.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/forlinx/shell/tsyewu/tool/public/src/utily.c -o CMakeFiles/public_lib.dir/src/utily.c.s

tool/public/CMakeFiles/public_lib.dir/src/utily.c.o.requires:

.PHONY : tool/public/CMakeFiles/public_lib.dir/src/utily.c.o.requires

tool/public/CMakeFiles/public_lib.dir/src/utily.c.o.provides: tool/public/CMakeFiles/public_lib.dir/src/utily.c.o.requires
	$(MAKE) -f tool/public/CMakeFiles/public_lib.dir/build.make tool/public/CMakeFiles/public_lib.dir/src/utily.c.o.provides.build
.PHONY : tool/public/CMakeFiles/public_lib.dir/src/utily.c.o.provides

tool/public/CMakeFiles/public_lib.dir/src/utily.c.o.provides.build: tool/public/CMakeFiles/public_lib.dir/src/utily.c.o


# Object files for target public_lib
public_lib_OBJECTS = \
"CMakeFiles/public_lib.dir/src/crc.c.o" \
"CMakeFiles/public_lib.dir/src/public.c.o" \
"CMakeFiles/public_lib.dir/src/type.c.o" \
"CMakeFiles/public_lib.dir/src/utily.c.o"

# External object files for target public_lib
public_lib_EXTERNAL_OBJECTS =

lib/libpublic_lib.a: tool/public/CMakeFiles/public_lib.dir/src/crc.c.o
lib/libpublic_lib.a: tool/public/CMakeFiles/public_lib.dir/src/public.c.o
lib/libpublic_lib.a: tool/public/CMakeFiles/public_lib.dir/src/type.c.o
lib/libpublic_lib.a: tool/public/CMakeFiles/public_lib.dir/src/utily.c.o
lib/libpublic_lib.a: tool/public/CMakeFiles/public_lib.dir/build.make
lib/libpublic_lib.a: tool/public/CMakeFiles/public_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/forlinx/shell/tsyewu/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library ../../lib/libpublic_lib.a"
	cd /home/forlinx/shell/tsyewu/build/tool/public && $(CMAKE_COMMAND) -P CMakeFiles/public_lib.dir/cmake_clean_target.cmake
	cd /home/forlinx/shell/tsyewu/build/tool/public && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/public_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tool/public/CMakeFiles/public_lib.dir/build: lib/libpublic_lib.a

.PHONY : tool/public/CMakeFiles/public_lib.dir/build

tool/public/CMakeFiles/public_lib.dir/requires: tool/public/CMakeFiles/public_lib.dir/src/crc.c.o.requires
tool/public/CMakeFiles/public_lib.dir/requires: tool/public/CMakeFiles/public_lib.dir/src/public.c.o.requires
tool/public/CMakeFiles/public_lib.dir/requires: tool/public/CMakeFiles/public_lib.dir/src/type.c.o.requires
tool/public/CMakeFiles/public_lib.dir/requires: tool/public/CMakeFiles/public_lib.dir/src/utily.c.o.requires

.PHONY : tool/public/CMakeFiles/public_lib.dir/requires

tool/public/CMakeFiles/public_lib.dir/clean:
	cd /home/forlinx/shell/tsyewu/build/tool/public && $(CMAKE_COMMAND) -P CMakeFiles/public_lib.dir/cmake_clean.cmake
.PHONY : tool/public/CMakeFiles/public_lib.dir/clean

tool/public/CMakeFiles/public_lib.dir/depend:
	cd /home/forlinx/shell/tsyewu/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/forlinx/shell/tsyewu /home/forlinx/shell/tsyewu/tool/public /home/forlinx/shell/tsyewu/build /home/forlinx/shell/tsyewu/build/tool/public /home/forlinx/shell/tsyewu/build/tool/public/CMakeFiles/public_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tool/public/CMakeFiles/public_lib.dir/depend

