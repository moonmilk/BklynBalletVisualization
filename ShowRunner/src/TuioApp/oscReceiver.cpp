#include "oscReceiver.h"

oscReceiver::oscReceiver(TuioApp *i_parent,int p)
{
    port=p;
    receiver.setup(port);

    frame_stale=0;
    prevFrame=0;
    lastFrame=0;

    parent=i_parent;
}

oscReceiver::~oscReceiver()
{
    //dtor
}

void oscReceiver::processOsc(){
    while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		if (m.getAddress() == "/tuio/2Dcur" && m.getNumArgs()==7 && m.getArgType(0)==OFXOSC_TYPE_STRING && m.getArgAsString(0)=="set"){
			tuioCursor tc;

			tc.s = m.getArgAsInt32(1);
			tc.x = m.getArgAsFloat(2);
			tc.y = m.getArgAsFloat(3);
			tc.dx = m.getArgAsFloat(4);
			tc.dy = m.getArgAsFloat(5);
			tc.m = m.getArgAsFloat(6);
			tc.age = 0;

			cursors[tc.s] = tc;

		}

		else if (m.getAddress() == "/tuio/2Dcur" && m.getNumArgs()==2 && m.getArgType(0)==OFXOSC_TYPE_STRING && m.getArgAsString(0)=="fseq"){
			if(lastFrame != m.getArgAsInt32(1)){
                vector<map<int,tuioCursor>::iterator> stale_cursors;
                for(map<int,tuioCursor>::iterator cursor=cursors.begin();cursor!=cursors.end();++cursor){
                    tuioCursor *tc=&(cursor->second);
                    if (++tc->age > 5){
                        stale_cursors.push_back(cursor);
                    }
                }
                for(vector<map<int,tuioCursor>::iterator>::iterator stale = stale_cursors.begin();stale != stale_cursors.end();++stale){
                    cursors.erase(*stale);
                }
                parent->updateTuioPoints(cursors);
                lastFrame=m.getArgAsInt32(1);
			}

		} else if (m.getAddress() != "/tuio/2Dcur"){
            parent->handleOscMessage(m);
		}
	}
    if (prevFrame == lastFrame){
        frame_stale++;
        if (frame_stale >= 5){
            cursors.clear();
            parent->updateTuioPoints(cursors);
        }
    } else {
        frame_stale=0;
        prevFrame=lastFrame;
    }
}
