#include "ShapeDetect.h"
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

void ShapeDetect::shdetect(std::string path) {
  cv::Mat img = cv::imread(path);
  cv::Mat imgGray, imgBlur, imgCanny, imgDil;
  cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
  cv::GaussianBlur(imgGray, imgBlur, cv::Size(7, 7), 5);
  cv::Canny(imgBlur, imgCanny, 25, 75);
  cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
  cv::dilate(imgCanny, imgDil, kernel);

  getContours(imgDil, img);

  cv::imshow("Image", img);

  while (cv::waitKey(0) != 113) {
  }
}

void ShapeDetect::getContours(cv::Mat imgDil, cv::Mat &img) {
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;

  cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL,
                   cv::CHAIN_APPROX_SIMPLE);

  // cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);

  for (int i = 0; i < contours.size(); ++i) {
    double area = cv::contourArea(contours[i]);
    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());
    std::string shape;
    if (area > 10000) {
      double peri = cv::arcLength(contours[i], true);
      cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
      cv::drawContours(img, contours, i, cv::Scalar(255, 0, 255), 3);
      boundRect[i] = cv::boundingRect(conPoly[i]);
      cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(),
                    cv::Scalar(0, 0, 255), 2);

      int corners = (int)conPoly.size();
      if (corners == 3) {
        shape = "Tri";
      } else if (corners == 4) {
        shape = "Rect";
      } else if (corners > 4) {
        shape = "Circle";
      }

      cv::putText(img, shape, {boundRect[i].x, boundRect[i].y},
                  cv::FONT_HERSHEY_PLAIN, 3, cv::Scalar(0, 0, 255), 2);
    }
  }
}
