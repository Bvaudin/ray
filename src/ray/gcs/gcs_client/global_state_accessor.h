// Copyright 2017 The Ray Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RAY_GCS_GLOBAL_STATE_ACCESSOR_H
#define RAY_GCS_GLOBAL_STATE_ACCESSOR_H

#include "service_based_gcs_client.h"

namespace ray {
namespace gcs {

/// \class GlobalStateAccessor
///
/// `GlobalStateAccessor` is used to provide synchronous interfaces to access data in GCS
/// for the language front-end (e.g., Python's `state.py`).
class GlobalStateAccessor {
 public:
  /// Constructor of GlobalStateAccessor.
  ///
  /// \param redis_address The address of GCS Redis.
  /// \param redis_password The password of GCS Redis.
  /// \param is_test Whether this accessor is used for tests.
  explicit GlobalStateAccessor(const std::string &redis_address,
                               const std::string &redis_password, bool is_test = false);

  ~GlobalStateAccessor();

  /// Connect gcs server.
  ///
  /// \return Whether the connection is successful.
  bool Connect();

  /// Disconnect from gcs server.
  void Disconnect();

  /// Get information of all jobs from GCS Service.
  ///
  /// \return All job info. To support multi-language, we serialized each JobTableData and
  /// returned the serialized string. Where used, it needs to be deserialized with
  /// protobuf function.
  std::vector<std::string> GetAllJobInfo();

 private:
  /// Whether this client is connected to gcs server.
  bool is_connected_{false};

  std::unique_ptr<ServiceBasedGcsClient> gcs_client_;

  std::unique_ptr<std::thread> thread_io_service_;
  std::unique_ptr<boost::asio::io_service> io_service_;
};

}  // namespace gcs
}  // namespace ray

#endif  // RAY_GCS_GLOBAL_STATE_ACCESSOR_H
