#include "polyflow/core/model.h"
#include "polyflow/tf/tf_runtime.h"
#include "polyflow/trt/trt_runtime.h"
#include "polyflow/ov/ov_runtime.h"

ModelRuntime* Model::create(RuntimeType type) {
  switch (type) {
  case TENSORFLOW:
    return new TensorflowRuntime;
  case TENSORRT:
    return new TensorrtRuntime;
  case OPENVINO:
    return new OpenvinoRuntime;
  default:
    return nullptr;
  }
}

Model::Model(RuntimeType type) : runtime(create(type)) {
}

Model::~Model() {
  delete runtime;
}

cub::Status Model::load() {
  return state.onLoad(*this);
}

cub::Status Model::unload() {
  return state.onUnload(*this);
}

template <typename Op>
cub::Status Model::op(Op op) {
  return runtime ? (op(*runtime), cub::Success) : cub::Failure;
}

cub::Status Model::loadModel() {
  return op([](ModelRuntime& runtime){
    return runtime.loadModel();
  });
}

cub::Status Model::unloadModel() {
  return op([](ModelRuntime& runtime){
    return runtime.unloadModel();
  });
}
