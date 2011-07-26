cmake_minimum_required(VERSION 2.8)

set (Eisenfaust_SRCS
    main.cpp
    game.cpp)

add_executable(eisenfaust ${Eisenfaust_SRCS})

install(TARGETS eisenfaust DESTINATION bin)
