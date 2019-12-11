#include "polyflow/trt/trt_runtime.h"

struct TensorrtModel {};

void TensorrtRuntime::loadModel() {
  trt = new TensorrtModel;
}

void TensorrtRuntime::unloadModel() {
  delete trt;
}
