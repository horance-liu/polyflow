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
    name = "model_state",
    hdrs = ["model_state.h"],
    srcs = ["model_state.cc"],    
    deps = [
        ":model_loader",
        "@github_cub//cub/base:assertions",
    ],    
)

cc_library(
    name = "model",
    hdrs = ["model.h"],
    srcs = ["model.cc"],
    deps = [
        ":model_state",
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
