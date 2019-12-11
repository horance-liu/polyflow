#ifndef HF9F842A4_C796_4725_8711_EA75EB36E484
#define HF9F842A4_C796_4725_8711_EA75EB36E484

#include "cub/base/status.h"

enum ModelType {
  TENSORFLOW, TENSORRT, OPENVINO,
};

enum ModelState {
  NEW, LOADING, READY, UNLOADING, DISABLED, ERROR,
};

struct TensorflowModel;
struct TensorrtModel;
struct OpenvinoModel;

struct Model {
  Model(ModelType type);

  cub::Status load();
  cub::Status unload();

  ModelState state;
  ModelType type;
  union {
    TensorflowModel* tf;
    TensorrtModel* trt;
    OpenvinoModel* ov;
  } runtime;

private:
  cub::Status transfer(ModelState from, ModelState to);
};

cub::Status model_unload(Model* model);

#endif
