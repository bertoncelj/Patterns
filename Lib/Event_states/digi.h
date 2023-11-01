#ifndef _digi_h_
#define _digi_h_

typedef struct digi_watch *digi_watch_p;

digi_watch_p create_watch(void);

void start_watch(digi_watch_p instance);

void stop_watch(digi_watch_p instance);

void destroy_watch(digi_watch_p instace);

#endif
