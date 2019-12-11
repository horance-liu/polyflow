#include "polyflow/tf/tf_runtime.h"

struct TensorflowModel {};

void TensorflowRuntime::loadModel() {
  tf = new TensorflowModel;
}

void TensorflowRuntime::unloadModel() {
  delete tf;
}
