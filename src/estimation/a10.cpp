
#include "a10.h"
using namespace std;

//returns the difference between two images
Image calcDiff(const Image &img1, const Image &img2) {
    Image input1 = img1;
    Image input2 = img2;

    int width = input1.width();
    int height = input1.height();
    int channels = input1.channels();

    Image result = Image(width, height, channels);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < channels; z++) {
                result(x,y,z) = input2(x,y,z) - input1(x,y,z);
            }
        }
    }

    return result;
}


//return 16x16 px block with top left corner at x, y
Image createBlock(const Image &img1, int x, int y) {
    int channels = img1.channels();
    Image result = Image(16,16, channels);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            for (int z = 0; z < channels; z++) {
                result(i,j,z) = img1.smartAccessor(x+i, y+j, z, true);
            }
        }
    }
    return result;
}


//compares block 1 with top left corner at x,y, with a 7px search window in img2 
//returns the displacement of the best matched pixel
Vec2f searchWindow(const Image &img1, const Image &img2, int x, int y) {
    Image block1 = createBlock(img1, x, y);
    Image block2 = createBlock(img2, x, y);

    int min = 10000;
    Vec2f pos(0,0);
    if (compareImage(block1, block2) < 0.1) {
        return pos;
    }

    for (int xx = -7; xx <= 7; xx++) {
        for (int yy = -7; yy <= 7; yy++) {
                block2 = createBlock(img2, x+xx, y+yy);       
                float diff = compareImage(block1, block2);
                if (diff < min) {
                    min = diff;
                    pos[0] = xx;
                    pos[1] = yy;
                    
                }
        }
    }
    return pos;
}


//return square difference betweeen pixels in img1 and img2
float compareImage(const Image &img1, const Image &img2) {
    int width = img2.width();
    int height = img2.height();
    int channels = img2.channels();

    float diff = 0.0;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < channels; z++) {    
                diff += pow((img2(x,y,z) - img1(x,y,z)), 2);
            }
        }
    }
    return diff;
}

//visualize a motion vector using Bresenham's line algorithm
Image visVector(const Image &img1, Vec2f pos){

    int x1 = 7;
    int y1 = 7;
    int x2 = (int) 7+pos[0];
    int y2 = (int) 7+pos[1];

    int dx0 = x2 - x1;
    int dy0 = y2 - y1;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int px = 2 * dy - dx;
    int py = 2 * dx - dy;

    int x = 0;
    int y = 0;
    int xe = 0;
    int ye = 0;

    Image result = Image(16,16, img1.channels());

    if (dy <= dx) {
        if (dx0 >= 0) {
           x = x1;
           y = y1;
           xe = x2;
        }
        else {
            x = x2;
            y = y2;
            xe = x1;
        }
        result(x,y, 1) = 1;

        for (int i = 0; x < xe; i++) {
            x += 1;
            if (px < 0) {
                px = px + 2* dy;
            }
            else {
                if ((dx0 < 0 && dy0) || (dx0 > 0 && dy0 > 0)) {
                    y += 1;
                }
                else {
                    y -= 1;
                }
                px = px+2*(dy-dx);
            }
            result(x,y, 1) = 1;
        }
    }
    else {
        if (dy >= 0) {
            x = x1;
            y = y1;
            ye = x2;
        }
        else {
            x = x2;
            y = y2;
            ye = y1;
        }
        result(x,y,1) = 1;

        for (int i = 0; y < ye; i++) {
           y += 1; 
           if (py <= 0) {
                py = py+2*dx;
           }
           else {
                if((dx0<0 && dy0<0) || (dx0>0 && dy0>0)) {
                    x += 1;
                }
                else {
                    x -= 1;
                }
                py = py + 2*(dx-dy);
           }
           result(x,y,1) = 1;
        }
    }

    return result;
}



//visualize the change in motion between two frames
Image estMotion(const Image &img1, const Image &img2) {
    int width = img1.width();
    int height = img1.height();

    Image result = img2;
    for (int x = 0; x < width; x+= 16) {
        for (int y = 0; y < height; y+= 16) {
            Vec2f pos = searchWindow(img1, img2, x, y);

            //Draw motion vectors
            if (abs(pos[0]) > 0.000 || abs(pos[1]) > 0.000) {

                int x1 = x+7;
                int y1 = y+7;
                int x2 = (int) x1+pos[0];
                int y2 = (int) y1+pos[1];

                int dx0 = x2 - x1;
                int dy0 = y2 - y1;

                int dx = abs(x2 - x1);
                int dy = abs(y2 - y1);

                int px = 2 * dy - dx;
                int py = 2 * dx - dy;

                int xx = 0;
                int yy = 0;
                int xe = 0;
                int ye = 0;

                //mark end point in red
                result(x2, y2, 0) = 1;

                if (dy <= dx) {
                    if (dx0 >= 0) {
                       xx = x1;
                       yy = y1;
                       xe = x2;
                    }
                    else {
                        xx = x2;
                        yy = y2;
                        xe = x1;
                    }
                    if (xx >= 0 && xx < width && yy >= 0 && yy < height) {
                        result(xx,yy,2) = 1;
                    }
  
                    for (int i = 0; xx < xe; i++) {
                        xx += 1;
                        if (px < 0) {
                            px = px + 2* dy;
                        }
                        else {
                            if ((dx0 < 0 && dy0) || (dx0 > 0 && dy0 > 0)) {
                                yy += 1;
                            }
                            else {
                                yy -= 1;
                            }
                            px = px+2*(dy-dx);
                        }
                        if (xx >= 0 && xx < width && yy >= 0 && yy < height){
                            result(xx,yy,2) = 1;
                        }
                    }
                }
                
                else {
                    if (dy0 >= 0) {
                        xx = x1;
                        yy = y1;
                        ye = y2;
                    }
                    else {
                        xx = x2;
                        yy = y2;
                        ye = y1;
                    }
                    if (xx >= 0 && xx < width && yy >= 0 && yy < height){
                        result(xx,yy,2) = 1;
                    }
                    for (int i = 0; yy < ye; i++) {
                       yy += 1; 
                       if (py <= 0) {
                            py = py+2*dx;
                       }
                       else {
                            if((dx0<0 && dy0<0) || (dx0>0 && dy0>0)) {
                                xx += 1;
                            }
                            else {
                                xx -= 1;
                            }
                            py = py + 2*(dx-dy);
                       }
                      if (xx >= 0 && xx < width && yy >= 0 && yy < height){
                        result(xx,yy,2) = 1;
                      }
                    }
                }
            }
            //END draw vectors 
            
        }
    }

    return result;
}


