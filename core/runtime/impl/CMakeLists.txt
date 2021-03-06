#
# Copyright Soramitsu Co., Ltd. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0
#

add_library(wasm_executor
    wasm_executor.hpp
    wasm_executor.cpp
    )
target_link_libraries(wasm_executor
    binaryen::binaryen
    buffer
    logger
    )

add_library(runtime_external_interface
    runtime_external_interface.hpp
    runtime_external_interface.cpp
    )
target_link_libraries(runtime_external_interface
    wasm_executor
    wasm_memory
    )

add_library(storage_wasm_provider
    storage_wasm_provider.cpp
    )
target_link_libraries(storage_wasm_provider
    buffer
    )

add_library(basic_wasm_provider
    basic_wasm_provider.cpp
    )
target_link_libraries(basic_wasm_provider
    buffer
    Boost::filesystem
    )
