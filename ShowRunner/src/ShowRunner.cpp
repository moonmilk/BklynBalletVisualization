#include "ShowRunner.h"
//--------------------------------------------------------------
void ShowRunner::setup(){
    ofBackground(0, 0, 0);
    ofHideCursor();
    ofSetFullscreen(true);
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    ofEnableSmoothing();

    TuioApp *fluid = new FluidVisualization();
    TuioApp *cross = new CrossVisualization();
    TuioApp *delaunay = new DelaunayVisualization();
    TuioApp *particle = new ParticleVisualization();

    Visuals.push_back(fluid);
    Visuals.push_back(cross);
    Visuals.push_back(delaunay);
    Visuals.push_back(particle);

    visualIndex=0;
    Visuals[0]->setup();
    Visuals[1]->setup();
    Visuals[2]->setup();
    Visuals[3]->setup();
    reset();
}

void ShowRunner::reset(){
    curtainAlpha=0;
    curtainX=0;
    curtainY=0;
    cursors.clear();
    tuioInhibit=false;
    tuioInvertX=false;
    tuioInvertY=false;
    tuioXScale=1.0;
    tuioYScale=1.0;
    tuioXPos=0.0;
    tuioYPos=0.0;

    for (visIterator vis=Visuals.begin();vis!=Visuals.end();++vis){
        TuioApp *visualPtr=*vis;
        visualPtr->reset();
    }
}

//--------------------------------------------------------------
void ShowRunner::update(){
    receiver.processOsc();
    Visuals[visualIndex]->update();
}

//--------------------------------------------------------------
void ShowRunner::draw(){
    Visuals[visualIndex]->draw();
    ofPushStyle();
    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(0,0,0,curtainAlpha);
    ofRect(curtainX,curtainY,ofGetViewportWidth(),ofGetViewportHeight());
    ofPopStyle();
}

void ShowRunner::updateTuioPoints(cursorMap input_tuioCursors){
    cursors.clear();
    for(cursorMap::iterator cursor=input_tuioCursors.begin();cursor!=input_tuioCursors.end();++cursor){
        int idx=cursor->first;
        tuioCursor tc=cursor->second;
        if(!tuioInhibit){
            if (tuioInvertY){
                tc.y=1.0-tc.y;
            }
            if (tuioInvertX){
                tc.x=1.0-tc.x;
            }
            tc.y=(tc.y*tuioYScale)+tuioYPos;
            tc.x=(tc.x*tuioXScale)+tuioXPos;
            //tc.dx=tc.dx*tuioXScale;
            //tc.dy=tc.dy*tuioYScale;
            cursors[idx]=tc;
        }
    }
    Visuals[visualIndex]->updateTuioPoints(cursors);
}

void ShowRunner::handleOscMessage(ofxOscMessage m){
    const string tuioDispatch = "/showrunner/tuio/";
    const string curtainDispatch = "/showrunner/curtain/";
    const string fluidDispatch = "/showrunner/fluid/";
    const string crossDispatch = "/showrunner/cross/";
    const string delaunayDispatch = "/showrunner/delaunay/";
    const string particleDispatch = "/showrunner/particle/";

    const string visual = "/showrunner/visual";

    string address = m.getAddress();

    if (address.compare(0,tuioDispatch.size(),tuioDispatch)==0){
        oscTuioDispatch(m);
    }else if (address.compare(0,curtainDispatch.size(),curtainDispatch)==0){
        oscCurtainDispatch(m);
    }else if (address.compare(0,fluidDispatch.size(),fluidDispatch)==0){
        Visuals[0]->handleOscMessage(m);
    }else if (address.compare(0,crossDispatch.size(),crossDispatch)==0){
        Visuals[1]->handleOscMessage(m);
    }else if (address.compare(0,delaunayDispatch.size(),delaunayDispatch)==0){
        Visuals[2]->handleOscMessage(m);
    }else if (address.compare(0,particleDispatch.size(),particleDispatch)==0){
        Visuals[3]->handleOscMessage(m);
    }else if (address == visual){
        int index=m.getArgAsFloat(0);
        if (index >= 0 && index < static_cast<int>(Visuals.size())){
            visualIndex=index;
            Visuals[visualIndex]->reset();
            ofEnableAlphaBlending();
            ofEnableSmoothing();
        }
    }

}

