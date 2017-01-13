#include "wearable-midi.h"
#include "view.h"
double bpm   = 100.0;
double bpm_T =  0.6;
int flag_timer_running = 0;
int flag_thread_priority = 0;

/* Tick Timer */
Ecore_Timer* ecore_metronome;

Eina_Bool doTick(void *data)
{
	if(flag_thread_priority == 0)
	{
		int which = PRIO_PROCESS;
		int priority = -20;
		id_t pid;
		int ret;
		pid = getpid();
		ret = setpriority(which, pid, priority);
        flag_thread_priority = 1;
	}
	//tone_player_start(TONE_TYPE_PROP_BEEP, SOUND_TYPE_SYSTEM, 100,  NULL);
	//tone_player_start(TONE_TYPE_PROP_BEEP2, SOUND_TYPE_SYSTEM, 40,  NULL);
	tone_player_start(TONE_TYPE_PROP_BEEP2, SOUND_TYPE_NOTIFICATION, 40,  NULL);
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
	//doTick(NULL);
	if (ev->direction == EEXT_ROTARY_DIRECTION_CLOCKWISE)
   {
	  bpm = bpm + 1.0;
   }
   else
   {
	  bpm = bpm - 1.0;
   }
   if(bpm < 1.0) bpm = 1.0;
   bpm_T = 60.0 / bpm;
   ecore_timer_interval_set(ecore_metronome, bpm_T);
   print_debug((int)bpm, (int)bpm);
   return EINA_FALSE;
}


int stop_timer(void)
{	int which = PRIO_PROCESS;
	int priority = 20;
	id_t pid;
	int ret;
	pid = getpid();
	ret = setpriority(which, pid, priority);

	ecore_timer_del(ecore_metronome);
	flag_timer_running = 0;
	flag_thread_priority = 0;
	return 0;
}

int start_timer(void)
{
	int which = PRIO_PROCESS;
	int priority = -20;
	id_t pid;
	int ret;
	pid = getpid();
	ret = setpriority(which, pid, priority);

	flag_thread_priority = 0;


	ecore_metronome = ecore_timer_add(bpm_T, doTick, NULL);  // make timer
	flag_timer_running = 1;
	return 0;
}

int start_stop_timer(void)
{


	if(flag_timer_running == 1) stop_timer();
	else                        start_timer();
	return 0;
}
