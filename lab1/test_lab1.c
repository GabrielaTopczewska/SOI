#include <stdio.h>
#include </usr/include/lib.h>
#include </usr/include/minix/callnr.h>
#include <string.h>
#include <stdlib.h>

int getprocnr(int number)
{
	message m;
	m.m1_i1 = number;
	return _syscall(MM, GETPROCNR, &m);
}

int main(int argc, char** argv)
{
	int id_proc, i, number;
	id_proc = atoi(argv[1]);
	
	for(i=id_proc-9; i<=id_proc; i++)
	{
		number = getprocnr(i);
		
		if(number>=0) printf("PID %d, Index %d\n", i, number);
		else printf("Error: %d\n", errno);
	}
	return 0;
}