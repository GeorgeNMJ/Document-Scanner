#pragma once
#include <opencv2/core/mat.hpp>
#include <string>

class Warp {

public:
  static void warp_image(std::string &path);
};
