/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "core/runtime/runtime_test.hpp"
#include "extensions/impl/extension_impl.hpp"
#include "runtime/impl/parachain_host_impl.hpp"
#include "runtime/impl/wasm_memory_impl.hpp"
#include "testutil/outcome.hpp"

using kagome::common::Buffer;
using kagome::extensions::ExtensionImpl;
using kagome::primitives::parachain::Chain;
using kagome::primitives::parachain::DutyRoster;
using kagome::primitives::parachain::Parachain;
using kagome::primitives::parachain::ParaId;
using kagome::primitives::parachain::Relay;
using kagome::primitives::parachain::ValidatorId;
using kagome::runtime::ParachainHost;
using kagome::runtime::ParachainHostImpl;

using ::testing::_;
using ::testing::Return;

namespace fs = boost::filesystem;

class ParachainHostTest : public RuntimeTest {
 public:
  void SetUp() override {
    RuntimeTest::SetUp();

    api_ = std::make_shared<ParachainHostImpl>(wasm_provider_, extension_factory_);
  }

  ParaId createParachainId() const {
    return 1ul;
  }

 protected:
  std::shared_ptr<ParachainHost> api_;
};

// TODO(yuraz): PRE-157 find out do we need to give block_id to api functions
/**
 * @given initialized parachain host api
 * @when dutyRoster() is invoked
 * @then successful result is returned
 */
TEST_F(ParachainHostTest, DISABLED_DutyRosterTest) {
  ASSERT_TRUE(api_->duty_roster());
}

/**
 * @given initialized parachain host api
 * @when activeParachains() is invoked
 * @then successful result is returned
 */
TEST_F(ParachainHostTest, DISABLED_ActiveParachainsTest) {
  ASSERT_TRUE(api_->active_parachains());
}

/**
 * @given initialized parachain host api
 * @when parachainHead() is invoked
 * @then successful result is returned
 */
TEST_F(ParachainHostTest, DISABLED_ParachainHeadTest) {
  auto id = createParachainId();
  ASSERT_TRUE(api_->parachain_head(id));
}

/**
 * @given initialized parachain host api
 * @when parachain_code() is invoked
 * @then successful result is returned
 */
TEST_F(ParachainHostTest, DISABLED_ParachainCodeTest) {
  auto id = createParachainId();
  ASSERT_TRUE(api_->parachain_code(id));
}

/**
 * @given initialized parachain host api
 * @when validators() is invoked
 * @then successful result is returned
 */
TEST_F(ParachainHostTest, DISABLED_ValidatorsTest) {
  ASSERT_TRUE(api_->validators());
}
