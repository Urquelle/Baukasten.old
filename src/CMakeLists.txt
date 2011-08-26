set( CORE_INC ${CMAKE_CURRENT_SOURCE_DIR}/core/include )

set (
    core_SRCS
    core/src/action.cpp
	core/src/action_manager.cpp
    core/src/drawable.cpp
    core/src/entity.cpp
	core/src/entity_manager.cpp
    core/src/entity_type.cpp
    core/src/form.cpp
	core/src/game_entity.cpp
    core/src/logical_space.cpp
	core/src/object_manager.cpp
    core/src/state.cpp
	core/src/state_manager.cpp
    core/src/virtual_space.cpp
)

option( WITH_LUA  "compile with Lua support." TRUE )
option( WITH_OGRE  "compile with OGRE support." TRUE )

if( WITH_OGRE )
	add_definitions( -DWITH_OGRE )
endif()

# compile lua action class
if( DEFINED WITH_LUA )
	set( core_SRCS ${core_SRCS} core/src/lua/action.cpp )
	set( slb_LINKDIR ${CMAKE_CURRENT_SOURCE_DIR}/core/lib/ )
	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/core/lib/libSLB.so DESTINATION lib/)
endif()

include_directories( ${CORE_INC} )
link_directories( ${slb_LINKDIR} )

add_definitions( -DEXPORT_LIB=1 )
add_library( Baukasten SHARED ${core_SRCS} )

set_target_properties( Baukasten PROPERTIES SOVERSION 0.0.1 )

install(DIRECTORY core/include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install(TARGETS Baukasten LIBRARY DESTINATION lib/)
install(FILES ${core_HEADER} DESTINATION include/)
