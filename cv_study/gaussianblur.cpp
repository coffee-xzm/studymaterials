#include <opencv4/opencv2/opencv.hpp>
void ex2_5(const cv::Mat&image){
    cv::namedWindow("ex-in",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("ex-out",cv::WINDOW_AUTOSIZE);
    cv::imshow("ex-in",image);
    cv::Mat out;
    cv::GaussianBlur(image,out,cv::Size(5,5),3,3);
    cv::GaussianBlur(out,out,cv::Size(5,5),3,3);
    cv::imshow("ex-out",out);
    cv::waitKey(0);
}