

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include <string>

#include "gme/gme.h"

class Track {
public:
  Track(std::string file);
  Track(std::string file, std::size_t tracknum);
  ~Track();
  std::string file;
  std::string tracknum;
  std::string trackname;
  bool is(std::string file, std::size_t tracknum);
};

class Playlist {
public:
  Playlist();
  Playlist(std::string playlist_file);
  ~Playlist();
  std::vector<Track> tracks; 
  
  bool add_track(std::string file, std::size_t tracknum);
  std::size_t add_tracks(std::string file);
  Track remove_track(std::size_t index);
  Track current_track();
  Track get_track(std::size_t index);
  void shuffle();
  std::size_t advance();
  std::size_t back();
  std::size_t jump_to(std::size_t tracknum);
  
private:
  
  std::size_t current_track_;
  std::size_t size;
  std::size_t tracks_from_file(std::string file);

};

#endif
