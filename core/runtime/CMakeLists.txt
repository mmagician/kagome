#
# Copyright Soramitsu Co., Ltd. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0
#

add_subdirectory(impl)

add_library(wasm_memory
    common.hpp
    wasm_result.hpp
    wasm_memory.hpp
    impl/wasm_memory_impl.hpp
    impl/wasm_memory_impl.cpp
    )
target_link_libraries(wasm_memory
    buffer
    binaryen::binaryen
    )
kagome_install(wasm_memory)

add_library(core
    core.hpp
    impl/core_impl.hpp
    impl/core_impl.cpp
    )
target_link_libraries(core
    scale
    runtime_external_interface
    )

add_library(tagged_transaction_queue
    tagged_transaction_queue.hpp
    impl/tagged_transaction_queue_impl.cpp
    impl/tagged_transaction_queue_impl.hpp
    )
target_link_libraries(tagged_transaction_queue
    scale
    runtime_external_interface
    )

add_library(block_builder_api
    block_builder_api.hpp
    impl/block_builder_api_impl.cpp
    impl/block_builder_api_impl.hpp
    )
target_link_libraries(block_builder_api
    scale
    primitives
    runtime_external_interface
    )

add_library(parachain_host_api
    parachain_host.hpp
    impl/parachain_host_impl.hpp
    impl/parachain_host_impl.cpp
    )
target_link_libraries(parachain_host_api
    scale
    runtime_external_interface
    )

add_library(grandpa_api
    grandpa.hpp
    impl/grandpa_impl.hpp
    impl/grandpa_impl.cpp
    )
target_link_libraries(grandpa_api
    scale
    runtime_external_interface
    )

add_library(metadata_api
    metadata.hpp
    impl/metadata_impl.hpp
    impl/metadata_impl.cpp
    )
target_link_libraries(metadata_api
    scale
    runtime_external_interface
    )

add_library(offchain_worker_api
    offchain_worker.hpp
    impl/offchain_worker_impl.hpp
    impl/offchain_worker_impl.cpp
    )
target_link_libraries(offchain_worker_api
    scale
    wasm_executor
    runtime_external_interface
    )
