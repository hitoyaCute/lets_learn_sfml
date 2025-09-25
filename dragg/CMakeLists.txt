cmake_minimum_required(VERSION 3.28)

# set name
project(viewport LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# set version 
set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_FLAGS -O2)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# downlaold and install the sfml lib
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME}
  ./src/app/main.cpp
  ./src/gui/RenderManager.cpp
  ./src/gui/Shapes/BasicShape.cpp
  ./src/gui/ViewPort.cpp
  # ./src/gui/Events/event.cpp
  # ./src/gui/Interpolated/Interpolated.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/lib")


# put the files next to the executables
add_custom_command(
  TARGET ${PROJECT_NAME}
  COMMENT "Copy res directory"
  PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)

set(SFML_LIBS SFML::Graphics SFML::Window SFML::System)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBS})

# set optimizer flag for sfml libraries
set_target_properties(sfml-graphics PROPERTIES COMPILE_OPTIONS "-O2")
set_target_properties(sfml-window   PROPERTIES COMPILE_OPTIONS "-O2")
set_target_properties(sfml-system   PROPERTIES COMPILE_OPTIONS "-O2")










