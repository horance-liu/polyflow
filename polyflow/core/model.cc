#include "polyflow/core/model.h"
#include "cub/base/assertions.h"

struct TensorflowModel {};
struct TensorrtModel {};
struct OpenvinoModel {};

namespace {
inline cub::Status model_transfer(Model* model, ModelState from, ModelState to) {
  if (model->state == from) {
    model->state = to;
    return cub::Success;
  } else {
    model->state = ERROR;
    return cub::Failure;
  }
}
} // namespace

cub::Status Model::load() {
  switch (type) {
  case TENSORFLOW: {
    CUB_ASSERT_SUCC_CALL(model_transfer(this, NEW, LOADING));
    runtime.tf = new TensorflowModel;
    CUB_ASSERT_SUCC_CALL(model_transfer(this, LOADING, READY));
    return cub::Success;
  }
  case TENSORRT: {
    CUB_ASSERT_SUCC_CALL(model_transfer(this, NEW, LOADING));
    runtime.trt = new TensorrtModel;
    CUB_ASSERT_SUCC_CALL(model_transfer(this, LOADING, READY));
    return cub::Success;
  }
  case OPENVINO: {
    CUB_ASSERT_SUCC_CALL(model_transfer(this, NEW, LOADING));
    runtime.ov = new OpenvinoModel;
    CUB_ASSERT_SUCC_CALL(model_transfer(this, LOADING, READY));
    return cub::Success;
  }
  default:
    return cub::Failure;
  }
}

cub::Status Model::unload() {
  switch (type) {
  case TENSORFLOW: {
    CUB_ASSERT_SUCC_CALL(model_transfer(this, READY, UNLOADING));
    delete runtime.tf;
    CUB_ASSERT_SUCC_CALL(model_transfer(this, UNLOADING, DISABLED));
    return cub::Success;
  }
  case TENSORRT: {
    CUB_ASSERT_SUCC_CALL(model_transfer(this, READY, UNLOADING));
    delete runtime.trt;
    CUB_ASSERT_SUCC_CALL(model_transfer(this, UNLOADING, DISABLED));
    return cub::Success;
  }
  case OPENVINO: {
    CUB_ASSERT_SUCC_CALL(model_transfer(this, READY, UNLOADING));
    delete runtime.ov;
    CUB_ASSERT_SUCC_CALL(model_transfer(this, UNLOADING, DISABLED));
    return cub::Success;
  }
  default:
    return cub::Failure;
  }
}
