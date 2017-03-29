cmake_minimum_required( VERSION 3.0 )
project( include-game-test )

add_subdirectory( deps/engine ${CMAKE_CURRENT_BINARY_DIR}/deps/engine )

include_directories(${GAME_INCLUDES})
add_subdirectory( src )
