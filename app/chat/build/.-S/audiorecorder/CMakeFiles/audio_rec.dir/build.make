# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/hah/Desktop/chat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hah/Desktop/chat/build/.-S

# Include any dependencies generated for this target.
include audiorecorder/CMakeFiles/audio_rec.dir/depend.make

# Include the progress variables for this target.
include audiorecorder/CMakeFiles/audio_rec.dir/progress.make

# Include the compile flags for this target's objects.
include audiorecorder/CMakeFiles/audio_rec.dir/flags.make

audiorecorder/CMakeFiles/audio_rec.dir/audio_rec.cpp.o: audiorecorder/CMakeFiles/audio_rec.dir/flags.make
audiorecorder/CMakeFiles/audio_rec.dir/audio_rec.cpp.o: ../../audiorecorder/audio_rec.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hah/Desktop/chat/build/.-S/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object audiorecorder/CMakeFiles/audio_rec.dir/audio_rec.cpp.o"
	cd /home/hah/Desktop/chat/build/.-S/audiorecorder && /home/hah/Downloads/orangepi-build/toolchains/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_rec.dir/audio_rec.cpp.o -c /home/hah/Desktop/chat/audiorecorder/audio_rec.cpp

audiorecorder/CMakeFiles/audio_rec.dir/audio_rec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_rec.dir/audio_rec.cpp.i"
	cd /home/hah/Desktop/chat/build/.-S/audiorecorder && /home/hah/Downloads/orangepi-build/toolchains/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hah/Desktop/chat/audiorecorder/audio_rec.cpp > CMakeFiles/audio_rec.dir/audio_rec.cpp.i

audiorecorder/CMakeFiles/audio_rec.dir/audio_rec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_rec.dir/audio_rec.cpp.s"
	cd /home/hah/Desktop/chat/build/.-S/audiorecorder && /home/hah/Downloads/orangepi-build/toolchains/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hah/Desktop/chat/audiorecorder/audio_rec.cpp -o CMakeFiles/audio_rec.dir/audio_rec.cpp.s

# Object files for target audio_rec
audio_rec_OBJECTS = \
"CMakeFiles/audio_rec.dir/audio_rec.cpp.o"

# External object files for target audio_rec
audio_rec_EXTERNAL_OBJECTS =

audiorecorder/libaudio_rec.a: audiorecorder/CMakeFiles/audio_rec.dir/audio_rec.cpp.o
audiorecorder/libaudio_rec.a: audiorecorder/CMakeFiles/audio_rec.dir/build.make
audiorecorder/libaudio_rec.a: audiorecorder/CMakeFiles/audio_rec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hah/Desktop/chat/build/.-S/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libaudio_rec.a"
	cd /home/hah/Desktop/chat/build/.-S/audiorecorder && $(CMAKE_COMMAND) -P CMakeFiles/audio_rec.dir/cmake_clean_target.cmake
	cd /home/hah/Desktop/chat/build/.-S/audiorecorder && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/audio_rec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
audiorecorder/CMakeFiles/audio_rec.dir/build: audiorecorder/libaudio_rec.a

.PHONY : audiorecorder/CMakeFiles/audio_rec.dir/build

audiorecorder/CMakeFiles/audio_rec.dir/clean:
	cd /home/hah/Desktop/chat/build/.-S/audiorecorder && $(CMAKE_COMMAND) -P CMakeFiles/audio_rec.dir/cmake_clean.cmake
.PHONY : audiorecorder/CMakeFiles/audio_rec.dir/clean

audiorecorder/CMakeFiles/audio_rec.dir/depend:
	cd /home/hah/Desktop/chat/build/.-S && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hah/Desktop/chat /home/hah/Desktop/chat/audiorecorder /home/hah/Desktop/chat/build/.-S /home/hah/Desktop/chat/build/.-S/audiorecorder /home/hah/Desktop/chat/build/.-S/audiorecorder/CMakeFiles/audio_rec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : audiorecorder/CMakeFiles/audio_rec.dir/depend

