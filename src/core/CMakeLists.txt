set (
    core_SRCS
    src/abstract_space.cpp
    src/action.cpp
    src/drawable.cpp
    src/entity.cpp
    src/entity_type.cpp
    src/form.cpp
	src/game_entity.cpp
    src/logical_space.cpp
	src/object.cpp
    src/state.cpp
    src/virtual_space.cpp
)

set (
    core_HEADER
    include/abstract_space.h
    include/action.h
    include/drawable.h
    include/entity.h
    include/entity_type.h
    include/form.h
	include/game_entity.h
    include/generic_state.h
    include/global.h
    include/logical_space.h
	include/object.h
    include/state.h
    include/virtual_space.h
)

include_directories( include )
add_definitions( -DEXPORT_LIB=1 )

add_library(
    Baukasten
    SHARED
    ${core_SRCS}
)

set_target_properties(
    Baukasten
    PROPERTIES SOVERSION 0.0.1
)

install(TARGETS Baukasten LIBRARY DESTINATION lib/)
install(FILES ${core_HEADER} DESTINATION include/)
