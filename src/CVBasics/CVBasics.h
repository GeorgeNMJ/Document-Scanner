#pragma once
#include <string>

class CVBasics {
public:
  static void load_image(std::string &path);
  static void resize_image(std::string &path);
  static void draw_shape(std::string &path);
  static void load_video(std::string &path);
  static void load_cam();
};
