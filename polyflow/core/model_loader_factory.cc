#include "polyflow/core/model_loader_factory.h"
#include "polyflow/tf/tf_model_loader.h"
#include "polyflow/trt/trt_model_loader.h"
#include "polyflow/ov/ov_model_loader.h"

namespace {
struct NilModelLoader : ModelLoader {
private:
  void loadModel()   override {}
  void unloadModel() override {}
};
} // namespace

ModelLoader* create_model_loader(ModelType type) {
  switch (type) {
  case TENSORFLOW:
    return new TensorflowModelLoader;
  case TENSORRT:
    return new TensorrtModelLoader;
  case OPENVINO:
    return new OpenvinoModelLoader;
  default:
    return new NilModelLoader;
  }
}
