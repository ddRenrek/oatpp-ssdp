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

#include "Message.hpp"

namespace oatpp { namespace ssdp {

data::stream::DefaultInitializedContext Message::DEFAULT_CONTEXT(data::stream::StreamType::STREAM_FINITE);

Message::Message(const std::shared_ptr<base::StrBuffer>& incomingData)
  : m_mode(data::stream::IOMode::BLOCKING)
  , m_inBuffer(incomingData)
  , m_in(incomingData, incomingData->getData(), incomingData->getSize())
{}

void Message::flush() {
  oatpp::String data = m_out.toString();
  OATPP_LOGD("Message", "Send '%s'", data->c_str());
}

v_io_size Message::write(const void *buff, v_buff_size count, async::Action& action) {
  if (m_out.getCurrentPosition() + count > MAX_MESSAGE_SIZE) {
    count = MAX_MESSAGE_SIZE - m_out.getCurrentPosition();
  }
  return m_out.write(buff, count, action);
}

v_io_size Message::read(void *buff, v_buff_size count, async::Action& action) {
  return m_in.read(buff, count, action);
}

void Message::setOutputStreamIOMode(data::stream::IOMode ioMode) {
  m_mode = ioMode;
}

data::stream::IOMode Message::getOutputStreamIOMode() {
  return m_mode;
}

data::stream::Context& Message::getOutputStreamContext() {
  return DEFAULT_CONTEXT;
}

void Message::setInputStreamIOMode(data::stream::IOMode ioMode) {
  m_mode = ioMode;
}

data::stream::IOMode Message::getInputStreamIOMode() {
  return m_mode;
}

data::stream::Context& Message::getInputStreamContext() {
  return DEFAULT_CONTEXT;
}

}}
