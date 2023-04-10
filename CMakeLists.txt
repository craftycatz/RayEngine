cmake_minimum_required(VERSION 3.25)
project(cengine C)

set(CMAKE_C_STANDARD 23)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Include SDL2 and SDL2_image directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(cengine main.c utils/utils.h utils/utils.c raycaster/raycaster.h raycaster/raycaster.c player/player.h player/player.c map/map.h map/map.c json/json.h json/json.c datastructures/dynamicarry.h datastructures/hashmap.h datastructures/strtream.h datastructures/dynamicarry.c datastructures/hashmap.c)

# Link SDL2 and SDL2_image libraries to your project
target_link_libraries(cengine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})