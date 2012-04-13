project( Tetris )

set(
	tetris_SRCS
	field_form.cpp
	game.cpp
	main.cpp
)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_executable( tetris ${tetris_SRCS} )
target_link_libraries( tetris Baukasten )
install(TARGETS tetris  RUNTIME DESTINATION tetris)
install(DIRECTORY media DESTINATION tetris)
install(DIRECTORY scripts DESTINATION tetris)
