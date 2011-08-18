if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=gnu++0x")
endif()

add_subdirectory( core )
add_subdirectory( example )
