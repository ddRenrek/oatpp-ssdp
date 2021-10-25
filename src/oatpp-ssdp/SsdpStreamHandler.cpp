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

#include "SsdpStreamHandler.hpp"

#include "SsdpMessage.hpp"

namespace oatpp { namespace ssdp {

void SsdpStreamHandler::onTaskStart(const provider::ResourceHandle<data::stream::IOStream>& connection) {
  (void) connection;
  // TODO - manage connection.
}

void SsdpStreamHandler::onTaskEnd(const provider::ResourceHandle<data::stream::IOStream>& connection) {
  (void) connection;
  // TODO - manage connection.
}

SsdpStreamHandler::SsdpStreamHandler(const std::shared_ptr<web::server::HttpProcessor::Components>& components)
  : m_components(components)
{}

std::shared_ptr<SsdpStreamHandler> SsdpStreamHandler::createShared(const std::shared_ptr<web::server::HttpRouter>& router){
  return std::make_shared<SsdpStreamHandler>(router);
}

void SsdpStreamHandler::setErrorHandler(const std::shared_ptr<web::server::handler::ErrorHandler>& errorHandler){
  m_components->errorHandler = errorHandler;
  if(!m_components->errorHandler) {
    m_components->errorHandler = web::server::handler::DefaultErrorHandler::createShared();
  }
}

void SsdpStreamHandler::addRequestInterceptor(const std::shared_ptr<web::server::interceptor::RequestInterceptor>& interceptor) {
  m_components->requestInterceptors.push_back(interceptor);
}

void SsdpStreamHandler::handleConnection(const provider::ResourceHandle<oatpp::data::stream::IOStream>& connection,
                                         const std::shared_ptr<const ParameterMap>& params)
{

  (void)params;

  connection.object->setOutputStreamIOMode(oatpp::data::stream::IOMode::BLOCKING);
  connection.object->setInputStreamIOMode(oatpp::data::stream::IOMode::BLOCKING);

  // This can be executed in a different thread.
  // Thread begin

  auto message = std::make_shared<SsdpMessage>(connection);

  message->setOutputStreamIOMode(oatpp::data::stream::IOMode::BLOCKING);
  message->setInputStreamIOMode(oatpp::data::stream::IOMode::BLOCKING);

  provider::ResourceHandle<oatpp::data::stream::IOStream> messageHandle(
    message,
    connection.invalidator
  );

  web::server::HttpProcessor::Task httpTask(m_components, messageHandle, this);
  httpTask.run();

  // or just message->flush() since we created the message with a valid connection stream
  message->flushToStream(connection.object.get());

  // Thread end

}

void SsdpStreamHandler::stop() {
  // DO NOTHING
}

}}
