//ofApp.cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    srand((unsigned)time(NULL));

    ofSetVerticalSync(true);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetCircleResolution(40);

    view_camera.setDistance(150); //150

    //If using camera input
    comp_camera.initGrabber(1280, 520);

    //Maze setup: Maze below derived from https://www.youtube.com/watch?v=9Ozu-B2HLY4
    unsigned char maze2[HEIGHT][WIDTH] = {
            {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
            {'#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
            {'#','#','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#','#','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#','#','#','#','#','#','#',' ','#',' ','#'},
            {'#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#'},
            {'#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#',' ','#','#','#',' ','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#'},
            {'#',' ','#','#','#','#','#','#','#','#','#',' ','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#','#','#','#','#',' ','#','#','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#'},
            {'#','#','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ','#'},
            {'#',' ','#','#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#'},
            {'#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#'},
            {'#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#','#','#','#','#',' ','#',' ','#','#','#',' ','#',' ','#'},
            {'#',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#'},
            {'#',' ','#','#','#',' ','#','#','#','#','#','#','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#'},
            {'#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#'},
            {'#',' ','#',' ','#','#','#',' ','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#','#','#',' ','#'},
            {'#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#'},
            {'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'}, //E was right before # symble
            {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},

    };

    for(int y=0 ; y< HEIGHT ; y++){
        for(int x=0 ; x< WIDTH ; x++){
            maze[x][y] = maze2[y][x];
        }
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    int camera_width = comp_camera.getWidth();
    int camera_height = comp_camera.getHeight();

    float current_max_brightness = 0.0;
    brightest_pixel_x = 0;
    brightest_pixel_y = 0;

    //ofColor current_color;
    float checking_brightness = 0;

    //find coordinate location of brightest pixel
    for (int current_y = 0; current_y < camera_height; current_y++) {
        for (int current_x = 0; current_x < camera_width; current_x++) {

            checking_brightness = comp_camera.getPixels().getColor(current_x, current_y).getBrightness(); //get brightness at current pixel

            if (checking_brightness > current_max_brightness) {
                current_max_brightness = checking_brightness;
                brightest_pixel_x = current_x;
                brightest_pixel_y = current_y;
            }
        }
    }

    comp_camera.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(ofColor::black);

    comp_camera.draw(0, 0, ofGetWidth(), ofGetWidth());
    view_camera.begin();

    //Draws the maze
    for (int current_y = 0; current_y < HEIGHT; current_y++) {
        for (int current_x = 0; current_x < WIDTH; current_x++) {
            /*
            if (maze[current_x][current_y] == ' ') {
                ofPushMatrix(); //save current coordinates axes
                ofSetColor(255, 255, 255);
                ofFill();
                ofDrawBox(4.0, 4.0, 4.0);
                ofNoFill();
                //ofSetColor(0);
                ofSetColor(0);
                ofDrawBox(4.0, 4.0, 4.0);
                ofPopMatrix();

            } else */if (maze[current_x][current_y] == '#') {
                ofPushMatrix();
                ofTranslate(current_x*5-100,-current_y*5+50,0);
                if (current_y ==0 && current_x==0) {
                    ofSetColor(255, 0, 0);
                } else {
                    ofSetColor(63.0,63.0,63.0);
                }
                ofFill();
                ofDrawBox(5.0, 5.0, 5.0);
                ofNoFill();
                ofSetColor(0);
                ofDrawBox(5.0, 5.0, 5.0);
                ofPopMatrix();
            }
        }
    }


    //draws brightest point stylus, position needs to be rescaled to deal with easycam changes...
    //ofPushMatrix();
    //ofTranslate(comp_camera.getWidth()/2,comp_camera.getHeight()/2,0); //centers the coordinates plane
    //ofTranslate(comp_camera.getWidth()/(2*view_camera.getDistance()), comp_camera.getHeight()/(2*view_camera.getDistance()), 0);
    ofSetColor(255, 255, 255); //white
    ofNoFill();
    ofDrawCircle(-(brightest_pixel_x - comp_camera.getWidth()/2), -(brightest_pixel_y - comp_camera.getHeight()/2), 5);
    ofFill();
    ofDrawCircle(-(brightest_pixel_x - comp_camera.getWidth()/2), -(brightest_pixel_y - comp_camera.getHeight()/2), 2);
    //ofPopMatrix();

    ofDrawBitmapString("the current pixel locations" + std::to_string(brightest_pixel_x) + ":" + std::to_string(brightest_pixel_y), 10, 20);
    view_camera.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    /*(switch (key) {
        case 'a':
            <#statements#>
            break;

        default:
            break;
    }*/
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
