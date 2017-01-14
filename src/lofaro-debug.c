#include "metronome.h"
#include "metronome-all.h"



void print_debug(int x, int y)
{
	/* debug location */
	char debug_buff[256];
	snprintf(debug_buff, 256, "x = %d  y = %d", x, y);


	dlog_print(DLOG_ERROR, LOG_TAG, "*******dan test %d", 42);
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, debug_buff);
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
}

void print_debug_double(double x)
{
	/* debug location */
	char debug_buff[256];
	snprintf(debug_buff, 256, "x = %f ", x);


	dlog_print(DLOG_ERROR, LOG_TAG, "*******dan test %d", 42);
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, debug_buff);
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
}

void error(char *msg) {

	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, msg);
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
    //exit(0);
}

void eprint(char *msg) {

	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, msg);
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
	dlog_print(DLOG_ERROR, LOG_TAG, "************************************************");
    //exit(0);
}

