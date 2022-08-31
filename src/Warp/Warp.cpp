#include "Warp.h"
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#define WIDTH 250
#define HEIGHT 350

void Warp::warp_image(std::string &path) {
  cv::Mat img = cv::imread(path);
  cv::Mat imgWarp;

  // Get corners of image to warp
  cv::Point2f src[4] = {{1333, 738}, {1482, 867}, {1095, 830}, {1228, 985}};

  // The warp destination
  cv::Point2f dst[4] = {
      {0.0f, 0.0f}, {WIDTH, 0.0f}, {0.0f, HEIGHT}, {WIDTH, HEIGHT}};

  // Warp image
  cv::Mat matrix = cv::getPerspectiveTransform(src, dst);
  cv::warpPerspective(img, imgWarp, matrix, cv::Size(WIDTH, HEIGHT));

  for (auto &point : src) {
    cv::circle(img, point, 5, cv::Scalar(255, 0, 255), cv::FILLED);
  }

  cv::imshow("Image", img);
  cv::imshow("Image Warped", imgWarp);

  while (cv::waitKey(0) != 113) {
  }
}
