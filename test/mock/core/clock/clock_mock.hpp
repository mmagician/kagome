/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef KAGOME_TEST_CORE_CLOCK_CLOCK_MOCK_HPP
#define KAGOME_TEST_CORE_CLOCK_CLOCK_MOCK_HPP

#include "clock/clock.hpp"

#include <gmock/gmock.h>

namespace kagome::clock {

  class SystemClockMock : public SystemClock {
   public:
    MOCK_CONST_METHOD0(now, SystemClock::TimePoint());
  };

  class SteadyClockMock : public SteadyClock {
   public:
    MOCK_CONST_METHOD0(now, SteadyClock::TimePoint());
  };

}  // namespace kagome::clock

#endif  // KAGOME_TEST_CORE_CLOCK_CLOCK_MOCK_HPP
