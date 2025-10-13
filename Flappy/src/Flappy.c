#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/system.h>
#include <stdlib.h>

#define SCREEN_W 383
#define SCREEN_H 216
#define BLOCK 25
#define JUMP_POWER 4
#define GRAVITY 2
#define PILLAR_W 10
#define PILLAR_H 85

// Prototypes
int jump(int *y, int *springmulti);
void draw(int *x, int *y, int *px, int *py);
int gravity(int *y, int *valtijd);

int main(void) {
    int x = 50;
    int y = 0;
    int px = 380;
    int py = 50;
    int last = 1;
	int valtijd = 0;
	int springtijd = 0;
	int springmulti = 4;
	int time = 0;

    while (1) {
        CMT_Delay_100micros(200);
		time++;

		if (time %= 5) px -= 6;

		if (px <= 0 + PILLAR_W) {
			px = 382;
			py = rand() % (SCREEN_H - PILLAR_H);
		}

		if (springtijd == 0) {
			valtijd++;
        	gravity(&y, &valtijd);
		}
		if (springtijd <= 3 && springtijd >= 1) {
			jump(&y, &springmulti);
			springtijd++;
			springmulti--;
		}
		else {
			springtijd = 0;
			springmulti = 4;
		}
        if (PRGM_GetKey() == 28 && last == 1) {
			springtijd++;
            jump(&y, &springmulti);
            last = 0;
			valtijd = 0;
        }
        else if (PRGM_GetKey() != 28) last = 1;
        if (PRGM_GetKey() == 47) break;

        draw(&x, &y, &px, &py);
    }

    return 0;
}

int gravity(int *y, int *valtijd) {
    if (*y + BLOCK <= SCREEN_H) *y += GRAVITY * *valtijd;
    else *y = SCREEN_H - BLOCK + 1;
    return *y;
}

void draw(int *x, int *y, int *px, int *py) {
    Bdisp_AllClr_VRAM();
	for (int ipx = 0; ipx < PILLAR_W; ipx++) {
		for (int ipy = 0; ipy < PILLAR_H; ipy++) {
			Bdisp_SetPoint_VRAM(*px + ipx, *py + ipy, 0x0FF0);
		}
	}
    for (int ix = 0; ix <= BLOCK; ix++) {
        for (int iy = 0; iy <= BLOCK; iy++) {
            Bdisp_SetPoint_VRAM(*x + ix, *y + iy, 0xF800); // red
        }
    }
    Bdisp_PutDisp_DD();
}

int jump(int *y, int *springmulti) {
    *y -= JUMP_POWER * *springmulti;
    return *y;
}