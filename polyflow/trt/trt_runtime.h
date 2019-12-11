#ifndef H1986F646_11DF_406E_9356_229E6DC6E393
#define H1986F646_11DF_406E_9356_229E6DC6E393

#include "polyflow/core/model_runtime.h"

struct TensorrtModel;

struct TensorrtRuntime : ModelRuntime {
private:
  void loadModel() override;
  void unloadModel() override;

private:
  TensorrtModel* trt = nullptr;
};

#endif
