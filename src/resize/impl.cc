#include "impls.h"
using namespace std;
using namespace cv;
#include <cmath>

cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    int new_rows = input.rows * scale, new_cols = input.cols * scale;
    // IMPLEMENT YOUR CODE HERE
    Mat out = Mat(new_rows, new_cols, CV_8UC3);
    int channel = input.channels();

    for (int y = 0; y < new_rows; y++)
    {
        for (int x = 0; x < new_cols; x++)
        {
            for (int c = 0; c < channel;c++){
                float srcX = x / scale;
                float srcY = y / scale;
                int srcX0 = static_cast<int>(srcX);
                int srcY0 = static_cast<int>(srcY);
                int srcX1 = min(srcX0 + 1, input.cols - 1);
                int srcY1 = min(srcY0 + 1, input.rows - 1);

                float dx = srcX - srcX0;
                float dy = srcY - srcY0;

                float value00 = input.at<Vec3b>(srcY0,srcX0)[c];
                float value01 = input.at<Vec3b>(srcY1,srcX0)[c];
                float value10 = input.at<Vec3b>(srcY0,srcX1)[c];
                float value11 = input.at<Vec3b>(srcY1,srcX1)[c];

                float newValue = (1 - dx) * (1 - dy) * value00 +
                                    dx * (1 - dy) * value10 +
                                    (1 - dx) * dy * value01 +
                                    dx * dy * value11;
                out.at<Vec3b>(y, x)[c] = newValue;
            }
                
            
        }
    }

    return out;
}