
#include "Playlist.h"

#include <algorithm>


/**
 * Creates a new playlist track from the given file
 * 
 * @param file The music file for this track.
 */
Track::Track(std::string file) {
  this->file = file;
  this->tracknum = 1;
  this->trackname = std::string();
}

/**
 * Creates a new playlist track from the given track in the given file
 * 
 * @param file The music file for this track.
 * @param tracknum The track number from the file for this entry
 * @return 
 */
Track::Track(std::string file, std::size_t tracknum) {
  this->file = file;
  this->tracknum = tracknum;
}

/**
 * Destroys the track.
 */
Track::~Track() {
}

bool Track::is(std::string file, std::size_t tracknum) {
}

/**
 * Creates a new empty playlist.
 */
Playlist::Playlist() {
  this->current_track_ = 0;
  this->size = 0;
}

/**
 * Creates a new playlist from the given playlist file.
 * 
 * @param 
 * @return 
 */
Playlist::Playlist(std::string playlist_file) {
}

/**
 * Destroys the playlist
 */
Playlist::~Playlist() {
}

/**
 * Adds a track to the playlist
 * 
 * @param file The music file for the new track.
 * @param tracknum The track number from the music file for the new track.
 * @return true if the operation succeeded.
 */
bool Playlist::add_track(std::string file, std::size_t tracknum) {
}

/**
 * Adds all tracks from the given music file.
 * 
 * @param file The file to read tracks from.
 * @return The number of new tracks added.
 */
std::size_t Playlist::add_tracks(std::string file) {
}

/**
 * Removes a track from the playlist
 * 
 * @param index The index of the track to be removed.
 * @return The removed track.
 */
Track Playlist::remove_track(std::size_t index) {
}

/**
 * Returns the current track in the playlist
 * 
 * @return The current track
 */
Track Playlist::current_track() {
}

/**
 * Returns the track at the given position in the playlist
 * 
 * @param index The index of the track to be retrieved.
 * @return The requested track.
 */
Track Playlist::get_track(std::size_t index) {
}

/**
 * Shuffles the playlist
 */
void Playlist::shuffle() {
}

/**
 * Advances the playlist by one track.
 * 
 * @return The new current track index.
 */
std::size_t Playlist::advance() {
}

/**
 * Goes back one track in the playlist.
 * 
 * @return The new current track index.
 */
std::size_t Playlist::back() {
}

/**
 * Jumps to the given track index.
 * 
 * @param tracknum The index of the new track.
 * @return The new current track index.
 */
std::size_t jump_to(std::size_t tracknum) {
}




