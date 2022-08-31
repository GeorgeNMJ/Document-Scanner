#include "src/DocScanner/DocScanner.h"

using namespace std;
using namespace cv;

int main() {
  // 420x596 size of A4 paper in pixels
  DocScanner scanner(420, 596);

  string path = "./img/giants.jpg";
  Mat img = imread(path);

  scanner.scanImage(img);

  // DocScanner::draw_points(img, scanner.getPoints(), Scalar(0, 0, 255));

  imshow("Image", img);
  imshow("Image Warped", scanner.getDocument());
  while (waitKey(0) != 113) {
  }
}
