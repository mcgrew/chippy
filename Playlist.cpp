
#include "Playlist.h"

#include <algorithm>
#include <random>
#include <chrono>
#include <ctype.h>

using std::string;
using std::vector;
using std::size_t;


/**
 * Creates a new playlist track from the given file
 * 
 * @param file The music file for this track.
 */
Track::Track(string file) {
  this->file = file;
  this->tracknum = 1;
  this->trackname = string();
}

/**
 * Creates a new playlist track from the given track in the given file
 * 
 * @param file The music file for this track.
 * @param tracknum The track number from the file for this entry
 * @return 
 */
Track::Track(string file, size_t tracknum) {
  this->file = file;
  this->tracknum = tracknum;
}

/**
 * Destroys the track.
 */
Track::~Track() {
}

bool Track::is(string file, size_t tracknum) {
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
Playlist::Playlist(string playlist_file) {
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
bool Playlist::add_track(string file, size_t tracknum) {
  this->play_order.emplace_back(this->tracks.size());
  this->tracks.emplace_back(file, tracknum);
  return true;
}

/**
 * Adds all tracks from the given music file.
 * 
 * @param file The file to read tracks from.
 * @return The number of new tracks added.
 */
size_t Playlist::add_tracks(string file) {
  return 0;
}

/**
 * Removes a track from the playlist
 * 
 * @param index The index of the track to be removed.
 * @return true if the index is not greater than the size of the playlist
 */
bool Playlist::remove_track(size_t index) {
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
Track Playlist::get_track(size_t index) {
  return this->tracks.at(this->play_order[index]);
}

/**
 * Shuffles the playlist
 */
void Playlist::shuffle(bool shuffle, bool live) {
  size_t now_playing = this->play_order[this->current_track_];
  if (shuffle) {
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(this->play_order.begin(), this->play_order.end(), 
              std::default_random_engine( seed ));
    // if this is a live shuffle, move the currently playing track to the front
    // and set our track pointer to it.
    if (live) {
      for (size_t i=0; i < this->tracks.size(); i++) {
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
    for (size_t i=0; i < this->tracks.size(); i++) {
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
size_t Playlist::advance() {
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
size_t Playlist::back() {
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
size_t Playlist::jump_to(size_t tracknum) {
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

size_t Playlist::size() {
  return this->tracks.size();
}

void Playlist::clear() {
  this->tracks.clear();
  this->play_order.clear();
}


