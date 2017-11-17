#ifndef CSCI_311_PLAYLIST_H
#define CSCI_311_PLAYLIST_H

#include "DoublyLinkedList.h"
using std::string;

class Playlist {
public:
   void mainLoop();                    // process commands until done
private:
   DoublyLinkedList dll;               // playlist stored in doubly linked list
   
   void processCommand();              // read and process one playlist command
   void processAppendSong(string&);    // appends song to playlist
   void processInsertBefore(string&);  // insert song before current pos
   void processInsertAfter(string&);   // insert song after current pos
   void processRemoveSong(string&);    // removes the specified song
   void processPlayCurrent();          // "plays" song at the current position
   void processGotoSong(string&);      // sets the current position to song
   void processGotoFirstSong();        // goes to the first song
   void processGotoLastSong();         // goes to the last song
   void processNextSong();             // go to next song
   void processPrevSong();             // go to previous song
   void processPlayForward();          // "play" all songs from current to end
   void processPlayReverse();          // "play" all songs from current to start
};

#endif // CSCI_311_PLAYLIST_H