set(
    example_SRCS
	entities.cpp
	entity_types.cpp
    example_game.cpp
    main.cpp
)

include_directories( ${CMAKE_INSTALL_PREFIX}/include )
link_directories( ${CMAKE_INSTALL_PREFIX}/lib )

add_executable(
    exampleGame
    ${example_SRCS}
)

target_link_libraries( exampleGame Baukasten SLB)

install(TARGETS exampleGame RUNTIME DESTINATION bin/)
