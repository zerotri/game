#include <engine>

int main( int argc, char** argv ) {
	window_t window = NULL;
	
	pixel_buffer_t buffer = calloc(640 * 480, sizeof(int));
	memset(buffer, 0xff, 640*480*4);

	if(window_create(&window, "Testing", 640, 480)) {
		printf("Failure\n");
		return 1;
	}
	while(!window_received_quit_event(window)) {
		window_update_events(window);
		window_update_buffer(window, buffer);
	}
	window_destroy(window);
	return 0;
}
