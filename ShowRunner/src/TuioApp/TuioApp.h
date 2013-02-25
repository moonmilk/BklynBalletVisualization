#ifndef TUIOAPP_H
#define TUIOAPP_H

#include <ofMain.h>
#include <ofxOsc.h>

#include "tuioCursor.h"
#include <algorithm>
typedef map<int,tuioCursor> cursorMap;
class TuioApp : public ofBaseApp
{
    public:
        TuioApp();
        virtual ~TuioApp();
        virtual void reset();
        virtual void updateTuioPoints(cursorMap input_tuioCursors);
        virtual void handleOscMessage(ofxOscMessage m);

    protected:
        cursorMap cursors;
    private:
};

#endif // TUIOAPP_H
