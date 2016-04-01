#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofShader inShader, outShader, ditherShader;
    ofFbo inFbo, outFbo, dith1Fbo, dith2Fbo;
    int w, h;
    ofImage img, noiseImg;
    ofPixels pix, noisePix;
    int bounce = 1;
    ofVec2f texOffset;
};
