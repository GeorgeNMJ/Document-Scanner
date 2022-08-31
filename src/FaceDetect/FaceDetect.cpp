#include "FaceDetect.h"
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>
#include <vector>

void FaceDetect::fdetect(std::string path) {
  cv::Mat img = cv::imread(path);
  cv::CascadeClassifier faceCascade;
  // faceCascade.load(const String &filename); // file path of premade
  // classifier

  std::vector<cv::Rect> faces;
  faceCascade.detectMultiScale(img, faces, 1.1, 10);
}
