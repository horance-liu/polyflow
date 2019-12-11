#include "polyflow/core/model.h"
#include "cub/base/assertions.h"

struct TensorflowModel {};
struct TensorrtModel {};
struct OpenvinoModel {};

struct ModelRuntime {
  virtual Model::Type getModelType() const = 0;
  virtual ~ModelRuntime() {}
};

struct TensorflowRuntime : ModelRuntime {
private:
  Model::Type getModelType() const override {
    return Model::TENSORFLOW;
  }
};

struct TensorrtRuntime : ModelRuntime {
private:
  Model::Type getModelType() const override {
    return Model::TENSORRT;
  }
};

struct OpenvinoRuntime : ModelRuntime {
private:
  Model::Type getModelType() const override {
    return Model::OPENVINO;
  }
};

ModelRuntime* Model::create(Type type) {
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

Model::Model(Type type) : runtime(create(type)) {
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

Model::Type Model::getType() const {
  return runtime->getModelType();
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
