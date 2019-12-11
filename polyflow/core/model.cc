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

Model::Type Model::getType() const {
  return type;
}

cub::Status Model::loadModel() {
  switch (getType()) {
  case TENSORFLOW: {
    m.tf = new TensorflowModel;
    return cub::Success;
  }
  case TENSORRT: {
    m.trt = new TensorrtModel;
    return cub::Success;
  }
  case OPENVINO: {
    m.ov = new OpenvinoModel;
    return cub::Success;
  }
  default:
    return cub::Failure;
  }
}

cub::Status Model::unloadModel() {
  switch (getType()) {
  case TENSORFLOW: {
    delete m.tf;
    return cub::Success;
  }
  case TENSORRT: {
    delete m.trt;
    return cub::Success;
  }
  case OPENVINO: {
    delete m.ov;
    return cub::Success;
  }
  default:
    return cub::Failure;
  }
}
