#include "polyflow/tf/tf_model_loader.h"

struct TensorflowModel {};

void TensorflowModelLoader::loadModel() {
  tf = new TensorflowModel;
}

void TensorflowModelLoader::unloadModel() {
  delete tf;
}
