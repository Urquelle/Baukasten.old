set (
    core_SRCS
    src/abstract_space.cpp
    src/game.cpp
    src/logical_space.cpp
    src/virtual_space.cpp
)

set (
    core_HEADER
    include/abstract_space.h
    include/action.h
    include/entity.h
    include/form.h
    include/game.h
    include/global.h
    include/logical_space.h
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
