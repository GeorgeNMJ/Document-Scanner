#pragma once
#include <opencv2/core/mat.hpp>
#include <string>

class ShapeDetect {
private:
  static void getContours(cv::Mat imgDil, cv::Mat &img);

public:
  static void shdetect(std::string path);
};
