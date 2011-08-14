set (
    core_SRCS
    core/abstract_space.cpp
    core/form.cpp
    core/game.cpp
    core/logical_space.cpp
    core/virtual_space.cpp
)

set (
    main_SRCS
    main.cpp
)

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=gnu++0x")
endif()

add_executable(
    eisenfaust
    ${core_SRCS}
    ${main_SRCS}
)
