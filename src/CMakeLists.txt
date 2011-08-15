if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=gnu++0x")
endif()

set(
    main_SRCS
    main.cpp
)

add_executable( ef ${main_SRCS} )

add_subdirectory(
    core
)

add_subdirectory(
    example
)

install(TARGETS ef RUNTIME DESTINATION bin)
