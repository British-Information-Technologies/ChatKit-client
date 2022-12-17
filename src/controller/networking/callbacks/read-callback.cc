#include "read-callback.h"

#include <event2/buffer.h>
#include <event2/event.h>
#include <string.h>

#include "cpp-chat-client/model/message-functionality/message.h"
#include "cpp-chat-client/model/networking/connection.h"
#include "callback-collection.h"

using namespace model_message_functionality;
using namespace controller_networking_callbacks;
using namespace model_networking;
using namespace std;

#define MAX_LINE 16384

void controller_networking_callbacks::ReadCallback(struct bufferevent *bev,
                                                   void *ctx) {
  struct CallbackCollection *items = (CallbackCollection *)ctx;
  struct evbuffer *input, *output;
  char *tmp_line;
  size_t n;
  int i;

  input = bufferevent_get_input(bev);
  output = bufferevent_get_output(bev);

  while ((tmp_line = evbuffer_readln(input, &n, EVBUFFER_EOL_CRLF))) {
    string line = tmp_line;
    unique_ptr<Message> message = items->connection->TranslateMessage(line);

    string type = message->ToJson()["type"];

    if (type.compare("UserMessage") == 0) {
      string from = message->ToJson()["from"];
      string content = message->ToJson()["content"];

      auto friend_node = items->model->GetFriend(from);

      // TODO: add message to friend node history

      // TODO: Create chatbox stacks with user uuid in id of stack.
      // At the moment just fake this, should pass from as the 2nd parameter.
      items->view->AddMessageToChatBox(content, "message");

    } else {
      std::cout << message->ToString() << std::endl;
    }

    free(tmp_line);
  }

  if (evbuffer_get_length(input) >= MAX_LINE) {
    /* Too long; just process what there is and go on so that the buffer
     * doesn't grow infinitely long. */
    char buf[1024];
    while (evbuffer_get_length(input)) {
      int n = evbuffer_remove(input, buf, sizeof(buf));
      // for (i = 0; i < n; ++i) buf[i] = rot13_char(buf[i]);
      // evbuffer_add(output, buf, n);
    }
    // evbuffer_add(output, "\n", 1);
  }
}