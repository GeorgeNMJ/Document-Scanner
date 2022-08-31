#include "CVBasics.h"
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

void CVBasics::load_image(std::string &path) {
  // opencv has own datatype for loading images/videos
  // cv::Mat
  cv::Mat img = cv::imread(path);

  // to load image directly to grayscale
  // cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);

  ///////////* converting image *///////////////////////
  cv::Mat imgGray;
  cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

  ///////////* Add blur to image *//////////////////////
  cv::Mat imgBlur;
  // Size must be odd numbers
  cv::GaussianBlur(img, imgBlur, cv::Size(7, 7), 5);

  ////////////* Edge Detector *////////////////////////
  /// common practice is to blur the image first before edge detection
  cv::Mat imgCanny;
  cv::Canny(imgBlur, imgCanny, 25, 75); // 50 and 150 are thresholds

  ///////////* Increase/Decrease line thickness of edges *///////
  /// We have to do this so the lines get connected
  cv::Mat imgDilate, imgErode; // dilate thicken, erode make thinner
  cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
  cv::dilate(imgCanny, imgDilate, kernel);
  cv::erode(imgDilate, imgErode, kernel);

  // show image
  // cv::imshow("Image", img);
  // cv::imshow("Image Gray", imgGray);
  // cv::imshow("Image Blur", imgBlur);
  // cv::imshow("Image Canny", imgCanny);
  // cv::imshow("Image Dilate", imgDilate);
  // cv::imshow("Image Erode", imgErode);

  // press q to quit
  while (cv::waitKey(0) != 113) {
  }
}

void CVBasics::resize_image(std::string &path) {
  cv::Mat img = cv::imread(path);
  cv::Mat imgResized, imgCropped;

  ////* Resizing Image *//////
  cv::resize(img, imgResized, cv::Size(), 0.5, 0.5);

  ////* Cropping Image *//////
  cv::Rect roi(260, 650, 500, 1200);
  imgCropped = img(roi);

  cv::imshow("Image", img);
  cv::imshow("Image Resized", imgResized);
  cv::imshow("Image Cropped", imgCropped);

  while (cv::waitKey(0) != 113) {
  }
}

void CVBasics::draw_shape(std::string &path) {

  // Blank Image
  // CV_8UC3; 8(2^8 = 256) = bytes; U = unsigned(0-255); C3 = 3 Channels (rgb)
  cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));

  // FILLED to fill shape, int to specific thickness
  cv::circle(img, cv::Point(256, 267), 155, cv::Scalar(255, 0, 255),
             cv::FILLED);
  cv::rectangle(img, cv::Point(130, 226), cv::Point(382, 286),
                cv::Scalar(255, 255, 255), cv::FILLED);
  cv::line(img, cv::Point(130, 296), cv::Point(382, 296),
           cv::Scalar(255, 255, 255), 2);

  cv::putText(img, "Some Drawings", cv::Point(137, 262),
              cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar(255, 0, 255), 2);
  cv::imshow("Image", img);

  while (cv::waitKey(0) != 113) {
  }
}

void CVBasics::load_video(std::string &path) {
  // video is just a series of images

  cv::VideoCapture cap(path);
  cv::Mat img;
  // show image
  while (true) {
    cap.read(img);

    cv::imshow("Video", img);

    // slow the video by increasing waitkey value
    if (cv::waitKey(1) == 113) {
      cv::destroyAllWindows();
      break;
    }
  }
}

void CVBasics::load_cam() {
  // video is just a series of images
  cv::VideoCapture cap(0);
  cv::Mat img;
  // show image
  while (true) {
    cap.read(img);

    cv::imshow("Video", img);

    // slow the video by increasing waitkey value
    if (cv::waitKey(1) == 113) {
      cv::destroyAllWindows();
      break;
    }
  }
}
