#ifndef H33D23DD5_8479_4F2B_A345_5723877C6A89
#define H33D23DD5_8479_4F2B_A345_5723877C6A89

#include "cub/base/status.h"

struct ModelLoader {
  virtual cub::Status loadModel() = 0;
  virtual cub::Status unloadModel() = 0;
  virtual ~ModelLoader() {};
};

#endif
