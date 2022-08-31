#pragma once
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

class VPainter {
private:
  std::vector<std::vector<int>> cvals;

public:
  static void detect_color();
};
