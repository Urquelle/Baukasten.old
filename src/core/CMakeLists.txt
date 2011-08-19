set (
    core_SRCS
    src/abstract_space.cpp
    src/action.cpp
    src/drawable.cpp
    src/entity.cpp
    src/entity_type.cpp
    src/form.cpp
	src/game_entity.cpp
	src/inc_actions.cpp
	src/inc_states.cpp
    src/logical_space.cpp
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
	include/inc_actions.h
	include/inc_states.h
    include/logical_space.h
    include/state.h
    include/virtual_space.h
)

set( targetLibs "" )

# compile lua action class
if( DEFINED USE_LUA )
	message(STATUS "lua dependencies on")

	find_library( luaLibPath lua )
	message(STATUS ${luaLib})

	# use the source only if the lib's found
	if (NOT ${luaLibPath} EQUAL "")
		set(
			targetLibs
			${targetLibs}
			lua
		)

		set (
			core_SRCS
			${core_SRCS}
			src/action_lua.cpp
		)

		set (
			core_HEADER
			${core_HEADER}
			include/action_lua.h
		)
	else()
		message(ERROR "liblua not found!")
	endif()
else()
	message(STATUS "lua dependencies off")
endif()

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

if (NOT ${targetLibs} EQUAL "" )
	message(STATUS "linking project " ${targetLibs})

	target_link_libraries(
		Baukasten
		${targetLibs}
	)
endif()

install(TARGETS Baukasten LIBRARY DESTINATION lib/)
install(FILES ${core_HEADER} DESTINATION include/)
