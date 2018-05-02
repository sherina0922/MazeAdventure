//
//  cameraTracking.hpp
//  final-project-sherina0922-master
//
//  Created by Sherina Hung on 4/15/18.
//

#pragma once
#include "ofMain.h"
#include <stdio.h>

#include "constants.cpp"

class CameraTracking {

public:
    CameraTracking();
    
    int brightest_pixel_x; // X-coordinate of brightest pixel
    int brightest_pixel_y; // Y-coordinate of brightest pixel
    
    void FindPoint(ofVideoGrabber camera);              // Finds the location of the brightest pixel
    void DrawStylus(int width, int height);             // Draws a stylus around the brightest pixel
    void ConvertPixelLocation(int width, int height);   // Converts the pixel's location according to the screen dimensions
};

