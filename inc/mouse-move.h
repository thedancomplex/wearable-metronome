#include <Ecore.h>
#include <Ecore_Evas.h>

/*
static struct view_info {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *img;
	Evas_Coord width;
	Evas_Coord height;
	cairo_t *cairo;
	cairo_surface_t *surface;
	unsigned char *pixels;


	///* Variable for start drawing state
	int touch_drawing_start;

	///* Variables for path start and end point
	int cur_x;
	int cur_y;
	int prev_x;
	int prev_y;

}  s_info = {
	.win = NULL,
	.conform = NULL,
};
*/

void mouse_down_cb(void *data, Evas *e, Evas_Object *obj, void *event_info);
void mouse_move_cb(void *data, Evas *e, Evas_Object *obj, void *event_info);
void mouse_up_cb(void *data, Evas *e, Evas_Object *obj, void *event_info);
//static Eina_Bool _key_down_cb(void *data __UNUSED__, int type __UNUSED__, void *ev);
Eina_Bool _key_down_cb(void *data , int type , void *ev);
Eina_Bool _exit_down_cb(void *data, int type, void *ev);
