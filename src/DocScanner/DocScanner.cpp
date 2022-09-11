#include "DocScanner.h"

using namespace cv;
using namespace std;

DocScanner::DocScanner(float width, float height) {
  m_DocSize[0] = width;
  m_DocSize[1] = height;
}

void DocScanner::Scan(cv::Mat &img) {
  Mat imgDil;

  // preprocess
  Preprocess(img, imgDil);

  // get contours
  FindDocument(imgDil);
  // TODO turn reorder to the same configuration as the find_doc
  // points = reorder(points);
  ReorderPoints();

  // warp image
  Warp(img, m_Document);
}

void DocScanner::Preprocess(const Mat img, Mat &imgDil) {
  Mat imgGray, imgBlur, imgCanny;

  // convert image to grayscale
  cvtColor(img, imgGray, COLOR_BGR2GRAY);

  // blur image
  GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);

  // find edges/contours
  Canny(imgBlur, imgCanny, 25, 75);

  // increase contour size
  Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
  dilate(imgCanny, imgDil, kernel);
}

void DocScanner::FindDocument(const Mat img) {
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;

  findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

  // cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);

  int maxArea = 0;
  for (int i = 0; i < contours.size(); ++i) {
    double area = contourArea(contours[i]);
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    string shape;
    if (area > 10000) {
      double peri = arcLength(contours[i], true);
      approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

      if (area > maxArea && conPoly[i].size() == 4) {
        m_DocPoints = {conPoly[i][0], conPoly[i][1], conPoly[i][2],
                       conPoly[i][3]};
        maxArea = area;
      }

      drawContours(img, contours, i, Scalar(255, 0, 255), 3);
    }
  }
}

void DocScanner::DrawPoints(Mat &img, const vector<Point> points,
                            const Scalar color) {
  for (int i = 0; i < points.size(); i++) {
    circle(img, points[i], 5, color, FILLED);
    putText(img, to_string(i), points[i], FONT_HERSHEY_PLAIN, 2, color, 2);
  }
}

void DocScanner::ReorderPoints() {
  vector<int> points_sum, points_dif;
  for (auto point : m_DocPoints) {
    points_sum.push_back(point.x + point.y);
    points_dif.push_back(point.x - point.y);
  }

  vector<Point> reordered_points = {
      m_DocPoints[std::min_element(points_sum.begin(), points_sum.end()) -
                  points_sum.begin()],
      m_DocPoints[std::max_element(points_dif.begin(), points_dif.end()) -
                  points_dif.begin()],
      m_DocPoints[std::min_element(points_dif.begin(), points_dif.end()) -
                  points_dif.begin()],
      m_DocPoints[std::max_element(points_sum.begin(), points_sum.end()) -
                  points_sum.begin()]};

  m_DocPoints = reordered_points;
}

void DocScanner::Warp(const Mat img, Mat &imgWarp) {
  // Get corners of image to warp
  Point2f src_corners[4] = {m_DocPoints[0], m_DocPoints[1], m_DocPoints[2],
                            m_DocPoints[3]};

  // The warp destination
  Point2f dst_corners[4] = {{0.0f, 0.0f},
                            {m_DocSize[0], 0.0f},
                            {0.0f, m_DocSize[1]},
                            {m_DocSize[0], m_DocSize[1]}};

  // Warp image
  Mat matrix = getPerspectiveTransform(src_corners, dst_corners);
  warpPerspective(img, imgWarp, matrix, cv::Size(m_DocSize[0], m_DocSize[1]));
}

Mat DocScanner::GetDocument() { return m_Document; }
int DocScanner::getWidth() { return m_DocSize[0]; }
int DocScanner::getHeight() { return m_DocSize[1]; }
void DocScanner::setWidth(const int w) { m_DocSize[0] = w; }
void DocScanner::setHeight(const int h) { m_DocSize[0] = h; }
void DocScanner::setPoints(std::vector<cv::Point> newPoints) {
  m_DocPoints = newPoints;
}

vector<Point> DocScanner::getPoints() { return m_DocPoints; };
