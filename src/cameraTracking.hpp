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

static int brightest_pixel_x; //X-coordinate of brightest pixel
static int brightest_pixel_y; //Y-coordinate of brightest pixel

class CameraTracking {
public:
    
    static void FindPoint(ofVideoGrabber camera);
    static void DrawStylus(int width, int height);
};

