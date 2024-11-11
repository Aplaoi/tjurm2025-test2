#include "impls.h"
#include <vector>
using namespace std;
using namespace cv;

std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    // IMPLEMENT YOUR CODE HERE
    Mat gray, dst;
    cvtColor(input, gray, COLOR_BGR2GRAY);
    threshold(gray, dst, 50, 255, THRESH_BINARY);
    vector<vector<Point>> contours;
    findContours(dst, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<Point> newContours;
    for (vector<Point> vec:contours){
        for (Point point:vec){
            newContours.push_back(point);
        }
    }
    Rect rect1 = boundingRect(newContours);
    RotatedRect rect2 = minAreaRect(newContours);
    res.first = rect1;
    res.second = rect2;
    return res;
}