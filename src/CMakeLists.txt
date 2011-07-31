cmake_minimum_required(VERSION 2.8)

set (Eisenfaust_SRCS
    main.cpp
    game.cpp
    abstract_space.cpp
    logical_space.cpp
    virtual_space.cpp)

add_executable(eisenfaust ${Eisenfaust_SRCS})

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=gnu++0x")
endif()

install(TARGETS eisenfaust DESTINATION bin)
