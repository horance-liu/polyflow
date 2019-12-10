#include "polyflow/core/model.h"

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

cub::Status model_load(Model* model) {
  switch (model->type) {
  case TENSORFLOW: {
    cub::Status status = model_transfer(model, NEW, LOADING);
    if (status != cub::Success) {
      return status;
    }
    model->runtime.tf = new TensorflowModel;
    status = model_transfer(model, LOADING, READY);
    if (status != cub::Success) {
      return status;
    }
    return cub::Success;
  }
  case TENSORRT: {
    cub::Status status = model_transfer(model, NEW, LOADING);
    if (status != cub::Success) {
      return status;
    }
    model->runtime.trt = new TensorrtModel;
    status = model_transfer(model, LOADING, READY);
    if (status != cub::Success) {
      return status;
    }
    return cub::Success;
  }
  case OPENVINO: {
    cub::Status status = model_transfer(model, NEW, LOADING);
    if (status != cub::Success) {
      return status;
    }
    model->runtime.ov = new OpenvinoModel;
    status = model_transfer(model, LOADING, READY);
    if (status != cub::Success) {
      return status;
    }
    return cub::Success;
  }
  default:
    return cub::Failure;
  }
}

cub::Status model_unload(Model* model) {
  switch (model->type) {
  case TENSORFLOW: {
    cub::Status status = model_transfer(model, READY, UNLOADING);
    if (status != cub::Success) {
      return status;
    }
    delete model->runtime.tf;
    status = model_transfer(model, UNLOADING, DISABLED);
    if (status != cub::Success) {
      return status;
    }
    return cub::Success;
  }
  case TENSORRT: {
    cub::Status status = model_transfer(model, READY, UNLOADING);
    if (status != cub::Success) {
      return status;
    }
    delete model->runtime.trt;
    status = model_transfer(model, UNLOADING, DISABLED);
    if (status != cub::Success) {
      return status;
    }
    return cub::Success;
  }
  case OPENVINO: {
    cub::Status status = model_transfer(model, READY, UNLOADING);
    if (status != cub::Success) {
      return status;
    }
    delete model->runtime.ov;
    status = model_transfer(model, UNLOADING, DISABLED);
    if (status != cub::Success) {
      return status;
    }
    return cub::Success;
  }
  default:
    return cub::Failure;
  }
}
