//
//  cameraTracking.hpp
//  final-project-sherina0922-master
//
//  Created by Sherina Hung on 4/15/18.
//

#pragma once
#include "ofMain.h"
#include <stdio.h>
#define FULL_COLOR 255

class CameraTracking {

public:
    CameraTracking();
    int brightest_pixel_x; //X-coordinate of brightest pixel
    int brightest_pixel_y; //Y-coordinate of brightest pixel
    void FindPoint(ofVideoGrabber camera); 
    void DrawStylus(int width, int height);
    void ConvertPixelLocation(int width, int height);
};

