#include "polyflow/core/model.h"
#include "cub/base/assertions.h"

struct TensorflowModel {};
struct TensorrtModel {};
struct OpenvinoModel {};

Model::Model(ModelType type) : state(NEW), type(type) {
}

inline cub::Status Model::transfer(ModelState from, ModelState to) {
  if (state == from) {
    state = to;
    return cub::Success;
  } else {
    state = ERROR;
    return cub::Failure;
  }
}

cub::Status Model::load() {
  switch (type) {
  case TENSORFLOW: {
    CUB_ASSERT_SUCC_CALL(transfer(NEW, LOADING));
    runtime.tf = new TensorflowModel;
    CUB_ASSERT_SUCC_CALL(transfer(LOADING, READY));
    return cub::Success;
  }
  case TENSORRT: {
    CUB_ASSERT_SUCC_CALL(transfer(NEW, LOADING));
    runtime.trt = new TensorrtModel;
    CUB_ASSERT_SUCC_CALL(transfer(LOADING, READY));
    return cub::Success;
  }
  case OPENVINO: {
    CUB_ASSERT_SUCC_CALL(transfer(NEW, LOADING));
    runtime.ov = new OpenvinoModel;
    CUB_ASSERT_SUCC_CALL(transfer(LOADING, READY));
    return cub::Success;
  }
  default:
    return cub::Failure;
  }
}

cub::Status Model::unload() {
  switch (type) {
  case TENSORFLOW: {
    CUB_ASSERT_SUCC_CALL(transfer(READY, UNLOADING));
    delete runtime.tf;
    CUB_ASSERT_SUCC_CALL(transfer(UNLOADING, DISABLED));
    return cub::Success;
  }
  case TENSORRT: {
    CUB_ASSERT_SUCC_CALL(transfer(READY, UNLOADING));
    delete runtime.trt;
    CUB_ASSERT_SUCC_CALL(transfer(UNLOADING, DISABLED));
    return cub::Success;
  }
  case OPENVINO: {
    CUB_ASSERT_SUCC_CALL(transfer(READY, UNLOADING));
    delete runtime.ov;
    CUB_ASSERT_SUCC_CALL(transfer(UNLOADING, DISABLED));
    return cub::Success;
  }
  default:
    return cub::Failure;
  }
}
