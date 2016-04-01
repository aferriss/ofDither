#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    w = 960;
    h = 540;
    
    ofSetWindowShape(w, h);
    
    img.load("images/img.jpg");
    
    inShader.load("shaders/base.vert", "shaders/in.frag");
    outShader.load("shaders/base.vert", "shaders/out.frag");
    ditherShader.load("shaders/base.vert", "shaders/dither.frag");
    
    noisePix.allocate(w, h, OF_IMAGE_COLOR);
    
    inFbo.allocate(w, h, GL_RGB);
    outFbo.allocate(w, h, GL_RGB);
    dith1Fbo.allocate(w, h, GL_RGB);
    dith2Fbo.allocate(w, h, GL_RGB);
    
    for(int i =0; i<w*h; i++){
        int loc = i*3;
        
        noisePix[loc] = 0;
        noisePix[loc+1] = (int)ofRandom(255);
        noisePix[loc+2] = (int)ofRandom(255);
    }
    
    noiseImg.setFromPixels(noisePix);
    
    inShader.begin();
        inShader.setUniformTexture("noise", noiseImg.getTexture(), 1);
    inShader.end();
    
    texOffset = ofVec2f(1.0,1.0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    inFbo.begin();
        inShader.begin();
            inShader.setUniformTexture("tex0", img.getTexture(), 0);
            ofPushMatrix();
//            ofRotate(ofGetFrameNum()*0.05, 1, 0, 1);
            ofTranslate(0, 0, ofMap(ofGetMouseX(), 0, w, 0, 2));
            img.draw(0,0);
            ofPopMatrix();
        inShader.end();
    inFbo.end();
    
    for(int i = 0; i<18; i++){
        if(i == 0){
            dith1Fbo.begin();
                ditherShader.begin();
                    ditherShader.setUniformTexture("tex0", inFbo.getTexture(), 0);
                    ditherShader.setUniform2f("texOffset", texOffset.x, texOffset.y);
                    ditherShader.setUniform1f("px", i%3);
                    ditherShader.setUniform1f("py", (i/3)%3);
                        inFbo.draw(0,0);
                ditherShader.end();
            dith1Fbo.end();
        } else{
            dith1Fbo.begin();
                ditherShader.begin();
                    ditherShader.setUniformTexture("tex0", dith2Fbo.getTexture(), 0);
                    ditherShader.setUniform2f("texOffset", texOffset.x, texOffset.y);
                    ditherShader.setUniform1f("px", i%3);
                    ditherShader.setUniform1f("py", (i/3)%3);
                        dith2Fbo.draw(0,0);
                ditherShader.end();
            dith1Fbo.end();
        }
    
            dith2Fbo.begin();
                ditherShader.begin();
                    ditherShader.setUniformTexture("tex0", dith2Fbo.getTexture(), 0);
                    ditherShader.setUniform2f("texOffset", texOffset.x, texOffset.y);
                    ditherShader.setUniform1f("px", i%3);
                    ditherShader.setUniform1f("py", (i/3)%3);
                        dith1Fbo.draw(0,0);
                ditherShader.end();
            dith2Fbo.end();
    }
    
    outFbo.begin();
        outShader.begin();
            outShader.setUniformTexture("tex0", dith2Fbo.getTexture(), 0);
                dith2Fbo.draw(0,0);
        outShader.end();
    outFbo.end();
    
    
    
    
    
    outFbo.draw(0,0);
    
//    outFbo.readToPixels(pix);
//    img.setFromPixels(pix);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
