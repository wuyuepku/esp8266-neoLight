#include <stdio.h>
#include "neo_exec.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "svpng.inc"
char buf[8192];
#define TIME_INTV 20  // 20ms
#define NUM_FRAME 100
#define UPSAMPLE 10
unsigned char rgb[NUM_FRAME * NEO_N * 3 * UPSAMPLE * UPSAMPLE], *p;

void draw_a_frame(struct neo_color *frame) {
    int i,j,k;
    for (j=0; j<UPSAMPLE; ++j) {
        for (i=0; i<NEO_N; ++i) {
            for (k=0; k<UPSAMPLE; ++k) {
                *p++ = frame[i].r;
                *p++ = frame[i].g;
                *p++ = frame[i].b;
            }
        }
    }
}

void draw_white_lines() {
    int i,j,k;
    for (i=0; i<NUM_FRAME; ++i) {
        for (j=0; j<UPSAMPLE*NEO_N; ++j) {
            k = 3 * (UPSAMPLE*NEO_N*i*UPSAMPLE + j);
            rgb[k] = rgb[k+1] = rgb[k+2] = 255;
        }
    }
}

int main() {
    int i, fd;

    // 初始化PNG输出
    p = rgb;
    FILE *fp = fopen("rgb.png", "wb");
    neo_exec_init();

    for (i=0; i<NUM_FRAME; ++i) {

        if (i == 0) {
            fd = open("../test1.json.txt", O_RDONLY);
            buf[read(fd, buf, sizeof(buf))] = '\0';
            neo_exec_load(buf);
            close(fd);
        }

        if (i == 30) {
            fd = open("../test2.json.txt", O_RDONLY);
            buf[read(fd, buf, sizeof(buf))] = '\0';
            neo_exec_load(buf);
            close(fd);
        }
        
        if (i == 50) {
            fd = open("../test3.json.txt", O_RDONLY);
            buf[read(fd, buf, sizeof(buf))] = '\0';
            neo_exec_load(buf);
            close(fd);
        }

        neo_exec_draw(TIME_INTV);
        draw_a_frame(frame);
        // draw_a_frame(neo_slot[0].frame1);
        // neo_exec_frame_dump(neo_slot[0].frame1);
    }

    draw_white_lines();
    svpng(fp, NEO_N * UPSAMPLE, NUM_FRAME * UPSAMPLE, rgb, 0);
    fclose(fp);
}

