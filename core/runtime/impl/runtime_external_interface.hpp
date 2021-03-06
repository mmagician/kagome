/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef KAGOME_CORE_RUNTIME_IMPL_RUNTIME_EXTERNAL_INTERFACE_HPP
#define KAGOME_CORE_RUNTIME_IMPL_RUNTIME_EXTERNAL_INTERFACE_HPP

#include <binaryen/shell-interface.h>

#include "common/logger.hpp"
#include "extensions/extension_factory.hpp"
#include "runtime/wasm_memory.hpp"

namespace kagome::runtime {

  class RuntimeExternalInterface : public wasm::ShellExternalInterface {
   public:
    explicit RuntimeExternalInterface(
        std::shared_ptr<extensions::ExtensionFactory> extension_factory);

    wasm::Literal callImport(wasm::Function *import,
                             wasm::LiteralList &arguments) override;

    inline std::shared_ptr<WasmMemory> memory() const {
      return extension_->memory();
    }

   private:
    /**
     * Checks that the number of arguments is as expected and terminates the
     * program if it is not
     */
    void checkArguments(std::string_view extern_name,
                        size_t expected,
                        size_t actual);

    std::shared_ptr<extensions::ExtensionFactory> extension_factory_;
    std::shared_ptr<extensions::Extension> extension_;
    common::Logger logger_ = common::createLogger(kDefaultLoggerTag);

    constexpr static auto kDefaultLoggerTag = "Runtime external interface";
  };

}  // namespace kagome::runtime

#endif  // KAGOME_CORE_RUNTIME_IMPL_RUNTIME_EXTERNAL_INTERFACE_HPP
