#include "FluidVisualization.h"


//--------------------------------------------------------------
void FluidVisualization::setup() {
	// setup fluid stuff
	fluidSolver.setup(100, 100);
    fluidSolver.enableRGB(true).setFadeSpeed(0.002).setDeltaT(0.5).setVisc(0.000015).setColorDiffusion(0.00001);
	fluidDrawer.setup(&fluidSolver);

	fluidCellsX			= 150;

	drawFluid			= true;
	drawParticles		= false;
    colorMult           = 1.0;
    velocityMult        = 10.0;
	ofSetVerticalSync(false);


#ifdef USE_GUI
	gui.addSlider("fluidCellsX", fluidCellsX, 20, 400);
	gui.addButton("resizeFluid", resizeFluid);
    gui.addSlider("colorMult", colorMult, 0, 100);
    gui.addSlider("velocityMult", velocityMult, 0, 100);
	gui.addSlider("fs.viscocity", fluidSolver.viscocity, 0.0, 0.01);
	gui.addSlider("fs.colorDiffusion", fluidSolver.colorDiffusion, 0.0, 0.0003);
	gui.addSlider("fs.fadeSpeed", fluidSolver.fadeSpeed, 0.0, 0.1);
	gui.addSlider("fs.solverIterations", fluidSolver.solverIterations, 1, 50);
	gui.addSlider("fs.deltaT", fluidSolver.deltaT, 0.1, 5);
	gui.addComboBox("fd.drawMode", (int&)fluidDrawer.drawMode, msa::fluid::getDrawModeTitles());
	gui.addToggle("fs.doRGB", fluidSolver.doRGB);
	gui.addToggle("fs.doVorticityConfinement", fluidSolver.doVorticityConfinement);
	gui.addToggle("drawFluid", drawFluid);
	gui.addToggle("drawParticles", drawParticles);
	gui.addToggle("fs.wrapX", fluidSolver.wrap_x);
	gui.addToggle("fs.wrapY", fluidSolver.wrap_y);
	gui.currentPage().setXMLName("ofxMSAFluidSettings.xml");
    gui.loadFromXML();
	gui.setDefaultKeys(true);
	gui.setAutoSave(true);
    gui.show();
#endif

	windowResized(ofGetWidth(), ofGetHeight());		// force this at start (cos I don't think it is called)
	pMouse = msa::getWindowCenter();
	resizeFluid			= true;

	ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);
}

void FluidVisualization::reset(){
    fluidSolver.reset();
    colorH = 0;
    colorS = 0;
    colorB = 128;
    force = true;
    ink = true;
    flame = false;
}

void FluidVisualization::fadeToColor(float r, float g, float b, float speed) {
    glColor4f(r, g, b, speed);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
}


// add force and dye to fluid, and create particles
void FluidVisualization::addToFluid(ofVec2f pos, ofVec2f vel, bool addColor, bool addForce) {
    float speed = vel.x * vel.x  + vel.y * vel.y * msa::getWindowAspectRatio() * msa::getWindowAspectRatio();    // balance the x and y components of speed with the screen aspect ratio
    if(speed > 0) {
		pos.x = ofClamp(pos.x, 0.0f, 1.0f);
		pos.y = ofClamp(pos.y, 0.0f, 1.0f);

        int index = fluidSolver.getIndexForPos(pos);

		if(addColor) {
//			Color drawColor(CM_HSV, (getElapsedFrames() % 360) / 360.0f, 1, 1);
			ofColor drawColor;
			//drawColor.setHsb((ofGetFrameNum() % 255), 255, 255);
			drawColor.setHsb(colorH, colorS, colorB);

			fluidSolver.addColorAtIndex(index, drawColor * colorMult);

			if(drawParticles)
				particleSystem.addParticles(pos * ofVec2f(ofGetWindowSize()), 10);
		}

		if(addForce)
			fluidSolver.addForceAtIndex(index, vel * velocityMult);

    }
}


