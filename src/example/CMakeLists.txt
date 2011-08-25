set(
    example_SRCS
	entities/entities.cpp
	entities/entity_types.cpp
    entities/example_game.cpp
    main.cpp
)

include_directories( ${core_include_dir} ${CMAKE_CURRENT_SOURCE_DIR} )
link_directories( ${core_lib_dir} ${CMAKE_INSTALL_PREFIX}/lib )

add_executable( exampleGame ${example_SRCS})
target_link_libraries( exampleGame Baukasten SLB)
set_target_properties( exampleGame PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)
install(TARGETS exampleGame RUNTIME DESTINATION bin/)
install(DIRECTORY scripts DESTINATION bin/)
