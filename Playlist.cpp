
#include "Playlist.h"

#include <algorithm>
#include <random>


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
  return (!this->file.compare(file) && this->tracknum == tracknum);
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
  this->tracks.emplace_back(file, tracknum);
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
 * @return true if the index is not greater than the size of the playlist
 */
bool Playlist::remove_track(std::size_t index) {
  // this probably isn't the right way to do this...
  if (index < this->tracks.size()) {
//    delete this->tracks.at(index)
    for (size_t i = index; i < this->tracks.size()-1; i++) {
      this->tracks[i] = this->tracks[i+1];
    }
    this->tracks.pop_back();
    return true;
  }
  return false;
}

/**
 * Returns the current track in the playlist
 * 
 * @return The current track
 */
Track Playlist::current_track() {
  return this->tracks.at(this->current_track_);
}

/**
 * Returns the track at the given position in the playlist
 * 
 * @param index The index of the track to be retrieved.
 * @return The requested track.
 */
Track Playlist::get_track(std::size_t index) {
  return this->tracks.at(index);
}

/**
 * Shuffles the playlist
 */
void Playlist::shuffle() {
  std::shuffle(this->tracks.begin(), this->tracks.end(), 
            std::default_random_engine());
}

/**
 * Advances the playlist by one track.
 * 
 * @return The new current track index.
 */
std::size_t Playlist::advance() {
  if (this->current_track_ < this->tracks.size()-1)
    this->current_track_++;
  return this->current_track_;
}

/**
 * Goes back one track in the playlist.
 * 
 * @return The new current track index.
 */
std::size_t Playlist::back() {
  if (this->current_track_ > 0)
    this->current_track_--;
  return this->current_track_;
}

/**
 * Jumps to the given track index.
 * 
 * @param tracknum The index of the new track.
 * @return The new current track index.
 */
std::size_t Playlist::jump_to(std::size_t tracknum) {
  if (tracknum < this->tracks.size())
    this->current_track_ = tracknum;
  return this->current_track_;
}




