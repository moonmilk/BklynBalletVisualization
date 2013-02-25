#ifndef _FLUIDVISUALIZATION_H
#define _FLUIDVISUALIZATION_H

#define MSA_HOST_OPENFRAMEWORKS
#include "MSAFluid.h"
//#include "MSATimer.h"
#include "ParticleSystem.h"
#include "ofMain.h"
#include "map"
#include "TuioApp.h"

class FluidVisualization : public TuioApp {
public:
	void setup();
	void reset();
	void update();
	void draw();

	void keyPressed  (int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);

	void fadeToColor(float r, float g, float b, float speed);
	void addToFluid(ofVec2f pos, ofVec2f vel, bool addColor, bool addForce);
	void gotMessage(ofMessage msg);

    float                   colorMult;
    float                   velocityMult;
	int                     fluidCellsX;
	bool                    resizeFluid;
	bool                    drawFluid;
	bool                    drawParticles;

	msa::fluid::Solver      fluidSolver;
	msa::fluid::DrawerGl	fluidDrawer;

	ParticleSystem          particleSystem;

	ofVec2f                 pMouse;
};

#endif //_FLUIDVISUALIZATION_H

