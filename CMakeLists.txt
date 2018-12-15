cmake_minimum_required(VERSION 2.8)
find_package(SDL QUIET)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(player_SRCS Audio_Scope.cpp
                Audio_Scope.h
                Music_Player.cpp
                Music_Player.h
                Playlist.cpp
                Playlist.h
                player.cpp)

if(SDL_FOUND)
    message(" ** SDL library located, player is available to be built")

    include_directories("${SDL_INCLUDE_DIR}" "${CMAKE_SOURCE_DIR}"
        "${CMAKE_HOME_DIRECTORY}" "${CMAKE_HOME_DIRECTORY}/gme"
        "${CMAKE_BINARY_DIR}/gme")

    add_executable(chippy ${player_SRCS})
    target_link_libraries(chippy ${SDL_LIBRARY} gme)

    # copy the compile_commands.json to the source directory
    add_custom_command(TARGET chippy POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )


    # Is not to be installed though
else()
    message("SDL library not found, disabling player demo build")
endif()

