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

#include "UDPStream.hpp"

namespace oatpp { namespace ssdp {

data::stream::DefaultInitializedContext UDPStream::DEFAULT_CONTEXT(data::stream::StreamType::STREAM_INFINITE);

v_io_size UDPStream::write(const void *buff, v_buff_size count, async::Action& action) {
  // TODO - create a single UDP-packet.
  throw std::runtime_error("[oatpp::ssdp::UDPStream::write()]: Error. Not Implemented!!!");
}

v_io_size UDPStream::read(void *buff, v_buff_size count, async::Action& action) {
  // TODO - read a single UDP-packet to buffer.
  // If there is data left in the buffer - read from buffer.
  // If no data left - read the next UDP-packet.
  // return the oatpp::IOError::RETRY_READ between packets.
  throw std::runtime_error("[oatpp::ssdp::UDPStream::read()]: Error. Not Implemented!!!");
}

void UDPStream::setOutputStreamIOMode(data::stream::IOMode ioMode) {
  m_mode = ioMode;
}

data::stream::IOMode UDPStream::getOutputStreamIOMode() {
  return m_mode;
}

data::stream::Context& UDPStream::getOutputStreamContext() {
  return DEFAULT_CONTEXT;
}

void UDPStream::setInputStreamIOMode(data::stream::IOMode ioMode) {
  m_mode = ioMode;
}

data::stream::IOMode UDPStream::getInputStreamIOMode() {
  return m_mode;
}

data::stream::Context& UDPStream::getInputStreamContext() {
  return DEFAULT_CONTEXT;
}

}}
