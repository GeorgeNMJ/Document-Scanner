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
private:
  std::array<float, 2> m_DocSize;
  std::vector<cv::Point> m_DocPoints;
  cv::Mat m_Document;

public:
  DocScanner(float width, float height);
  void Scan(cv::Mat &img);
  static void DrawPoints(cv::Mat &img, const std::vector<cv::Point> points,
                         const cv::Scalar color);
  void Preprocess(const cv::Mat img, cv::Mat &imgDil);
  void FindDocument(const cv::Mat img);
  void ReorderPoints();
  void Warp(const cv::Mat img, cv::Mat &imgWarp);
  cv::Mat GetDocument();
  void setWidth(const int w);
  void setHeight(const int h);
  int getWidth();
  int getHeight();
  void setPoints(std::vector<cv::Point> newPoints);
  std::vector<cv::Point> getPoints();
};
