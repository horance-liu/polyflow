package(
    default_visibility = [
        "//polyflow:internal"
    ],
)

cc_library(
    name = "model_loader",
    hdrs = ["model_loader.h"],
    deps = [
        "@github_cub//cub/base:status",
    ],    
)

cc_library(
    name = "model_runtime",
    hdrs = ["model_runtime.h"],
)

cc_library(
    name = "runtime_type",
    hdrs = ["runtime_type.h"],
)

cc_library(
    name = "model_state",
    hdrs = ["model_state.h"],
    srcs = ["model_state.cc"],    
    deps = [
        ":model_loader",
        "@github_cub//cub/base:assertions",
    ],    
)

cc_library(
    name = "runtime_factory",
    hdrs = ["runtime_factory.h"],
    srcs = ["runtime_factory.cc"],
    deps = [
        ":runtime_type",
        "//polyflow/tf",
        "//polyflow/trt",
        "//polyflow/ov",        
    ],    
)

cc_library(
    name = "model",
    hdrs = ["model.h"],
    srcs = ["model.cc"],
    deps = [
        ":model_state",
        ":runtime_factory",
    ],    
)

cc_test(
    name = "model_test",
    srcs = ["model_test.cc"],
    deps = [
        ":model",
        "@xunit_cctest//cctest",
        "@xunit_cctest//cctest:main",        
    ],    
)
