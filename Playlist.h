

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include <string>

#include "gme/gme.h"

using std::string;
using std::vector;
using std::size_t;

class Track {
public:
  Track(string file);
  Track(string file, size_t tracknum);
  ~Track();
  string file;
  size_t tracknum;
  string trackname;
  bool is(string file, size_t tracknum);
};

class Playlist {
public:
  Playlist();
  Playlist(string playlist_file);
  ~Playlist();
  vector<Track> tracks; 
  vector<size_t> play_order;
  
  bool add_track(string file, size_t tracknum);
  size_t add_tracks(string file);
  bool remove_track(size_t index);
  Track current_track();
  Track get_track(size_t index);
  void shuffle(bool shuffle, bool live);
  void repeat(bool);

  size_t advance();
  size_t back();
  size_t jump_to(size_t tracknum);
  bool at_beginning();
  bool at_end();
  size_t size();
  void clear();
  
private:
  
  size_t current_track_;
  size_t tracks_from_file(string file);
  bool repeat_;

};

#endif
