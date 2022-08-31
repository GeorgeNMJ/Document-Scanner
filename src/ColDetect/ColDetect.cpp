#include "ColDetect.h"
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

void ColDetect::cdetect(const std::string path) {
  cv::Mat img = cv::imread(path);
  cv::Mat imgHSV, mask;
  int hmin = 0, smin = 0, vmin = 105;
  int hmax = 360, smax = 114, vmax = 255;

  cv::namedWindow("Trackbars", (640, 200));
  cv::createTrackbar("Hue Min", "Trackbars", &hmin, 360);
  cv::createTrackbar("Hue Max", "Trackbars", &hmax, 360);
  cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
  cv::createTrackbar("Sat Max", "Trackbars", &smax, 255);
  cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
  cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);

  while (true) {
    cv::Scalar lower(hmin, smin, vmin);
    cv::Scalar upper(hmax, smax, vmax);

    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
    cv::inRange(img, lower, upper, mask);

    // cv::imshow("Image HSV", imgHSV);
    cv::imshow("Trackbars", mask);
    if (cv::waitKey(1) == 113) {
      cv::destroyAllWindows();
      break;
    }
  }
}
