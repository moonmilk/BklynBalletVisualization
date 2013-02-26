#ifndef OSCRECEIVER_H
#define OSCRECEIVER_H
#include "ofxOscReceiver.h"
#include "TuioApp.h"

typedef map<int,tuioCursor> cursorMap;

class oscReceiver
{
    public:
        oscReceiver(TuioApp *parent,int p=3333);
        virtual ~oscReceiver();
        void processOsc();
    protected:

    private:
    int port;
    TuioApp *parent;
    ofxOscReceiver receiver;
    cursorMap cursors;
    int frame_stale;
    int prevFrame;
    int lastFrame;
};

#endif // OSCRECEIVER_H
