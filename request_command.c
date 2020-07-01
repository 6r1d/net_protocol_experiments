#include <stdio.h>
#include "dyad/src/dyad.h"

static void onConnect(dyad_Event *e) {
  printf("connected: %s\n", e->msg);
  dyad_writef(e->stream, "uptime\r\n");
}

static void onData(dyad_Event *e) {
  printf("%s", e->data);
  dyad_end(e->stream);
}

int main(void) {
  dyad_init();

  dyad_Stream *s = dyad_newStream();
  dyad_addListener(s, DYAD_EVENT_CONNECT, onConnect, NULL);
  dyad_addListener(s, DYAD_EVENT_DATA,    onData,    NULL);
  dyad_connect(s, "localhost", 4729);

  while (dyad_getStreamCount() > 0) {
    dyad_update();
  }

  dyad_shutdown();
  return 0;
}
