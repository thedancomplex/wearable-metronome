#include "wearable-midi.h"
#include "view.h"
double bpm = 100.0;

Eina_Bool doTick(void *data)
{
	//tone_player_start(TONE_TYPE_PROP_BEEP, SOUND_TYPE_SYSTEM, 100,  NULL);
	tone_player_start(TONE_TYPE_PROP_BEEP2, SOUND_TYPE_SYSTEM, 100,  NULL);
	haptic_device_h hapt_dev;
	int hapt_num;
	device_haptic_get_count( &hapt_num );  // gets haptic count
	device_haptic_open(hapt_num-1, &hapt_dev);  // Opens haptic device
	haptic_effect_h hapt_eff;
	device_haptic_vibrate(hapt_dev, 100, 100, &hapt_eff); // vibrates at 100ms at 100%
	//device_haptic_close(hapt_dev);  // closes device
	return ECORE_CALLBACK_RENEW;
}

Eina_Bool _rotary_handler_cb(void *data, Eext_Rotary_Event_Info *ev)
{
	doTick(NULL);
	if (ev->direction == EEXT_ROTARY_DIRECTION_CLOCKWISE)
   {
	  bpm = bpm + 1.0;
   }
   else
   {
	  bpm = bpm - 1.0;
   }

	print_debug((int)bpm, (int)bpm);
	return EINA_FALSE;
}

