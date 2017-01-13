#include <tone_player.h>
#include <device/haptic.h>
#include <Ecore.h>
#include <efl_extension.h>
#include <efl_extension_events.h>
#include <efl_util.h>
Eina_Bool doTick(void *data);
Eina_Bool _rotary_handler_cb(void *data, Eext_Rotary_Event_Info *ev);
