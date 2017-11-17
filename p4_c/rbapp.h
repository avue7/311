#ifndef RBAPP_H
#define RBAPP_H

#include <string>
#include "rbtree.h"

using std::string;

class RBapp {
    public:
        void mainLoop();               // process commands until done
    private:
        RBTree myRBT;
        void processCommand();         // read and process one command
        void processInsert(string&);   // insert into red-black tree
        void processPrint();           // print tree
        void processFind(string&);     // find & print all occurances of a key
        void processDelete(string&);   // delete from the red-black tree
        void processQuit();
};

#endif // RBAPP_H