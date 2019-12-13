#include "polyflow/trt/trt_model_loader.h"

struct TensorrtModel {};

void TensorrtModelLoader::loadModel() {
  trt = new TensorrtModel;
}

void TensorrtModelLoader::unloadModel() {
  delete trt;
}
