#include <gtest/gtest.h>

#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <memory>
#include <event2/event.h>

#include "model/networking/utility/buffer-reader.h"
#include "model/networking/utility/buffer-writer.h"

#define IP "localhost"
#define PORT "3490"

using namespace model;

class BufferWriterTest : public ::testing::Test {
  protected:
    int fd;

    std::shared_ptr<struct event_base> base;
    
    std::shared_ptr<bufferevent> bev;

 protected:
  void SetUp() override {
    base.reset(event_base_new(),
      [](event_base *b){
        event_base_loopexit(b, NULL);
        event_base_free(b);
      }
    );

    bev.reset(bufferevent_socket_new(base.get(), -1, BEV_OPT_CLOSE_ON_FREE),
      [](bufferevent *b){
        bufferevent_free(b);
      }
    );
    
    fd = open("tmp_buffer_file_test.txt", O_WRONLY | O_RDONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if (fd == -1) {
      std::cout << "ERR: file error! fd = " << fd << std::endl;
    }
    
    bufferevent_setfd(bev.get(), fd);

    bufferevent_setcb(bev.get(), nullptr, nullptr, nullptr, nullptr);
    
    bufferevent_enable(bev.get(), EV_READ|EV_WRITE);
  }

  void TearDown() override {
    close(fd);
  }
};

TEST_F(BufferWriterTest, SendAndReadManyMessagesTest) {
  std::string message("this is a test message");

  for (int i = 0; i < 1000; ++i) {
    WriteBufferLine(bev, message);
  }

  for (int i = 0; i < 1000; ++i) {
    std::string result = ReadBufferLine(bev);
    ASSERT_EQ(message, result);
  }
}