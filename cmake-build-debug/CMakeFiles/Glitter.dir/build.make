# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\CLion 2021.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CLion 2021.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Glitter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Glitter\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Glitter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Glitter.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Glitter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Glitter.dir/flags.make

CMakeFiles/Glitter.dir/Glitter/Sources/main.cpp.obj: CMakeFiles/Glitter.dir/flags.make
CMakeFiles/Glitter.dir/Glitter/Sources/main.cpp.obj: CMakeFiles/Glitter.dir/includes_CXX.rsp
CMakeFiles/Glitter.dir/Glitter/Sources/main.cpp.obj: ../Glitter/Sources/main.cpp
CMakeFiles/Glitter.dir/Glitter/Sources/main.cpp.obj: CMakeFiles/Glitter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Glitter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Glitter.dir/Glitter/Sources/main.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Glitter.dir/Glitter/Sources/main.cpp.obj -MF CMakeFiles\Glitter.dir\Glitter\Sources\main.cpp.obj.d -o CMakeFiles\Glitter.dir\Glitter\Sources\main.cpp.obj -c D:\Glitter\Glitter\Sources\main.cpp

CMakeFiles/Glitter.dir/Glitter/Sources/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Glitter.dir/Glitter/Sources/main.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Glitter\Glitter\Sources\main.cpp > CMakeFiles\Glitter.dir\Glitter\Sources\main.cpp.i

CMakeFiles/Glitter.dir/Glitter/Sources/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Glitter.dir/Glitter/Sources/main.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Glitter\Glitter\Sources\main.cpp -o CMakeFiles\Glitter.dir\Glitter\Sources\main.cpp.s

CMakeFiles/Glitter.dir/Glitter/Vendor/glad/src/glad.c.obj: CMakeFiles/Glitter.dir/flags.make
CMakeFiles/Glitter.dir/Glitter/Vendor/glad/src/glad.c.obj: CMakeFiles/Glitter.dir/includes_C.rsp
CMakeFiles/Glitter.dir/Glitter/Vendor/glad/src/glad.c.obj: ../Glitter/Vendor/glad/src/glad.c
CMakeFiles/Glitter.dir/Glitter/Vendor/glad/src/glad.c.obj: CMakeFiles/Glitter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Glitter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Glitter.dir/Glitter/Vendor/glad/src/glad.c.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Glitter.dir/Glitter/Vendor/glad/src/glad.c.obj -MF CMakeFiles\Glitter.dir\Glitter\Vendor\glad\src\glad.c.obj.d -o CMakeFiles\Glitter.dir\Glitter\Vendor\glad\src\glad.c.obj -c D:\Glitter\Glitter\Vendor\glad\src\glad.c

CMakeFiles/Glitter.dir/Glitter/Vendor/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Glitter.dir/Glitter/Vendor/glad/src/glad.c.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Glitter\Glitter\Vendor\glad\src\glad.c > CMakeFiles\Glitter.dir\Glitter\Vendor\glad\src\glad.c.i

CMakeFiles/Glitter.dir/Glitter/Vendor/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Glitter.dir/Glitter/Vendor/glad/src/glad.c.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Glitter\Glitter\Vendor\glad\src\glad.c -o CMakeFiles\Glitter.dir\Glitter\Vendor\glad\src\glad.c.s

# Object files for target Glitter
Glitter_OBJECTS = \
"CMakeFiles/Glitter.dir/Glitter/Sources/main.cpp.obj" \
"CMakeFiles/Glitter.dir/Glitter/Vendor/glad/src/glad.c.obj"

# External object files for target Glitter
Glitter_EXTERNAL_OBJECTS =

Glitter/Glitter.exe: CMakeFiles/Glitter.dir/Glitter/Sources/main.cpp.obj
Glitter/Glitter.exe: CMakeFiles/Glitter.dir/Glitter/Vendor/glad/src/glad.c.obj
Glitter/Glitter.exe: CMakeFiles/Glitter.dir/build.make
Glitter/Glitter.exe: Glitter/Vendor/assimp/lib/libassimpd.a
Glitter/Glitter.exe: lib/libglfw3d.a
Glitter/Glitter.exe: lib/libBulletDynamicsd.a
Glitter/Glitter.exe: lib/libBulletCollisiond.a
Glitter/Glitter.exe: lib/libLinearMathd.a
Glitter/Glitter.exe: C:/Program\ Files\ (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/i686-w64-mingw32/lib/libz.a
Glitter/Glitter.exe: CMakeFiles/Glitter.dir/linklibs.rsp
Glitter/Glitter.exe: CMakeFiles/Glitter.dir/objects1.rsp
Glitter/Glitter.exe: CMakeFiles/Glitter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Glitter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Glitter\Glitter.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Glitter.dir\link.txt --verbose=$(VERBOSE)
	"C:\Program Files (x86)\CLion 2021.3\bin\cmake\win\bin\cmake.exe" -E copy_directory D:/Glitter/Glitter/Shaders D:/Glitter/cmake-build-debug/Glitter

# Rule to build all files generated by this target.
CMakeFiles/Glitter.dir/build: Glitter/Glitter.exe
.PHONY : CMakeFiles/Glitter.dir/build

CMakeFiles/Glitter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Glitter.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Glitter.dir/clean

CMakeFiles/Glitter.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Glitter D:\Glitter D:\Glitter\cmake-build-debug D:\Glitter\cmake-build-debug D:\Glitter\cmake-build-debug\CMakeFiles\Glitter.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Glitter.dir/depend
