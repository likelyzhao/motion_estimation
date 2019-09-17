
#ifndef __a10__h
#define __a10__h

#include <cmath>
#include <iostream>

#include "common/matrix.h"
#include "common/Image.h"
#include "filtering.h"
#include <cstdlib>
#include <string>

using namespace std;

Image calcDiff(const Image &img1, const Image &img2);
Image createBlock(const Image &img1, int x, int y);
Image estMotion(const Image &img1, const Image &img2);
Image visVector(const Image &img1, Vec2f pos);

Vec2f  searchWindow(const Image &img1, const Image &img2, int x, int y);
float compareImage(const Image &img1, const Image &img2);

#endif
