project( Tetris )

set(
	tetris_SRCS
	form2d.cpp
	game.cpp
	main.cpp
)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_executable( tetris ${tetris_SRCS} )
target_link_libraries( tetris Baukasten SLB bz2 jpeg png gif )
install(TARGETS tetris  RUNTIME DESTINATION tetris/)
install(DIRECTORY media DESTINATION tetris/)
