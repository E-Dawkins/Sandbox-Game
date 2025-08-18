cmake_minimum_required(VERSION 3.25)

# Define our build configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Available build configurations" FORCE)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Create project
set(PROJECT_NAME SandboxGame)
project(${PROJECT_NAME} LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch raylib
include(FetchContent)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5) # raylib seems to use cmake 3.5, so we need to support it
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        4.5.0
)
FetchContent_MakeAvailable(raylib)

# This function will be used to recursively add filters that are the same as our sub-directories
# i.e. src/game/... or include/game/...
function(group_sources_by_folder target file_list)
	foreach(file IN LISTS ${file_list})
		# Get relative path from project root
		file(RELATIVE_PATH rel_path ${CMAKE_CURRENT_SOURCE_DIR} ${file})

		# Extract folder path
		get_filename_component(folder ${rel_path} PATH)

		# Replace slashes with backslashes for Visual Studio
		string(REPLACE "/" "\\" group_name ${folder})

		source_group("${group_name}" FILES ${file})
	endforeach()
endfunction()

# Recursively find all .h and .cpp files
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# Add filters recursively
group_sources_by_folder(${PROJECT_NAME} SOURCE_FILES)
group_sources_by_folder(${PROJECT_NAME} HEADER_FILES)

# Set our include directory to include/...
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Setup compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE 
	/W4 
	/WX 
	/external:W0 
	/external:anglebrackets
)

# Link raylib to our project
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Set startup project in Visual Studio to our project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})