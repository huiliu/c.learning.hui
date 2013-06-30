#include <graphics.h>
int main(void){
int gdriver, gmode;
	gdriver = DETECT;
	initgraph(&gdriver, &gmode,0);
line(100, 100, 200, 200);
getch();
closegraph();
return 0;

}
