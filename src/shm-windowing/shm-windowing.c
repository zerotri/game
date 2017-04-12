#include <engine>


#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

enum {
    kScreenWidth = 256,
    kScreenHeight = 256
};

int draw(pixel_buffer_t buffer);
int main( int argc, char** argv ) {
    window_t window = NULL;

    const char* shm_file = "test.shm";
    int buffer_size = kScreenWidth*kScreenHeight*sizeof(int);

    int shm_fd = shm_open(shm_file, O_CREAT | O_RDONLY, 0666);
    if (shm_fd == -1) {
        printf("shared memory failed\n");
        exit(-1);
    }

    ftruncate(shm_fd, buffer_size);

    pixel_buffer_t primary_buffer = calloc( kScreenWidth*kScreenHeight, sizeof(int) );

    pixel_buffer_t shared_buffer = mmap(0,buffer_size, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shared_buffer == MAP_FAILED) {
        printf("Map failed\n");
        exit(-1);
    }

    if(window_create(&window, "Testing", kScreenWidth, kScreenHeight)) {
        printf("Failure\n");
        return 1;
    }
    while(!window_received_quit_event(window)) {
        window_update_events(window);

        memcpy(primary_buffer, shared_buffer, buffer_size);
        draw(primary_buffer);

        window_update_buffer(window, primary_buffer);

        SDL_Delay(16);
    }
    window_destroy(window);

    if (shm_unlink(shm_file) == -1) {
        printf("Error removing %s\n",shm_file);
        exit(-1);
    }
    return 0;
}

void draw_pixel(pixel_buffer_t buffer, int x, int y) {
    ((unsigned int*)buffer)[y * kScreenWidth + x] = 0xffffffff;
}

int draw(pixel_buffer_t buffer) {

    draw_pixel(buffer, 32, 32);
    draw_pixel(buffer, 32, 33);
    draw_pixel(buffer, 33, 32);
    draw_pixel(buffer, 33, 33);
    return 0;
}