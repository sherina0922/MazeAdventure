#include "../src/cameraTracking.hpp"

//--------------------------------------------------------------
CameraTracking::CameraTracking() {
    brightest_pixel_x = 0;
    brightest_pixel_y = 0;
}

//--------------------------------------------------------------
void CameraTracking::FindPoint(ofVideoGrabber camera) {
    int camera_width = camera.getWidth();
    int camera_height = camera.getHeight();
    
    float current_max_brightness = 0.0;
    brightest_pixel_x = 0;
    brightest_pixel_y = 0;
    float checking_brightness = 0;
    
    //find coordinate location of brightest pixel
    for (int current_y = 0; current_y < camera_height; current_y++) {
        for (int current_x = 0; current_x < camera_width; current_x++) {
            
            checking_brightness = camera.getPixels().getColor(current_x,
                                                              current_y).getBrightness(); //get brightness at current pixel
            
            if (checking_brightness > current_max_brightness) {
                current_max_brightness = checking_brightness;
                brightest_pixel_x = current_x;
                brightest_pixel_y = current_y;
            }
        }
    }
    camera.update();
}

//--------------------------------------------------------------
void CameraTracking::DrawStylus(int width, int height) {
    //draws brightest point stylus
    ofPushMatrix();
    CameraTracking::ConvertPixelLocation(width, height);
    
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR); //white
    ofNoFill();
    ofDrawCircle(brightest_pixel_x, brightest_pixel_y, 5);
    ofFill();
    ofDrawCircle(brightest_pixel_x, brightest_pixel_y, 2);
    ofPopMatrix();
    
    ofDrawBitmapString("the current pixel locations" + std::to_string(brightest_pixel_x) + ":" + std::to_string(brightest_pixel_y),
                       10, 30);
}

//--------------------------------------------------------------
void CameraTracking::ConvertPixelLocation(int width, int height) {
    brightest_pixel_x = -HALF * (brightest_pixel_x - width * HALF);
    brightest_pixel_y = -HALF * (brightest_pixel_y - height * HALF);
}
