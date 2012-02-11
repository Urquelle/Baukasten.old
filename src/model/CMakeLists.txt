set (
    model_SRCS
    model/src/action.cpp
	model/src/action_lambda.cpp
	model/src/action_manager.cpp
	model/src/core_services.cpp
    model/src/drawable.cpp
    model/src/entity.cpp
	model/src/entity_manager.cpp
    model/src/entity_type.cpp
    model/src/form.cpp
	model/src/game_entity.cpp
    model/src/logical_space.cpp
    model/src/state.cpp
	model/src/state_manager.cpp
    model/src/virtual_space.cpp
)

include_directories(
	"/usr/include/sigc++-2.0"
	"/usr/lib64/sigc++-2.0/include"
)

# compile lua action class
if( WITH_LUA )
	set( model_SRCS ${model_SRCS} model/src/lua/action_lua.cpp )
	set( slb_LINKDIR ${CMAKE_SOURCE_DIR}/lib/ )
	install(FILES ${CMAKE_SOURCE_DIR}/lib/libSLB.so DESTINATION lib/)
endif()

