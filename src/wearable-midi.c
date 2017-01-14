#include "wearable-midi.h"
#include "view.h"
double bpm   = 100.0;
double bpm_T =  0.6;
int flag_timer_running = 0;
int flag_thread_priority = 0;

/* Tick Timer */
Ecore_Timer* ecore_metronome;

struct timespec tick;
struct timespec tick2;
struct timespec tock;

struct timespec start, end;

Eina_Bool doTick(void *data)
{
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
	int delta_ms = (int)(delta_us / 1000);
	start = end;
	print_debug(delta_ms, delta_ms);

	// start event
	tick2 = tick;

    //usleep(1000000);
    //usleep((useconds_t)(T * 1000));
    //usleep(1000000);
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

	//get end of the event
	clock_gettime(CLOCK_MONOTONIC_RAW, &tock);

	//get elapsed time
	uint64_t elapssed_us = (tock.tv_sec - tick2.tv_sec) * 1000000 + (tock.tv_nsec - tick2.tv_nsec) / 1000;

    uint64_t t_wait_us = (uint64_t)(bpm_T * 1000000) - elapssed_us;

    int final_wait = (int)t_wait_us;
    if(final_wait < 0) final_wait = 0;
    //print_debug(1234, final_wait);
    usleep(final_wait);

    clock_gettime(CLOCK_MONOTONIC_RAW, &tick);

	return ECORE_CALLBACK_RENEW;
}




int doTick2(void)
{
	tone_player_start(TONE_TYPE_PROP_BEEP2, SOUND_TYPE_NOTIFICATION, 40,  NULL);
	haptic_device_h hapt_dev;
	int hapt_num;
	device_haptic_get_count( &hapt_num );  // gets haptic count
	device_haptic_open(hapt_num-1, &hapt_dev);  // Opens haptic device
	haptic_effect_h hapt_eff;
	device_haptic_vibrate(hapt_dev, 100, 100, &hapt_eff); // vibrates at 100ms at 100%
	//device_haptic_close(hapt_dev);  // closes device
	return 0;
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
   //ecore_timer_interval_set(ecore_metronome, bpm_T);

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

	/* initilize timers */
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	clock_gettime(CLOCK_MONOTONIC_RAW, &tick);
	clock_gettime(CLOCK_MONOTONIC_RAW, &tick2);
	clock_gettime(CLOCK_MONOTONIC_RAW, &tock);

	ecore_metronome = ecore_timer_add(bpm_T, doTick, NULL);  // make timer
	//ecore_metronome = ecore_timer_loop_add(bpm_T, doTick, NULL);  // make timer
	ecore_timer_precision_set(0.0);
	ecore_timer_interval_set(ecore_metronome, 0.001);
/*
	double dt = ecore_timer_precision_get();
	print_debug(2222222, (int)(dt*1000));
	ecore_timer_precision_set(0.001);
	dt = ecore_timer_precision_get();
	print_debug(2222222, (int)(dt*1000));
*/
	flag_timer_running = 1;
	return 0;
}

int start_stop_timer(void)
{
	if(flag_timer_running == 1) stop_timer();
	else                        start_timer(); //start_timer_thread(); //realTimeThread(); // start_timer();
	return 0;
}

void start_timer_thread(void)
{
	pthread_t pth;  // thread identifier
	pthread_create(&pth, NULL, threadFunc, &bpm_T);  // create thread and send bpm_T
	eprint("started Timer Thread");

    int i = 0;
	while(1)
	{
		print_debug(i,i);
		usleep(1000000);
		i++;
	}
    eprint("exiting Timer thread");
	pthread_join(pth,NULL); // wait for thread to terminate
}

void realTimeThread(void)
{
	struct timespec tv;
	struct timespec t_sleep;
	t_sleep.tv_nsec = 1;
	t_sleep.tv_sec = 1;

	//t_sleep.tv_sec = 0;
	//t_sleep.tv_
	gettimeofday(&tv,NULL);

	unsigned long tick_in_micros = 1000000000 * tv.tv_sec + tv.tv_nsec;
	unsigned long tock_in_micros = 1000000000 * tv.tv_sec + tv.tv_nsec;
	double dt = (double)(tock_in_micros - tick_in_micros);
	while(1)
	{
		doTick2();
		/*
		while(dt < bpm_T)
		{
			gettimeofday(&tv,NULL);
			tock_in_micros = 1000000000 * tv.tv_sec + tv.tv_nsec;
			dt = (double)(tock_in_micros - tick_in_micros);
			sleep(1);
		}
		*/
		//usleep(1500000);
		nanosleep(&t_sleep,NULL);
	//	print_debug((int)tick_in_micros, (int)(tock_in_micros));
	//	tick_in_micros = tock_in_micros;
	}

}


void *threadFunc(double *arg)
{
	eprint("1 in Timer Thread");
	double T = (double)*arg;
	bpm_T = T;
	eprint("2 in Timer Thread");
	realTimeThread();

	while(1) usleep(1000);
	return NULL;
}
