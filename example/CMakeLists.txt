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

include_directories(
	${Core_INCLUDE_DIR}
	${Graphics_INCLUDE_DIR}
	${Input_INCLUDE_DIR}
	"/usr/include/sigc++-2.0"
	"/usr/lib64/sigc++-2.0/include"
	${CMAKE_CURRENT_SOURCE_DIR}
)

link_directories( ${Core_LIB_DIR} ${CMAKE_INSTALL_PREFIX}/lib )

set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
   set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif("${isSystemDir}" STREQUAL "-1")

add_executable( exampleGame ${example_SRCS})
target_link_libraries( exampleGame Baukasten SLB bz2 jpeg png gif )

install(TARGETS exampleGame RUNTIME DESTINATION bin/)
install(DIRECTORY scripts DESTINATION bin/)
install(DIRECTORY media DESTINATION bin/)
