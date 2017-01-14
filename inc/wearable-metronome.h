#include <tone_player.h>
#include <device/haptic.h>
#include <Ecore.h>
#include <efl_extension.h>
#include <efl_extension_events.h>
#include <efl_util.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>
#include <tizen.h>
#include <cairo.h>


Eina_Bool doTick(void *data);
int doTick2(void);
Eina_Bool _rotary_handler_cb(void *data, Eext_Rotary_Event_Info *ev);
int start_timer(void);
int stop_timer(void);
int start_stop_timer(void);

void start_timer_thread(void);
void *threadFunc(double *arg);
void realTimeThread(void);

