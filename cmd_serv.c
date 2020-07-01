#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dyad.h"

time_t * start_time, current_time;

/* Returns program uptime in seconds as a double value */
double get_uptime() {
    time(&current_time);
    double interval = difftime(current_time, start_time);
    return interval;
}

static void onData(dyad_Event *e) {
  if (strcmp(e->data, "uptime") == 1) {
    dyad_writef(e->stream, "%f\n\r", get_uptime());
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
  time(&start_time);

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
