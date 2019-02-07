/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef UGUISU_ROUTER_HPP
#define UGUISU_ROUTER_HPP

#include <queue>

#include "libp2p/common_objects/multihash.hpp"
#include "libp2p/common_objects/peer.hpp"

namespace libp2p {
  namespace routing {
    /**
     * Provides a way to find other peers in the network to establish
     * connections with them
     */
    class Router {
     public:
      /**
       * Find peers 'responsible' or 'closest' to a given key; explanation of
       * these terms can be found in the articles about Kademlia DHT
       * @param key to be searched for
       * @return collection of found peers, sorted by 'closeness' to the key
       */
      virtual std::priority_queue<common::Peer::PeerInfo> findPeers(
          const common::Multihash &key) const = 0;
    };
  }  // namespace routing
}  // namespace libp2p

#endif  // UGUISU_ROUTER_HPP
