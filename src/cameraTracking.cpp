#include "../src/cameraTracking.hpp"

/**
 * Constructor for CameraTracking. Sets the current brightest pixel locations to 0
 */
CameraTracking::CameraTracking() {
    brightest_pixel_x = 0;
    brightest_pixel_y = 0;
}

/**
 * Determines the brightest pixel's location captured in the camera frame
 *
 * @param camera - the OfVideoGrabber camera that accesses the computer's camera
 */
void CameraTracking::FindPoint(ofVideoGrabber camera) {
    int camera_width = camera.getWidth();
    int camera_height = camera.getHeight();
    
    float current_max_brightness = 0.0;
    brightest_pixel_x = 0;
    brightest_pixel_y = 0;
    float checking_brightness = 0;
    
    // find coordinate location of brightest pixel
    for (int current_y = 0; current_y < camera_height; current_y++) {
        for (int current_x = 0; current_x < camera_width; current_x++) {
            
            checking_brightness = camera.getPixels().getColor(current_x, current_y).getBrightness(); //get brightness at current pixel
            if (checking_brightness > current_max_brightness) {
                current_max_brightness = checking_brightness;
                brightest_pixel_x = current_x;
                brightest_pixel_y = current_y;
            }
        }
    }
    camera.update();
}

/**
 * Draws a stylus (circle indicator) around the brightest pixel point
 *
 * @param width - the width of the screen
 * @param height - the height of the screen
 */
void CameraTracking::DrawStylus(int width, int height) {
    // draws brightest point stylus
    ofPushMatrix();
    CameraTracking::ConvertPixelLocation(width, height);
    
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR); //white
    ofNoFill();
    ofDrawCircle(brightest_pixel_x, brightest_pixel_y, CAMERA_STYLUS_OUTER);
    ofFill();
    ofDrawCircle(brightest_pixel_x, brightest_pixel_y, CAMERA_STYLUS_INNER);
    ofPopMatrix();
    
    ofDrawBitmapString("USING CAMERA INPUT\nthe current pixel location " + std::to_string(brightest_pixel_x) + ":" + std::to_string(brightest_pixel_y),
                       0, CAMERA_MODE_SIGN_Y);
}

/**
 * Converts the current brightest pixel's location according to screen dimensions
 *
 * @param width - the width of the screen
 * @param height - the height of the screen
 */
void CameraTracking::ConvertPixelLocation(int width, int height) {
    brightest_pixel_x = -HALF * (brightest_pixel_x - width * HALF);
    brightest_pixel_y = -HALF * (brightest_pixel_y - height * HALF);
}

