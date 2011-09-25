project( Eisenfaust )

set(
    example_SRCS
	entities/basic_type.cpp
	entities/city.cpp
    entities/game.cpp
	entities/unit.cpp
	entities/world_map.cpp
	forms/city_form.cpp
	forms/form2d.cpp
	forms/menu_form.cpp
    main.cpp
)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
add_executable( eisenfaust ${example_SRCS})
target_link_libraries( eisenfaust Baukasten SLB bz2 jpeg png gif )

install(TARGETS eisenfaust RUNTIME DESTINATION bin/)
install(DIRECTORY scripts DESTINATION bin/)
install(DIRECTORY media DESTINATION bin/)
