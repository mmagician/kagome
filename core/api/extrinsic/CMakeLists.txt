#
# Copyright Soramitsu Co., Ltd. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0
#

add_library(extrinsic_api_service
    error.cpp
    error.hpp
    extrinsic_api.hpp
    extrinsic_jrpc_processor.hpp
    extrinsic_jrpc_processor.cpp
    extrinsic_api_service.hpp
    extrinsic_api_service.cpp
    impl/extrinsic_api_impl.hpp
    impl/extrinsic_api_impl.cpp
    request/submit_extrinsic.hpp
    request/submit_extrinsic.cpp
    )
target_link_libraries(extrinsic_api_service
    buffer
    api_jrpc_processor
    api_service
    transaction_pool
    )
