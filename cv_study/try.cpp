/*#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int main(){
    auto img = imread("./IMG_2598.jpeg");
    imshow("fff",img);
    waitKey(0);
}*/

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

bool buttonPressed = false;

// 鼠标回调函数
void onMouse(int event, int x, int y, int flags, void* userdata) {
    cout << "Mouse event: " << event << " at (" << x << ", " << y << ")" << endl;
    if (event == EVENT_LBUTTONDOWN) {
        // 检测点击位置是否在按钮区域内
        if (x >= 50 && x <= 150 && y >= 50 && y <= 100) {
            cout << "Button clicked at (" << x << ", " << y << ")" << endl;
            buttonPressed = true;
        }
    }
}

int main() {
    // 创建一个空白图像
    Mat img(200, 300, CV_8UC3, Scalar(255, 255, 255));

    // 注册鼠标回调函数
    namedWindow("Button Example", WINDOW_AUTOSIZE);
    setMouseCallback("Button Example", onMouse);

    while (true) {
        // 绘制按钮
        img = Mat::zeros(200, 300, CV_8UC3); // 每次循环重新创建图像
        rectangle(img, Point(50, 50), Point(150, 100), Scalar(0, 255, 0), -1);
        putText(img, "Click Me", Point(60, 80), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 0, 0), 2);

        // 显示图像
        imshow("Button Example", img);

        // 检测按钮是否被点击
        if (buttonPressed) {
            cout << "Button was clicked!" << endl;
            buttonPressed = false; // 重置按钮状态
        }

        // 等待按键
        if (waitKey(10) == 27) { // 按下 ESC 键退出
            break;
        }
    }

    return 0;
}