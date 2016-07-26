cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_FLAGS "-fpermissive")
find_package(SDL QUIET)

set(player_SRCS Audio_Scope.cpp
                Audio_Scope.h
                Music_Player.cpp
                Music_Player.h
                Playlist.cpp
                Playlist.h
                player.cpp)

if(SDL_FOUND)
    message(" ** SDL library located, player is available to be built")
    add_subdirectory(convert2wav)
    add_subdirectory(gme)

    include_directories("${CMAKE_HOME_DIRECTORY}/gme" ${SDL_INCLUDE_DIR})

    add_executable(chippy ${player_SRCS})
    target_link_libraries(chippy ${SDL_LIBRARY} gme)

    # Is not to be installed though
else()
    message("SDL library not found, disabling player demo build")
endif()
