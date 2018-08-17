cmake_minimum_required(VERSION 3.10)
project(rpgSFML)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp Entity.cpp Entity.h Player.cpp Player.h Projectile.cpp Projectile.h Enemy.cpp Enemy.h Random.cpp Random.h)
add_executable(rpgSFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(rpgSFML ${SFML_LIBRARIES})
endif ()
