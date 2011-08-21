if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=gnu++0x")
endif()

set(core_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/core/include)

add_subdirectory( core )
add_subdirectory( example )
