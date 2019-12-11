#include "polyflow/core/model.h"
#include "cub/base/assertions.h"

struct TensorflowModel {};
struct TensorrtModel {};
struct OpenvinoModel {};

Model::Model(Type type) : type(type) {
}

cub::Status Model::load() {
  return state.onLoad(*this);
}

cub::Status Model::unload() {
  return state.onUnload(*this);
}

cub::Status Model::loadModel() {
  switch (type) {
  case TENSORFLOW: {
    runtime.tf = new TensorflowModel;
    return cub::Success;
  }
  case TENSORRT: {
    runtime.trt = new TensorrtModel;
    return cub::Success;
  }
  case OPENVINO: {
    runtime.ov = new OpenvinoModel;
    return cub::Success;
  }
  default:
    return cub::Failure;
  }
}

cub::Status Model::unloadModel() {
  switch (type) {
  case TENSORFLOW: {
    delete runtime.tf;
    return cub::Success;
  }
  case TENSORRT: {
    delete runtime.trt;
    return cub::Success;
  }
  case OPENVINO: {
    delete runtime.ov;
    return cub::Success;
  }
  default:
    return cub::Failure;
  }
}
