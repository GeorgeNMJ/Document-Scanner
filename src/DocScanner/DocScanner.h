#pragma once
#include <array>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <string>
#include <vector>

class DocScanner {
  std::array<float, 2> docSize;
  std::vector<cv::Point> docPoints;
  cv::Mat document;

public:
  DocScanner(float width, float height);
  void scanImage(cv::Mat &img);
  static void drawPoints(cv::Mat &img, const std::vector<cv::Point> points,
                         const cv::Scalar color);
  void preprocessImage(const cv::Mat img, cv::Mat &imgDil);
  void findDocument(const cv::Mat img);
  void reorderPoints();
  void warpImage(const cv::Mat img, cv::Mat &imgWarp);
  cv::Mat getDocument();
  void setWidth(const int w);
  void setHeight(const int h);
  int getWidth();
  int getHeight();
  void setPoints(std::vector<cv::Point> newPoints);
  std::vector<cv::Point> getPoints();
};
