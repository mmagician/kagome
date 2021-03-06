/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "consensus/babe/impl/babe_lottery_impl.hpp"

#include <gtest/gtest.h>
#include "common/buffer.hpp"
#include "crypto/util.hpp"
#include "mock/core/crypto/hasher_mock.hpp"
#include "mock/core/crypto/vrf_provider_mock.hpp"

using namespace kagome;
using namespace crypto;
using namespace consensus;
using namespace common;

using testing::Return;

namespace vrf_constants = kagome::crypto::constants::sr25519::vrf;

struct BabeLotteryTest : public testing::Test {
  void SetUp() override {
    keypair_.public_key.fill(2);
    keypair_.secret_key.fill(3);
  }

  std::shared_ptr<VRFProviderMock> vrf_provider_ =
      std::make_shared<VRFProviderMock>();
  std::shared_ptr<HasherMock> hasher_ = std::make_shared<HasherMock>();

  BabeLotteryImpl lottery_{vrf_provider_, hasher_};

  std::vector<VRFValue> submitted_vrf_values_{28482, 57302840, 8405};
  Epoch current_epoch_{
      1,
      0,
      3,
      std::chrono::milliseconds(20),
      {},
      10,
      Randomness{
          0x11, 0x22, 0x33, 0x44, 0x11, 0x22, 0x33, 0x44, 0x11, 0x22, 0x33,
          0x44, 0x11, 0x22, 0x33, 0x44, 0x11, 0x22, 0x33, 0x44, 0x11, 0x22,
          0x33, 0x44, 0x11, 0x22, 0x33, 0x44, 0x11, 0x22, 0x33, 0x44,
      }};
  SR25519Keypair keypair_{};
};

/**
 * @given BabeLottery with a number of VRF values submitted
 * @when computing leadership for the epoch
 * @then leadership is computed as intended
 */
TEST_F(BabeLotteryTest, SlotsLeadership) {
  // GIVEN
  for (const auto &value : submitted_vrf_values_) {
    lottery_.submitVRFValue(value);
  }

  std::vector<VRFOutput> vrf_outputs;
  vrf_outputs.reserve(2);
  vrf_outputs.push_back({3749373, {}});
  vrf_outputs.push_back({1057472095, {}});

  Buffer vrf_input(vrf_constants::OUTPUT_SIZE + 8, 0);
  std::copy(current_epoch_.randomness.begin(),
            current_epoch_.randomness.end(),
            vrf_input.begin());
  for (size_t i = 0; i < current_epoch_.epoch_duration; ++i) {
    auto slot_bytes = crypto::util::uint64_t_to_bytes(i);
    std::copy(slot_bytes.begin(),
              slot_bytes.end(),
              vrf_input.begin() + vrf_constants::OUTPUT_SIZE);
    if (i == 2) {
      // just random case for testing
      EXPECT_CALL(*vrf_provider_,
                  sign(vrf_input, keypair_, current_epoch_.threshold))
          .WillOnce(Return(boost::none));
      continue;
    }
    EXPECT_CALL(*vrf_provider_,
                sign(vrf_input, keypair_, current_epoch_.threshold))
        .WillOnce(Return(vrf_outputs[i]));
  }

  // WHEN
  auto leadership = lottery_.slotsLeadership(current_epoch_, keypair_);

  // THEN
  ASSERT_TRUE(leadership[0]);
  ASSERT_EQ(leadership[0]->value, 3749373);
  ASSERT_TRUE(leadership[1]);
  ASSERT_EQ(leadership[1]->value, 1057472095);
  ASSERT_FALSE(leadership[2]);
}

/**
 * @given BabeLottery with a number of VRF values submitted
 * @when computing randomness for the next epoch
 * @then randomness is computed as intended
 */
TEST_F(BabeLotteryTest, ComputeRandomness) {
  // GIVEN
  for (const auto &value : submitted_vrf_values_) {
    lottery_.submitVRFValue(value);
  }

  // WHEN
  Buffer concat_values{};
  concat_values.put(current_epoch_.randomness);
  concat_values.put(
      crypto::util::uint64_t_to_bytes(current_epoch_.epoch_index));
  for (const auto &value : submitted_vrf_values_) {
    concat_values.put(crypto::util::uint256_t_to_bytes(value));
  }

  Hash256 new_randomness{};
  new_randomness.fill(1);
  new_randomness[10] = 9;
  EXPECT_CALL(*hasher_,
              blake2b_256(gsl::span<const uint8_t>(concat_values.toVector())))
      .WillOnce(Return(new_randomness));

  auto returned_randomness = lottery_.computeRandomness(
      current_epoch_.randomness, current_epoch_.epoch_index);

  // THEN
  ASSERT_EQ(new_randomness, returned_randomness);
}
