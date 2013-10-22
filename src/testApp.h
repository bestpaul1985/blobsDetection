#pragma once

#include "ofMain.h"
#include "ofxMacamPs3Eye.h"
#include "ofxOpenCv.h"
#include "lines.h"
#include "blobs.h"
#include "ofxGui.h"
//#define _USE_LIVE_VIDEO

class testApp : public ofBaseApp{
    
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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void findAdjacentLines(vector<lines>* theLines);
    void lineFinder(vector<lines>* theLines, int i);
    
    
#ifdef PS3_EYE
    ofxMacamPs3Eye          ps3eye;
#else
    ofVideoGrabber          vidGraber;
#endif
    
    ofxCvColorImage             colorImg;
    ofxCvGrayscaleImage         grayImg;
    
    int                         w; 
    int                         h;
    char                        charValue;
    vector<lines>               myLine;
    vector<blobs>               myBlob;
    
    ofxPanel                    gui;
};
