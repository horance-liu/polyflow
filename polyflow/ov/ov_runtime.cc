#include "polyflow/ov/ov_runtime.h"

struct OpenvinoModel {};

void OpenvinoRuntime::loadModel() {
  ov = new OpenvinoModel;
}

void OpenvinoRuntime::unloadModel() {
  delete ov;
}
