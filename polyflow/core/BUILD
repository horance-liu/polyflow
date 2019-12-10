package(
    default_visibility = [
        "//polyflow:internal"
    ],
)

cc_library(
    name = "model",
    hdrs = ["model.h"],
    srcs = ["model.cc"],
    deps = [
        "@github_cub//cub/base:status",
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
