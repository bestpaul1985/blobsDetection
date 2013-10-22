//
//  blobs.cpp
//  goodluck
//
//  Created by PengCheng on 10/21/13.
//
//

#include "blobs.h"


void blobs::drawRect(){

    int x = line[0].x1;
    int x2 = line[0].x2;
    int y = line[0].y;
    int y2 = line[0].y;
    
    for (int i=0; i<line.size(); i++) {
        
        if(line[i].x1 < x){
           x = line[i].x1;
        } 
        
        if (line[i].x2 > x2) {
            x2 = line[i].x2;
        }
        
        
        if (line[i].y < y) {
            y = line[i].y;
        }
        
        if (line[i].y > y2) {
            y2 = line[i].y;
        }
        
    }
    
    int w = x2-x;
    int h = y2-y;
    
    ofSetColor(255,0,0,150);
    ofNoFill();
    ofRect(x, y, w, h);
        
}

