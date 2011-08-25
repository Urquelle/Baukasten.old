set(
    example_SRCS
	actions/render_scene.cpp
	entities/basic_type.cpp
    entities/example_game.cpp
	entities/unit.cpp
	entities/world_map.cpp
	forms/ogre_form.cpp
	forms/world_map_form.cpp
    main.cpp
)

include_directories( ${core_include_dir} ${CMAKE_CURRENT_SOURCE_DIR} )
link_directories( ${core_lib_dir} ${CMAKE_INSTALL_PREFIX}/lib )

add_executable( exampleGame ${example_SRCS})
target_link_libraries( exampleGame Baukasten SLB OgreMain )
set_target_properties( exampleGame PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)
install(TARGETS exampleGame RUNTIME DESTINATION bin/)
install(DIRECTORY scripts DESTINATION bin/)
