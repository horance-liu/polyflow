#include "polyflow/ov/ov_model_loader.h"

struct OpenvinoModel {};

void OpenvinoModelLoader::loadModel() {
  ov = new OpenvinoModel;
}

void OpenvinoModelLoader::unloadModel() {
  delete ov;
}
