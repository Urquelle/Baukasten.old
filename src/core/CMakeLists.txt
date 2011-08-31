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

include_directories(
	"/usr/include/sigc++-2.0"
	"/usr/lib64/sigc++-2.0/include"
)

# compile lua action class
if( WITH_LUA )
	set( core_SRCS ${core_SRCS} core/src/lua/action.cpp )
	set( slb_LINKDIR ${CMAKE_HOME_DIRECTORY}/lib/ )
	install(FILES ${CMAKE_HOME_DIRECTORY}/lib/libSLB.so DESTINATION lib/)
endif()

