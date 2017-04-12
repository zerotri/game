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

    const char* file = "test.shm";
    int buffer_size = kScreenWidth*kScreenHeight*sizeof(int);

    int fd = shm_open(file , O_RDWR, 0666);

    pixel_buffer_t buffer = mmap(0, buffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (buffer == MAP_FAILED) {
        printf("Map failed\n");
        return -1;
    }

    memset(buffer, 0xff, buffer_size);

    while(1) {
        draw(buffer);
        SDL_Delay(16);
    }
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
    int i, j, yofs, ofs, pitch=kScreenWidth*4;

    // Draw to screen
    yofs = 0;
    for (i = 0; i < kScreenWidth; i++)
    {
        for (j = 0, ofs = yofs; j < kScreenHeight; j++, ofs++)
        {
            ((unsigned int*)buffer)[ofs] = i * i + j * j + tick;
        }
        yofs += pitch / 4;
    }
    return 0;
}