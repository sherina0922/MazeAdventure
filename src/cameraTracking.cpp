//
//  cameraTracking.cpp
//  final-project-sherina0922-master
//
//  Created by Sherina Hung on 4/15/18.
//

#include "cameraTracking.hpp"

void CameraTracking::FindPoint(ofVideoGrabber camera) {
    int camera_width = camera.getWidth();
    int camera_height = camera.getHeight();
    
    float current_max_brightness = 0.0;
    brightest_pixel_x = 0;
    brightest_pixel_y = 0;
    
    //ofColor current_color;
    float checking_brightness = 0;
    
    //find coordinate location of brightest pixel
    for (int current_y = 0; current_y < camera_height; current_y++) {
        for (int current_x = 0; current_x < camera_width; current_x++) {
            
            checking_brightness = camera.getPixels().getColor(current_x, current_y).getBrightness(); //get brightness at current pixel
            
            if (checking_brightness > current_max_brightness) {
                current_max_brightness = checking_brightness;
                brightest_pixel_x = current_x;
                brightest_pixel_y = current_y;
            }
            /* //Make it track green... but doesnt work
             ofColor current_color = comp_camera.getPixels().getColor(current_posX, current_posY);
             float hue = current_color.getHue();
             float bright = current_color.getLightness();
             float saturation = current_color.getSaturation();
             checking_brightness = abs(hue - 90) + abs(bright - 49) + abs(saturation - 100);
             if (checking_brightness < current_max_brightness) {
             current_max_brightness = checking_brightness;
             brightest_pixel_x = current_x;
             brightest_pixel_y = current_y;
             }
             */
        }
    }
    camera.update();
}

void CameraTracking::DrawStylus(int width, int height) {
    //comp_camera.draw(0, 0, ofGetWidth(), ofGetWidth());
    
    //draws brightest point stylus, position needs to be rescaled to deal with easycam changes...
    ofPushMatrix();
    
    //ofTranslate(comp_camera.getWidth()/2,comp_camera.getHeight()/2,0); //centers the coordinates plane
    //ofTranslate(comp_camera.getWidth()/(2*view_camera.getDistance()), comp_camera.getHeight()/(2*view_camera.getDistance()), 0);
    
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR); //white
    ofNoFill();
    ofDrawCircle(-0.5 * (brightest_pixel_x - width / 2), -0.5 * (brightest_pixel_y - height / 2), 5);
    ofFill();
    ofDrawCircle(-0.5 * (brightest_pixel_x - width / 2), -0.5 * (brightest_pixel_y - height / 2), 2);
    ofPopMatrix();
    
    ofDrawBitmapString("the current pixel locations" + std::to_string(brightest_pixel_x) + ":" + std::to_string(brightest_pixel_y), 10, 30);
}
