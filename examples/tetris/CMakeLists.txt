project( Tetris )

set(
	tetris_SRCS
	block_form.cpp
	field_form.cpp
	form2d.cpp
	game.cpp
	main.cpp
	score_form.cpp
)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_executable( tetris ${tetris_SRCS} )
target_link_libraries( tetris Baukasten )
install(TARGETS tetris  RUNTIME DESTINATION tetris)
install(DIRECTORY media DESTINATION tetris)
install(DIRECTORY scripts DESTINATION tetris)
