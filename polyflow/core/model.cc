#include "polyflow/core/model.h"
#include "cub/base/assertions.h"

struct TensorflowModel {};
struct TensorrtModel {};
struct OpenvinoModel {};

struct ModelRuntime {
  virtual cub::Status loadModel() {
    switch (getModelType()) {
    case Model::TENSORRT:
      m.trt = new TensorrtModel;
      return cub::Success;
    case Model::OPENVINO:
      m.ov = new OpenvinoModel;
      return cub::Success;
    default:
      return cub::Failure;
    }
  }

  virtual cub::Status unloadModel() {
    switch (getModelType()) {
    case Model::TENSORRT:
      delete m.trt;
      return cub::Success;
    case Model::OPENVINO:
      delete m.ov;
      return cub::Success;
    default:
      return cub::Failure;
    }
  }

  virtual Model::Type getModelType() const = 0;
  virtual ~ModelRuntime() {}

private:
  union {
    TensorrtModel* trt;
    OpenvinoModel* ov;
  } m;
};

struct TensorflowRuntime : ModelRuntime {
private:
  Model::Type getModelType() const override {
    return Model::TENSORFLOW;
  }

  cub::Status loadModel() override {
    tf = new TensorflowModel;
    return cub::Success;
  }

  cub::Status unloadModel() override {
    delete tf;
    return cub::Success;
  }

private:
  TensorflowModel* tf = nullptr;
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

cub::Status Model::loadModel() {
  return runtime->loadModel();
}

cub::Status Model::unloadModel() {
  return runtime->unloadModel();
}
