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

#ifndef oatpp_ssdp_SsdpMessage_hpp
#define oatpp_ssdp_SsdpMessage_hpp

#include "oatpp/core/provider/Provider.hpp"

#include "oatpp/core/data/stream/BufferStream.hpp"
#include "UdpStream.hpp"

namespace oatpp { namespace ssdp {

/**
 * Class Adaptor, representing a single SSDP message.
 */
class SsdpMessage : public base::Countable, public data::stream::IOStream {
public:
  static constexpr v_buff_size MAX_MESSAGE_SIZE = 65507;
private:
  provider::ResourceHandle<data::stream::IOStream> m_inStream;
  data::stream::BufferOutputStream m_out;
public:

  /**
   * Constructor.
   * @param incomingStream
   */
  SsdpMessage(const provider::ResourceHandle<data::stream::IOStream>& incomingStream);

  /**
   * This flushes the buffered data to any other stream.
   */
  v_io_size flushToStream(OutputStream* stream);

  /**
   * This flushes the buffered data to the given input stream
   */
  v_io_size flush();

  /**
   * Implementation of &id:oatpp::data::stream::IOStream::write;.
   * @param buff - buffer containing data to write.
   * @param count - bytes count you want to write.
   * @param action - async specific action. If action is NOT &id:oatpp::async::Action::TYPE_NONE;, then
   * caller MUST return this action on coroutine iteration.
   * @return - actual amount of bytes written. See &id:oatpp::v_io_size;.
   */
  v_io_size write(const void *buff, v_buff_size count, async::Action& action) override;

  /**
   * Implementation of &id:oatpp::data::stream::IOStream::read;.
   * @param buff - buffer to read data to.
   * @param count - buffer size.
   * @param action - async specific action. If action is NOT &id:oatpp::async::Action::TYPE_NONE;, then
   * caller MUST return this action on coroutine iteration.
   * @return - actual amount of bytes read. See &id:oatpp::v_io_size;.
   */
  v_io_size read(void *buff, v_buff_size count, async::Action& action) override;

  /**
   * Set OutputStream I/O mode.
   * @param ioMode
   */
  void setOutputStreamIOMode(oatpp::data::stream::IOMode ioMode) override;

  /**
   * Set OutputStream I/O mode.
   * @return
   */
  oatpp::data::stream::IOMode getOutputStreamIOMode() override;

  /**
   * Get output stream context.
   * @return - &id:oatpp::data::stream::Context;.
   */
  oatpp::data::stream::Context& getOutputStreamContext() override;

  /**
   * Set InputStream I/O mode.
   * @param ioMode
   */
  void setInputStreamIOMode(oatpp::data::stream::IOMode ioMode) override;

  /**
   * Get InputStream I/O mode.
   * @return
   */
  oatpp::data::stream::IOMode getInputStreamIOMode() override;

  /**
   * Get input stream context. <br>
   * @return - &id:oatpp::data::stream::Context;.
   */
  oatpp::data::stream::Context& getInputStreamContext() override;

};

}}

#endif //oatpp_ssdp_SsdpMessage_hpp
