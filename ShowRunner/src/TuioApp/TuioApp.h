#ifndef TUIOAPP_H
#define TUIOAPP_H

#include <ofMain.h>
#include "tuioCursor.h"
#include <algorithm>

class TuioApp : public ofBaseApp
{
    public:
        TuioApp();
        virtual ~TuioApp();
        typedef map<int,tuioCursor> cursorMap;


        virtual void updateTuioPoints(cursorMap input_tuioCursors);
    protected:
        cursorMap cursors;
    private:
};

#endif // TUIOAPP_H
