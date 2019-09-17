#include "estimation/a10.h"
#include <iostream>

using namespace std;


void testConstDiff() {
    Image img1 = Image("Input/Dalmations/frame_1.png");
    Image img2 = Image("Input/Dalmations/frame_2.png");
    Image result = calcDiff(img1, img2);
    result.write("./Output/diff.png");
    return;
}

void testCompareImage() {
    Image img1 = Image("Input/Dalmations/frame_1.png");
    Image img2 = Image("Input/Dalmations/frame_2.png");

    float diff = compareImage(img1, img2);
    cout << "Difference between images: " << diff << endl;
    return;
}

void testCreateBlock() {
    Image img1 = Image("Input/Dalmations/frame_1.png");
    Image result = createBlock(img1, 50, 50);
    result.write("./Output/block.png");
    cout << "16 x 16 px block created" << endl;
    return;
}

void testSearchWindow() {
    Image img1 = Image("Input/Dalmations/frame_1.png");
    Image img2 = Image("Input/Dalmations/frame_2.png");

    Vec2f pos = searchWindow(img1, img2, 100, 100);
    Image block1 = createBlock(img1, 100, 100);
    Image block2 = createBlock(img2, pos[0] + 100, pos[1] + 100);

    block1.write("./Output/block1.png");
    block2.write("./Output/block2.png");
    float diff = compareImage(block1, block2);
    cout << "Difference between blocks: " << diff << endl;
}

void testEstMotion() {

    for (int i = 1; i < 10; i++) {
        
        //string s1 = "Input/Dalmations/frame_";
        //string s2 = "Input/Dalmations/frame_";
        string s1 = "Input/DespicableMe/frame_";
        string s2 = "Input/DespicableMe/frame_";

        s1.append(to_string(i));
        s2.append(to_string(i+1));
        s1.append(".png");
        s2.append(".png");

        Image img1 = Image(s1);
        Image img2 = Image(s2);

        Image result = estMotion(img1, img2);
        string res = "./Output/motionestimation_";
        res.append(to_string(i));
        res.append(".png");
        result.write(res);
        cout << "Output: " << res << endl;
    }

    cout << "Image rendered" << endl;
}

void testVisVector() {
    Image img1 = Image("Input/Dalmations/frame_1.png");
    Vec2f pos;
    pos[0] = -7.0f;
    pos[1] = -7.0f;
    Image result = visVector(img1, pos);
    result.write("./Output/testVisualization.png");
    cout << "vector field rendered" << endl;
}

int main() {
    //testConstDiff();
    //testCompareImage();
    //testCreateBlock();
    //testSearchWindow();
    testEstMotion();
    //testVisVector();

    return 0;
}
