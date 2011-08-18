set(
    example_SRCS
	entities.cpp
    example_game.cpp
    frame_listener.cpp
    main.cpp
)

include_directories( ${CMAKE_INSTALL_PREFIX}/include )
link_directories( ${CMAKE_INSTALL_PREFIX}/lib )

add_definitions( -DUSE_OGRE )

add_executable(
    exampleGame
    ${example_SRCS}
)

target_link_libraries( exampleGame Baukasten OgreMain OIS )

install(TARGETS exampleGame RUNTIME DESTINATION bin/)
