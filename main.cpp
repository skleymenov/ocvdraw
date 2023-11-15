#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using std::cout;
using std::endl;

int main(int argc, char** argv) {
    const int img_size_x = 4096;
    const int img_size_y = 4096;
    cv::Scalar background(10,10,10);
    cv::Scalar lcolour(10,255,50);
    const int lthick = 5;

    cv::Mat img(img_size_x, img_size_y, CV_8UC3 ,background);

    //cv::line(img, cv::Point(0, img_size_y/2), cv::Point(img_size_x, img_size_y/2), lcolour, lthick);
    //cv::line(img, cv::Point(img_size_x/2, img_size_y/4), cv::Point(img_size_x/2, img_size_y*3/4), lcolour, lthick);
    
    double sq_size = img_size_x/2.0;
    double angle = asin(1/sqrt(5)) * 180 / M_PI;
    cv::Point2f center(img_size_x/2.0, img_size_y/2.0);

    for (int i = 0; i < 1000; i++) {
        cv::Size2f size(sq_size, sq_size);
        cv::RotatedRect rect(center, size, angle*i);

        // Get the four vertices of the rotated rectangle
        cv::Point2f vertices[4];
        rect.points(vertices);

        // Draw the rotated rectangle 
        for (int j = 0; j < 4; ++j) {
            cv::line(img, vertices[j], vertices[(j + 1) % 4], lcolour, lthick);
        }

        sq_size *= (sqrt(5) / 3.0);
    }


    cv::namedWindow("ocvdraw", cv::WINDOW_AUTOSIZE);
    cv::imshow("ocvdraw", img);
    
    cv::waitKey(0);
    cv::destroyAllWindows();

    cv::imwrite("out.png", img);

    return 0;
}