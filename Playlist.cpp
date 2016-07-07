
#include "Playlist.h"

#include <algorithm>
#include <random>
#include <chrono>


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
  this->play_order.emplace_back(this->tracks.size());
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
      this->play_order[i]--;
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
  return this->tracks.at(this->play_order[this->current_track_]);
}

/**
 * Returns the track at the given position in the playlist
 * 
 * @param index The index of the track to be retrieved.
 * @return The requested track.
 */
Track Playlist::get_track(std::size_t index) {
  return this->tracks.at(this->play_order[index]);
}

/**
 * Shuffles the playlist
 */
void Playlist::shuffle(bool shuffle, bool live) {
  std::size_t now_playing = this->play_order[this->current_track_];
  if (shuffle) {
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(this->play_order.begin(), this->play_order.end(), 
              std::default_random_engine( seed ));
    // if this is a live shuffle, move the currently playing track to the front
    // and set our track pointer to it.
    if (live) {
      for (std::size_t i=0; i < this->tracks.size(); i++) {
        if (this->play_order[i] == now_playing) {
          this->play_order[i] = this->play_order[0];
          break;
        }
        this->play_order[0] = now_playing;
        this->current_track_ = 0;
      }
    }
  } else {
    this->play_order.clear();
    for (std::size_t i=0; i < this->tracks.size(); i++) {
      this->play_order.emplace_back(i);
    }
    if (live)
      this->current_track_ = now_playing;
  }
}

void Playlist::repeat(bool repeat) {
  this->repeat_ = repeat;
}

/**
 * Advances the playlist by one track.
 * 
 * @return The new current track index.
 */
std::size_t Playlist::advance() {
  if (this->current_track_ < this->tracks.size()-1)
    this->current_track_++;
  else if (this->repeat_) {
    this->current_track_ = 0;
  }
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
  else if (this->repeat_) {
    this->current_track_ = this->size() - 1;
  }
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

/**
 * Determines whether the playlist is at the beginning.
 * 
 * @return true if the playlist it at it's first track.
 */
bool Playlist::at_beginning() {
  return !this->repeat_ && this->current_track_ <= 0;
}

/**
 * Determines whether the playlist is at it's end.
 * 
 * @return true if the playlist is at it's last track.
 */
bool Playlist::at_end() {
  return !(this->repeat_ || (this->current_track_ < this->tracks.size() - 1));
}

std::size_t Playlist::size() {
  return this->tracks.size();
}

void Playlist::clear() {
  this->tracks.clear();
  this->play_order.clear();
}


