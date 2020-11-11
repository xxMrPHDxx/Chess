cmake_minimum_required( VERSION 3.10 )
project( chess )

include_directories( "D:/SFML-2.5.1/include" ${CMAKE_CURRENT_SOURCE_DIR}/include )
link_directories( "D:/SFML-2.5.1/lib" )

file( GLOB_RECURSE SOURCES src/*.cpp )

add_definitions( -DOSTREAM_OVERRIDE )

add_executable( chess ${SOURCES} )
target_link_libraries( chess -lsfml-graphics -lsfml-window -lsfml-system )