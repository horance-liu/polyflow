#ifndef HF9F842A4_C796_4725_8711_EA75EB36E484
#define HF9F842A4_C796_4725_8711_EA75EB36E484

#include "polyflow/core/model_loader.h"
#include "polyflow/core/model_state.h"

struct TensorflowModel;
struct TensorrtModel;
struct OpenvinoModel;

struct Model : private ModelLoader {
  enum Type {
    TENSORFLOW, TENSORRT, OPENVINO,
  };

  Model(Type type);

  cub::Status load();
  cub::Status unload();

private:
  cub::Status loadModel() override;
  cub::Status unloadModel() override;

private:
  ModelState state;
  Type type;
  union {
    TensorflowModel* tf;
    TensorrtModel* trt;
    OpenvinoModel* ov;
  } m;
};

#endif
