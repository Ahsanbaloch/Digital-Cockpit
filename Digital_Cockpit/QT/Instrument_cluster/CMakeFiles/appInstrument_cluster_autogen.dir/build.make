# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/ahsan/Documents/Automotive-Software-Engineering-Project/Digital_Cockpit/QT/Instrument_cluster

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ahsan/Documents/Automotive-Software-Engineering-Project/Digital_Cockpit/QT/Instrument_cluster

# Utility rule file for appInstrument_cluster_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/appInstrument_cluster_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/appInstrument_cluster_autogen.dir/progress.make

CMakeFiles/appInstrument_cluster_autogen: appInstrument_cluster_autogen/timestamp

appInstrument_cluster_autogen/timestamp: /home/ahsan/Qt/6.8.0/gcc_64/libexec/moc
appInstrument_cluster_autogen/timestamp: CMakeFiles/appInstrument_cluster_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/ahsan/Documents/Automotive-Software-Engineering-Project/Digital_Cockpit/QT/Instrument_cluster/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target appInstrument_cluster"
	/usr/bin/cmake -E cmake_autogen /home/ahsan/Documents/Automotive-Software-Engineering-Project/Digital_Cockpit/QT/Instrument_cluster/CMakeFiles/appInstrument_cluster_autogen.dir/AutogenInfo.json ""
	/usr/bin/cmake -E touch /home/ahsan/Documents/Automotive-Software-Engineering-Project/Digital_Cockpit/QT/Instrument_cluster/appInstrument_cluster_autogen/timestamp

appInstrument_cluster_autogen: CMakeFiles/appInstrument_cluster_autogen
appInstrument_cluster_autogen: appInstrument_cluster_autogen/timestamp
appInstrument_cluster_autogen: CMakeFiles/appInstrument_cluster_autogen.dir/build.make
.PHONY : appInstrument_cluster_autogen

# Rule to build all files generated by this target.
CMakeFiles/appInstrument_cluster_autogen.dir/build: appInstrument_cluster_autogen
.PHONY : CMakeFiles/appInstrument_cluster_autogen.dir/build

CMakeFiles/appInstrument_cluster_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/appInstrument_cluster_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/appInstrument_cluster_autogen.dir/clean

CMakeFiles/appInstrument_cluster_autogen.dir/depend:
	cd /home/ahsan/Documents/Automotive-Software-Engineering-Project/Digital_Cockpit/QT/Instrument_cluster && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ahsan/Documents/Automotive-Software-Engineering-Project/Digital_Cockpit/QT/Instrument_cluster /home/ahsan/Documents/Automotive-Software-Engineering-Project/Digital_Cockpit/QT/Instrument_cluster /home/ahsan/Documents/Automotive-Software-Engineering-Project/Digital_Cockpit/QT/Instrument_cluster /home/ahsan/Documents/Automotive-Software-Engineering-Project/Digital_Cockpit/QT/Instrument_cluster /home/ahsan/Documents/Automotive-Software-Engineering-Project/Digital_Cockpit/QT/Instrument_cluster/CMakeFiles/appInstrument_cluster_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/appInstrument_cluster_autogen.dir/depend

