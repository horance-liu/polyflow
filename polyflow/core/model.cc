#include "polyflow/core/model.h"
#include "polyflow/core/model_loader_factory.h"

Model::Model(ModelType type) : loader(create_model_loader(type)) {
}

Model::~Model() {
  delete loader;
}

cub::Status Model::load() {
  return state.onLoad(*loader);
}

cub::Status Model::unload() {
  return state.onUnload(*loader);
}
