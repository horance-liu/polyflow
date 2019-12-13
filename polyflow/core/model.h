#ifndef HF9F842A4_C796_4725_8711_EA75EB36E484
#define HF9F842A4_C796_4725_8711_EA75EB36E484

#include "polyflow/core/model_loader.h"
#include "polyflow/core/model_state.h"
#include "polyflow/core/model_type.h"

struct Model {
  Model(ModelType type);
  ~Model();

  cub::Status load();
  cub::Status unload();

private:
  ModelState state;
  ModelLoader* loader;
};

#endif
