set(
    example_SRCS
    example_game.cpp
    main.cpp
)

include_directories( ${CMAKE_INSTALL_PREFIX}/include )
link_directories( ${CMAKE_INSTALL_PREFIX}/lib )

add_executable(
    exampleGame
    ${example_SRCS}
)

target_link_libraries( exampleGame Baukasten )

install(TARGETS exampleGame RUNTIME DESTINATION bin/)
