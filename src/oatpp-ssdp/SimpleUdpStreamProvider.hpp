/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *                         Benedikt-Alexander Mokroß <oatpp@bamkrs.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#ifndef oatpp_ssdp_SimpleUdpStreamProvider_hpp
#define oatpp_ssdp_SimpleUdpStreamProvider_hpp

#include "SsdpMessage.hpp"
#include "oatpp/network/ConnectionProvider.hpp"

namespace oatpp { namespace ssdp {

/**
 * Simple implementation of provider of UDP streams.
 */
class SimpleUdpStreamProvider : public network::ServerConnectionProvider {
private:

  class Invalidator : public provider::Invalidator<data::stream::IOStream> {
  public:
    void invalidate(const std::shared_ptr<data::stream::IOStream>& stream);
  };

private:
  v_io_handle instantiateServer();
protected:
  std::shared_ptr<Invalidator> m_invalidator;
  v_uint16 m_port;
  v_io_handle m_handle;
  std::atomic<bool> m_closed;
public:

  /**
   * Constructor.
   * @param port
   */
  explicit SimpleUdpStreamProvider(v_uint16 port);

  /**
   * Close accept-socket.
   */
  void stop() override;

  /**
   * Get incoming connection.
   * @return &id:oatpp::data::stream::IOStream;.
   */
  provider::ResourceHandle<data::stream::IOStream> get() override;

  /**
   * No need to implement this.<br>
   * For Asynchronous IO in oatpp it is considered to be a good practice
   * to accept connections in a seperate thread with the blocking accept()
   * and then process connections in Asynchronous manner with non-blocking read/write.
   * <br>
   * *It may be implemented later*
   */
  async::CoroutineStarterForResult<const provider::ResourceHandle<data::stream::IOStream>&> getAsync() override {
    /*
     *  No need to implement this.
     *  For Asynchronous IO in oatpp it is considered to be a good practice
     *  to accept connections in a seperate thread with the blocking accept()
     *  and then process connections in Asynchronous manner with non-blocking read/write
     *
     *  It may be implemented later
     */
    throw std::runtime_error("[oatpp::ssdp::UdpStreamProvider::getAsync()]: Error. Not implemented.");
  }

};

}}

#endif // oatpp_ssdp_SimpleUdpStreamProvider_hpp
