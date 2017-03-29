#include <engine>

int draw(pixel_buffer_t buffer);
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

		draw(buffer);

		window_update_buffer(window, buffer);
	}
	window_destroy(window);
	return 0;
}

int draw(pixel_buffer_t buffer) {
	//
	// Example code taken from:
	// http://sol.gfxile.net/gp/ch02.html
	//

	// Ask SDL for the time in milliseconds
	int tick = SDL_GetTicks();

	// Declare a couple of variables
	int i, j, yofs, ofs, pitch=640*4;

	// Draw to screen
	yofs = 0;
	for (i = 0; i < 480; i++)
	{
		for (j = 0, ofs = yofs; j < 640; j++, ofs++)
		{
			((unsigned int*)buffer)[ofs] = i * i + j * j + tick;
		}
		yofs += pitch / 4;
	}
	return 0;
}