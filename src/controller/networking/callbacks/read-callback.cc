#include "read-callback.h"

#include <event2/buffer.h>
#include <event2/event.h>
#include <string.h>

#include "../../../model/message-functionality/message.h"
#include "../../../model/networking/connection.h"

using namespace model_message_functionality;
using namespace controller_networking_callbacks;
using namespace model_networking;
using namespace std;

#define MAX_LINE 16384

void controller_networking_callbacks::ReadCallback(struct bufferevent *bev,
                                                   void *ctx) {
  Connection *connection = (Connection *)ctx;
  struct evbuffer *input, *output;
  char *tmp_line;
  size_t n;
  int i;

  input = bufferevent_get_input(bev);
  output = bufferevent_get_output(bev);

  while ((tmp_line = evbuffer_readln(input, &n, EVBUFFER_EOL_CRLF))) {
    string line = tmp_line;
    unique_ptr<Message> message = connection->TranslateMessage(line);

    evbuffer_add(output, tmp_line, n);
    evbuffer_add(output, "\n", 1);
    free(tmp_line);
  }

  if (evbuffer_get_length(input) >= MAX_LINE) {
    /* Too long; just process what there is and go on so that the buffer
     * doesn't grow infinitely long. */
    char buf[1024];
    while (evbuffer_get_length(input)) {
      int n = evbuffer_remove(input, buf, sizeof(buf));
      // for (i = 0; i < n; ++i) buf[i] = rot13_char(buf[i]);
      evbuffer_add(output, buf, n);
    }
    evbuffer_add(output, "\n", 1);
  }
}