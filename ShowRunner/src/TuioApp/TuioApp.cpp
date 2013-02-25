#include "TuioApp.h"

TuioApp::TuioApp()
{
    //ctor
}

TuioApp::~TuioApp()
{
    //dtor
}
void TuioApp::reset(){
    return;
}
void TuioApp::updateTuioPoints(cursorMap input_tuioCursors){
    cursors.clear();
    for(cursorMap::iterator cursor=input_tuioCursors.begin();cursor!=input_tuioCursors.end();++cursor){
        int idx=cursor->first;
        tuioCursor tc=cursor->second;
        cursors[idx]=tc;
    }
}
void TuioApp::handleOscMessage(ofxOscMessage m){
        //should implement OscHandler here
}

