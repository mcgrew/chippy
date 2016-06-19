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

    include_directories(${SDL_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_HOME_DIRECTORY}" "${CMAKE_HOME_DIRECTORY}/gme"
        "${CMAKE_BINARY_DIR}/gme")

    add_executable(chippy ${player_SRCS})
    target_link_libraries(chippy ${SDL_LIBRARY} gme)

    # Is not to be installed though
else()
    message("SDL library not found, disabling player demo build")
endif()
