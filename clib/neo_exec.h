/* general */
#include "stdio.h"
#define MAX_NEO_STR_LENGTH 1000
#define NEO_N 100  // WS2812灯珠的个数，这个是编译时必需确定的
#define NEO_SLOT 5  // 最多存储的procedure个数
#define NEO_PRINTF 1
#define NEO_NAME_LENGTH 32

#if NEO_PRINTF
#define neo_printf(...) printf(__VA_ARGS__)
#else
#define neo_printf(...) 
#endif

/* version 1 */
struct neo_var_v1 {
    
};
extern void neo_exec_v1_init(int slot);
extern void neo_exec_v1_draw(int slot);

/* general */

union neo_var_union {
    struct neo_var_v1 v1;
};

struct neo_color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct neo_var {
    unsigned char valid;
    int version;
    char name[NEO_NAME_LENGTH];
    char str[MAX_NEO_STR_LENGTH];  // 记录原本的字符串信息，不包括version那一行
    struct neo_color frame1[NEO_N];
    struct neo_color frame2[NEO_N];
    union neo_var_union var;  // 每个版本维护自己的一套实现变量
};

extern struct neo_color frame[NEO_N];
extern void neo_exec_init();
extern struct neo_var neo_slot[NEO_SLOT];
extern void neo_exec_load(const char* str);
extern void neo_exec_draw();
extern void neo_exec_frame_dump();
