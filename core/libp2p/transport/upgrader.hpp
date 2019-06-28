/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef KAGOME_UPGRADER_HPP
#define KAGOME_UPGRADER_HPP

#include <memory>

#include <outcome/outcome.hpp>
#include "libp2p/connection/capable_connection.hpp"
#include "libp2p/connection/raw_connection.hpp"
#include "libp2p/connection/secure_connection.hpp"

namespace libp2p::transport {

  /**
   * Lifetime of the connection is: Raw -> Secure -> Muxed -> [Streams over
   * Muxed]. Upgrader handles the first two steps, understanding, which security
   * and muxer protocols are available on both sides (via Multiselect protocol)
   * and using the chosen protocols to actually upgrade the connections
   */
  struct Upgrader {
    using RawSPtr = std::shared_ptr<connection::RawConnection>;
    using SecSPtr = std::shared_ptr<connection::SecureConnection>;
    using CapSPtr = std::shared_ptr<connection::CapableConnection>;

    using OnSecuredCallbackFunc = std::function<void(outcome::result<SecSPtr>)>;
    using OnMuxedCallbackFunc = std::function<void(outcome::result<CapSPtr>)>;

    virtual ~Upgrader() = default;

    /**
     * Upgrade a raw connection to the secure one
     * @param conn to be upgraded
     * @param cb - callback, which is called, when a connection is upgraded or
     * error happens
     */
    virtual void upgradeToSecure(RawSPtr conn, OnSecuredCallbackFunc cb) = 0;

    /**
     * Upgrade a secure connection to the muxed (capable) one
     * @param conn to be upgraded
     * @param cb - callback, which is called, when a connection is upgraded or
     * error happens
     */
    virtual void upgradeToMuxed(SecSPtr conn, OnMuxedCallbackFunc cb) = 0;
  };

}  // namespace libp2p::transport

#endif  // KAGOME_UPGRADER_HPP
