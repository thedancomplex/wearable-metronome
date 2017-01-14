#include "metronome.h"
#include "metronome-all.h"

int prev_x = 0;
int prev_y = 0;
int cur_x = 0;
int cur_y = 0;
int touch_drawing_start = 0;

Eina_Bool _exit_down_cb(void *data, int type, void *ev)
{
	exit(0);
	return ECORE_CALLBACK_PASS_ON;
}




Eina_Bool _key_down_cb(void *data, int type, void *ev)
{
	//Evas_Event_Mouse_Down *ev = (Evas_Event_Mouse_Down *) event_info;

	/* Change the variable's state to enable start drawing */
	if (touch_drawing_start == 0)
		touch_drawing_start = 1;

	/* Get previous position from Evas_Event_Mouse_Down event */
	//prev_x = ev->canvas.x;
	//prev_y = ev->canvas.y;


	//print_debug((int)ev->canvas.x,(int)ev->canvas.y);
	eprint("Button Pressed");
//	send_udp((int)ev->canvas.x,(int)ev->canvas.y);

	start_stop_timer();
	//start_timer();
	//doTick();



	//send_udp(1,2);
	return ECORE_CALLBACK_PASS_ON;
}




void mouse_down_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	Evas_Event_Mouse_Down *ev = (Evas_Event_Mouse_Down *) event_info;

	/* Change the variable's state to enable start drawing */
	if (touch_drawing_start == 0)
		touch_drawing_start = 1;

	/* Get previous position from Evas_Event_Mouse_Down event */
	prev_x = ev->canvas.x;
	prev_y = ev->canvas.y;


	print_debug((int)ev->canvas.x,(int)ev->canvas.y);
//	send_udp((int)ev->canvas.x,(int)ev->canvas.y);

	start_stop_timer();
	//start_timer();
	//doTick();



	//send_udp(1,2);
}


/* When user touch off on screen, EVAS_CALLBACK_MOUSE_UP event occurred
	At that time this mouse_up_cb function callback called
	In this function, get and set the touch end position
	Can draw a line from down event position to up event position */
void mouse_up_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	Evas_Event_Mouse_Up *ev = (Evas_Event_Mouse_Up *) event_info;

	/* Get current position from Evas_Event_Mouse_Up event */
	cur_x = ev->canvas.x;
	cur_y = ev->canvas.y;

//	send_udp((int)ev->canvas.x,(int)ev->canvas.y);
	//print_debug((int)ev->canvas.x,(int)ev->canvas.y);
	tone_player_stop(NULL);

	//stop_timer();

}

/* When user touch and move on screen, EVAS_CALLBACK_MOUSE_MOVE event occurred
	At that time this mouse_move_cb function callback called
	In this function, can get the mouse moved from some position to other position
	And set the moved position with inputs */
void mouse_move_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	Evas_Event_Mouse_Move *ev = (Evas_Event_Mouse_Move *)event_info;

	/* Get touch moved position values */
	cur_x = ev->cur.canvas.x;
	cur_y = ev->cur.canvas.y;
	prev_x = ev->prev.canvas.x;
	prev_y = ev->prev.canvas.y;

	//print_debug((int)s_info.cur_x, (int)s_info.cur_y);
//	send_udp((int)s_info.cur_x, (int)s_info.cur_y);
}
