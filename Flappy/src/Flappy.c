#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/system.h>

#define SCREEN_W 383
#define SCREEN_H 216
#define BLOCK 25
#define JUMP_POWER 5
#define GRAVITY 1.8

// Prototypes
int jump(int *y, int *springmulti);
void draw(int *x, int *y);
int gravity(int *y, int *valtijd);

int main(void) {
    int x = 50;
    int y = 0;
    int last = 1;
	int valtijd = 0;
	int springtijd = 0;
	int springmulti = 1;

    while (1) {
        CMT_Delay_100micros(200);

		if (springtijd == 0) {
			valtijd++;
        	gravity(&y, &valtijd);
		}
        //int key;
		if (springtijd <= 3 && springtijd >= 1) {
			jump(&y, &springmulti);
			springtijd++;
			springmulti++;
		}
		else {
			springtijd = 0;
			springmulti = 1;
		}
        if (PRGM_GetKey() == 57 && last == 1) {
			springtijd++;
            jump(&y, &springmulti);  // JUMP
            last = 0;
			valtijd = 0;
        }
        else if (PRGM_GetKey() != 57) last = 1;
        if (PRGM_GetKey() == 47) break;  // Exit

        draw(&x, &y);
    }

    return 0;
}

int gravity(int *y, int *valtijd) {
    if (*y + BLOCK <= SCREEN_H) *y += GRAVITY * *valtijd;
    else *y = SCREEN_H - BLOCK + 1;
    return *y;
}

void draw(int *x, int *y) {
    Bdisp_AllClr_VRAM();
    for (int ix = 0; ix <= BLOCK; ix++) {
        for (int iy = 0; iy <= BLOCK; iy++) {
            Bdisp_SetPoint_VRAM((*x) + ix, (*y) + iy, 0xF800); // red
        }
    }
    Bdisp_PutDisp_DD();
}

int jump(int *y, int *springmulti) {
    *y -= JUMP_POWER * *springmulti;
    return *y;
}