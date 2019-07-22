/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef KAGOME_KADEMLIA_COMMON_HPP
#define KAGOME_KADEMLIA_COMMON_HPP

#include <string>
#include <unordered_set>

#include "common/blob.hpp"
#include "libp2p/peer/peer_id.hpp"
#include "libp2p/peer/peer_info.hpp"

namespace libp2p::protocol::kademlia {

  using kagome::common::Hash256;

  /// DHT key
  using Key = std::vector<uint8_t>;

  /// DHT value
  using Value = std::vector<uint8_t>;

  /// Set of peer Ids
  using PeerIdSet = std::unordered_set<peer::PeerId>;

  using PeerIdVec = std::vector<peer::PeerId>;

  using PeerInfoVec = std::vector<peer::PeerInfo>;

  struct NodeId : public Hash256 {
    using Hash256::Hash256;

    bool operator==(const peer::PeerId &other) {
      auto size = other.toVector().size();
      if (other.toVector().size() != this->size()) {
        return false;
      }

      return 0 == std::memcmp(this->data(), other.toVector().data(), size);
    }
  };

  using NodeIdVec = std::vector<NodeId>;

  /// Content Id
  struct Cid {
    // TODO: tbd
  };

  struct ReceivedValue {
    Value value;
    peer::PeerId from;
  };

}  // namespace libp2p::protocol::kademlia

#endif  // KAGOME_KADEMLIA_COMMON_HPP