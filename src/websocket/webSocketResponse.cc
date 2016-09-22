// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "webSocketResponse.h"
#include <muduo/net/Buffer.h>

#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

void webSocketResponse::appendToBuffer(Buffer* output) const
{
  char buf[32];
  snprintf(buf, sizeof buf, "HTTP/1.1 %d ", statusCode_);
  //output->append(buf);
  output->append("HTTP/1.1 101 Web Socket Protocol Handshake\r\n");
  output->append(statusMessage_);
  output->append("\r\n");

  if (closeConnection_)
  {
    output->append("Connection: close\r\n");
  }
  else
  {
    snprintf(buf, sizeof buf, "Content-Length: %zd\r\n", body_.size());
    output->append(buf);
    output->append("Connection: Keep-Alive\r\n");
  }

  for (std::map<string, string>::const_iterator it = headers_.begin();
       it != headers_.end();
       ++it)
  {
    output->append(it->first);
    output->append(": ");
    output->append(it->second);
    output->append("\r\n");
    //printf("%s:%s\n", it->first,it->second);
    std::cout<<it->first<<":"<<it->second<<std::endl;
  }

  output->append("\r\n");
  output->append(body_);
}