void ShowRunner::oscTuioDispatch(ofxOscMessage m){
    string address = m.getAddress();
    string yscale = "/showrunner/tuio/yscale";
    string pos ="/showrunner/tuio/pos";
    string yinv ="/showrunner/tuio/yinvert";
    string xscale ="/showrunner/tuio/xscale";
    string xinv ="/showrunner/tuio/xinvert";
    string inhibit ="/showrunner/tuio/inhibit";


    if(address == yscale){
        tuioYScale=m.getArgAsFloat(0);
    }else if(address == xscale){
        tuioXScale=m.getArgAsFloat(0);
    }else if(address == pos){
        tuioXPos=m.getArgAsFloat(0);
        tuioYPos=m.getArgAsFloat(1);
    }else if(address == xinv){
        tuioInvertX= (m.getArgAsFloat(0) == 1.0);
    }else if(address == yinv){
        tuioInvertY= (m.getArgAsFloat(0) == 1.0);
    }else if(address == inhibit){
        tuioInhibit= (m.getArgAsFloat(0) == 1.0);
    }
}
void ShowRunner::oscCurtainDispatch(ofxOscMessage m){
    string address = m.getAddress();
    const string alpha = "/showrunner/curtain/alpha";
    const string xpos = "/showrunner/curtain/xpos";
    const string ypos = "/showrunner/curtain/ypos";

    if (address == alpha){
        curtainAlpha = m.getArgAsFloat(0) * 255;
    }else if (address == ypos){
        curtainY= m.getArgAsFloat(0) * (-ofGetViewportHeight());
    }
}


//--------------------------------------------------------------
void ShowRunner::keyPressed(int key){
    switch (key){
        case '+':
            visualIndex=(visualIndex+1)% static_cast<int>(Visuals.size());
            ofEnableAlphaBlending();
            ofEnableSmoothing();
            break;
        case '-':
            visualIndex=(visualIndex-1);
            if (visualIndex < 0){
                visualIndex=static_cast<int>(Visuals.size())-1;
            }
            ofEnableAlphaBlending();
            ofEnableSmoothing();
            break;
        case '>':
            curtainAlpha=curtainAlpha+1;
            if(curtainAlpha > 255)
                curtainAlpha=255;
            break;
        case '<':
            curtainAlpha=curtainAlpha-1;
            if(curtainAlpha < 0)
                curtainAlpha=0;
            break;
        case 'a':
            curtainY=curtainY-10;
            if(curtainY < -(ofGetViewportHeight()))
                curtainY=-(ofGetViewportHeight());
            break;
        case 'z':
            curtainY=curtainY+10;
            if(curtainY > 0)
                curtainY=0;
            break;
        case '*':
            Visuals[visualIndex]->reset();
            break;
        case '[':
            tuioYScale=tuioYScale-0.01;
            if (tuioYScale<0){
                tuioYScale=0;
            }
            tuioYPos=1-tuioYScale;
            break;
        case ']':
            tuioYScale=tuioYScale+0.01;
            if (tuioYScale>1){
                tuioYScale=1;
            }
            tuioYPos=1-tuioYScale;
            break;

        default:
            Visuals[visualIndex]->keyPressed(key);
        }
}

//--------------------------------------------------------------
void ShowRunner::keyReleased(int key){
    Visuals[visualIndex]->keyReleased(key);
}

//--------------------------------------------------------------
void ShowRunner::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ShowRunner::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ShowRunner::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ShowRunner::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ShowRunner::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ShowRunner::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ShowRunner::dragEvent(ofDragInfo dragInfo){

}
