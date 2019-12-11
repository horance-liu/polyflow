#ifndef HF9F842A4_C796_4725_8711_EA75EB36E484
#define HF9F842A4_C796_4725_8711_EA75EB36E484

#include "polyflow/core/model_loader.h"
#include "polyflow/core/model_state.h"
#include "polyflow/core/runtime_type.h"

struct ModelRuntime;

struct Model : private ModelLoader {
  Model(RuntimeType type);
  ~Model();

  cub::Status load();
  cub::Status unload();

private:
  cub::Status loadModel() override;
  cub::Status unloadModel() override;

  template <typename Op>
  cub::Status op(Op op);

private:
  static ModelRuntime* create(RuntimeType type);

private:
  ModelState state;
  ModelRuntime* runtime;
};

#endif
