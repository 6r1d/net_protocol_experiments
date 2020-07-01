#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dyad.h"

clock_t start_time;

static void onData(dyad_Event *e) {
  if (strcmp(e->data, "uptime") == 1) {
    double time_spent = (double)(clock() - start_time);
    dyad_writef(e->stream, "%f", time_spent);
  } else {
    dyad_write(e->stream, e->data, e->size);
  }
}

static void onAccept(dyad_Event *e) {
  dyad_addListener(e->remote, DYAD_EVENT_DATA, onData, NULL);
  dyad_writef(e->remote, "connection successful\r\n");
}

static void onError(dyad_Event *e) {
  printf("server error: %s\n", e->msg);
}

int main(void) {
  /* Used in uptime */
  start_time = clock();

  /* Init dyad */
  dyad_Stream *s;
  dyad_init();

  s = dyad_newStream();
  dyad_addListener(s, DYAD_EVENT_ERROR,  onError,  NULL);
  dyad_addListener(s, DYAD_EVENT_ACCEPT, onAccept, NULL);
  dyad_listen(s, 4729);

  while (dyad_getStreamCount() > 0) {
    dyad_update();
  }

  return 0;
}
