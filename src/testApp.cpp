#include "testApp.h"

//-----------------------------------------------------------------------------------------------
void testApp::lineFinder(vector<lines>* theLines, int i){
    
    vector<int> num;
    
    for (int j= 0; j<(*theLines).size(); j++) {
        
        if ((*theLines)[j].z == -1) {
            
            if ((*theLines)[j].y == (*theLines)[i].y+1 || (*theLines)[j].y == (*theLines)[i].y-1){
                
                if ((*theLines)[j].x1>(*theLines)[i].x1 && (*theLines)[j].x1<(*theLines)[i].x2 && (*theLines)[j].x2>(*theLines)[i].x1 && (*theLines)[j].x2<(*theLines)[i].x2) {
                    (*theLines)[j].z = 0;
                    myBlob.back().line.push_back((*theLines)[j]);
                    num.push_back(j);
                }
                
                else if((*theLines)[j].x1 == (*theLines)[i].x1 && (*theLines)[j].x2 == (*theLines)[i].x2){
                    (*theLines)[j].z = 0;
                    myBlob.back().line.push_back((*theLines)[j]);
                    num.push_back(j);
                }
                else if((*theLines)[j].x1<(*theLines)[i].x1 && (*theLines)[j].x1<(*theLines)[i].x2 && (*theLines)[j].x2>(*theLines)[i].x1 && (*theLines)[j].x2>(*theLines)[i].x2){
                    (*theLines)[j].z = 0;
                    myBlob.back().line.push_back((*theLines)[j]);
                    num.push_back(j);
                }
                else if((*theLines)[j].x1<=(*theLines)[i].x1 && (*theLines)[j].x1<(*theLines)[i].x2 && (*theLines)[j].x2>=(*theLines)[i].x1 && (*theLines)[j].x2<=(*theLines)[i].x2){
                    (*theLines)[j].z = 0;
                    myBlob.back().line.push_back((*theLines)[j]);
                    
                    num.push_back(j);
                    
                }  
                else if((*theLines)[j].x1>=(*theLines)[i].x1 && (*theLines)[j].x1<=(*theLines)[i].x2 && (*theLines)[j].x2>(*theLines)[i].x1 && (*theLines)[j].x2>=(*theLines)[i].x2){
                    (*theLines)[j].z = 0;
                    myBlob.back().line.push_back((*theLines)[j]);
                    num.push_back(j);
                    
                }
                
            }
        }
    }
    
    
    for (int i=0; i<num.size(); i++) {
        lineFinder(theLines, num[i]);
    }
    
}

//---------------------------------------------------------------
void testApp::findAdjacentLines(vector<lines>* theLines){
    
    bool bLinesAreAdjacent = false;
    
    for (int i=0; i< (*theLines).size(); i++) {
        if ((*theLines)[i].z == -1) {
            
            blobs temp;
            myBlob.push_back(temp);
            (*theLines)[i].z = 0;
            myBlob.back().line.push_back((*theLines)[i]);
            
            lineFinder(theLines, i);
        }
    }
    
}

//--------------------------------------------------------------
void testApp::setup(){   
    
    ofSetFrameRate(60);
	ofSetVerticalSync(true);
    
    w = 320;
    h = 240;
    
#ifdef PS3_EYE
    ps3eye.listDevices();
	ps3eye.setDesiredFrameRate(60);
	ps3eye.initGrabber(w,h,true);
#else
    vidGraber.setVerbose(true);
    vidGraber.initGrabber(w,h);
#endif
    
    
    colorImg.allocate(w,h);
    grayImg.allocate(w, h);
    
    ofSetWindowShape(w*2, h*2);
}

//--------------------------------------------------------------
void testApp::update(){
    
    ofBackground(100,100,100);
    
#ifdef PS3_EYE
    ps3eye.update();
    if (ps3eye.isFrameNew()){
        colorImg.setFromPixels(ps3eye.getPixels(), w,h);
    }
#else
    vidGraber.update();
    if (vidGraber.isFrameNew()){
        colorImg.setFromPixels(vidGraber.getPixels(), w,h);
    }
#endif
    
    grayImg = colorImg;
    grayImg.blur();
    grayImg.threshold(200);
    
    //get pixcles
    unsigned char* grayPix = grayImg.getPixels();
    
    //get lines
    myLine.clear();
    myBlob.clear();
    
    for(int i=0; i< w*h; i++){
        if(grayPix[i] == 0){
            
            int x = i- (int)(i/w)*w;
            int y = (int)(i/w);
            
            lines temp;
            myLine.push_back(temp);
            myLine.back().x1 = x;
            myLine.back().y = y;
            myLine.back().z = -1;
            
            for (int j = x; j<=w; j++) {
                if (grayPix[w*y+j] == 0) {
                    grayPix[w*y+j] = 125;
                    myLine.back().x2 = j;
                }else{
                    break;
                }
            }
            
        }
    }
    
    
    if (myLine.size()>1) {
        findAdjacentLines(&myLine);
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255);
#ifdef PS3_EYE
    ps3eye.draw(0,0);
#else
    vidGraber.draw(0, 0);
#endif
    grayImg.draw(w, 0);
    
    for(int i=0; i<myBlob.size();i++){
        ofPushMatrix();
        ofTranslate(w, 0);
        myBlob[i].drawRect();
        ofPopMatrix();
    }
    
    cout<<"Blob Number: "<<myBlob.size()<<endl;
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}
