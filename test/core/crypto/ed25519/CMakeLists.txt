#
# Copyright Soramitsu Co., Ltd. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0
#

addtest(ed25519_provider_test
    ed25519_provider_test.cpp
    )
target_link_libraries(ed25519_provider_test
    ed25519_provider
    )