void FluidVisualization::update(){
	if(resizeFluid) 	{
		fluidSolver.setSize(fluidCellsX, fluidCellsX / msa::getWindowAspectRatio());
		fluidDrawer.setup(&fluidSolver);
		resizeFluid = false;
	}
    for (cursorMap::iterator i = cursors.begin(); i != cursors.end(); ++i) {
        tuioCursor tc = (i->second);

        ofVec2f Pos=ofVec2f(tc.x,tc.y);
        ofVec2f Vel=ofVec2f(tc.dx,tc.dy)*0.05;

        addToFluid(Pos, Vel,ink,force);
    }
    if(flame){
        ofVec2f Pos = ofVec2f(0.5, 1);
        ofVec2f Vel = ofVec2f(ofRandom(-0.005,0.005),-0.01);
        addToFluid(Pos, Vel, true, true);
    }
    /*Pos = ofVec2f(0.25, 1);
	Vel = ofVec2f(ofRandom(-0.005,0.005)-0.005,-0.1);
	addToFluid(Pos, Vel, true, true);
    Pos = ofVec2f(0.75, 1);
	Vel = ofVec2f(ofRandom(-0.005,0.005)+0.005,-0.1);
	addToFluid(Pos, Vel, true, true);*/
	fluidSolver.update();
}

void FluidVisualization::draw(){
    ofClear(0);
	if(drawFluid) {
		glColor3f(1, 1, 1);
		fluidDrawer.draw(0, 0, ofGetWidth(), ofGetHeight());
	} else {
//		if(ofGetFrameNum()%5==0)
            fadeToColor(0, 0, 0, 0.01);
	}
	if(drawParticles)
		particleSystem.updateAndDraw(fluidSolver, ofGetWindowSize(), drawFluid);

}


void FluidVisualization::keyPressed  (int key){
    switch(key) {
		case '1':
			fluidDrawer.setDrawMode(msa::fluid::kDrawColor);
			break;

		case '2':
			fluidDrawer.setDrawMode(msa::fluid::kDrawMotion);
			break;

		case '3':
			fluidDrawer.setDrawMode(msa::fluid::kDrawSpeed);
			break;

		case '4':
			fluidDrawer.setDrawMode(msa::fluid::kDrawVectors);
			break;

		case 'd':
			drawFluid ^= true;
			break;

		case 'p':
			drawParticles ^= true;
			break;

		case 'f':
			ofToggleFullscreen();
			break;

		case 'r':
			fluidSolver.reset();
			break;

		case 'b': {
//			Timer timer;
//			const int ITERS = 3000;
//			timer.start();
//			for(int i = 0; i < ITERS; ++i) fluidSolver.update();
//			timer.stop();
//			cout << ITERS << " iterations took " << timer.getSeconds() << " seconds." << std::endl;
		}
			break;

    }
}

void FluidVisualization::handleOscMessage(ofxOscMessage m){
    string address = m.getAddress();
    const string fluidColorHS = "/showrunner/fluid/colorhs";
    const string fluidColorB = "/showrunner/fluid/colorb";
    const string fluidInk = "/showrunner/fluid/ink";
    const string fluidFlame = "/showrunner/fluid/flame";
    const string fluidForce = "/showrunner/fluid/force";
    const string fluidReset = "/showrunner/fluid/reset";

    if(address == fluidFlame){
        flame=(m.getArgAsFloat(0) == 1);
    }else if(address == fluidInk){
        ink=(m.getArgAsFloat(0) == 1);
    }else if(address == fluidForce){
        force=(m.getArgAsFloat(0) == 1);
    }else if(address == fluidReset){
        if (m.getArgAsFloat(0) == 1){
            fluidSolver.reset();
        }
    }else if(address == fluidColorHS){
        colorH=m.getArgAsFloat(0)*255;
        colorS=m.getArgAsFloat(1)*255;
    }else if(address == fluidColorB){
        colorB= m.getArgAsFloat(0)*255;
    }
}
//--------------------------------------------------------------
void FluidVisualization::mouseMoved(int x, int y){
	//ofVec2f eventPos = ofVec2f(x, y);
	//ofVec2f mouseNorm = ofVec2f(eventPos) / ofGetWindowSize();
	//ofVec2f mouseVel = ofVec2f(eventPos - pMouse) / ofGetWindowSize();
	//addToFluid(mouseNorm, mouseVel, true, true);
	//pMouse = eventPos;
}

void FluidVisualization::mouseDragged(int x, int y, int button) {
	//ofVec2f eventPos = ofVec2f(x, y);
	//ofVec2f mouseNorm = ofVec2f(eventPos) / ofGetWindowSize();
	//ofVec2f mouseVel = ofVec2f(eventPos - pMouse) / ofGetWindowSize();
	//addToFluid(mouseNorm, mouseVel, false, true);
	//pMouse = eventPos;
}

void FluidVisualization::gotMessage(ofMessage msg){

}
