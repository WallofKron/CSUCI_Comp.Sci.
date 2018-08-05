#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

#include "sim_dev.h"

#define oops(msg, errnum) { perror(msg); exit(errnum); }

#define BUFSIZE 4096

int main(void)
{
	int i, fd, len, wlen, tmp, tmp2;
	
	// test message to send to the device
	char msg[] = "Skeleton Kernel Module Test";
	char receive_buffer[128];
	
	// variables for holding device control data
	int ioctl_control_data, ioctl_status_data;

   // open the I/O channel to the device
	fd = open("/dev/sim_dev", O_RDWR | O_SYNC);
	if( fd == -1)
	   oops("Unable to open device...", 1);

	// test device write function
	len = write(fd, msg, strlen(msg) + 1);
	if( len == -1 )
		oops("Unable to write to the simuated device.\n", 2);

	printf("'%s' written to /dev/sim_dev\n", msg);
	
	// test device read function
	len = read(fd, receive_buffer, 128);
	if( len == -1 )
		oops("Unable to read from the simulated device.\n", 3);

	printf("'%s' read from /dev/sim_dev\n", receive_buffer);

	// test ioctl with the device
	// this is a sample content to send to the device
	ioctl_control_data = 0xABCDEFEF;
	
	// send command to the device
	ioctl(fd, IOCTL_SIM_DEV_WRITE, &ioctl_control_data);
	
	// get a status from the device
	// we poll here, but that also can be in response to an interrupt
	ioctl(fd, IOCTL_SIM_DEV_READ, &ioctl_status_data);
	
	printf("IOCTL test: written: '%x' - received: '%x'\n", ioctl_control_data, ioctl_status_data);

	close(fd);
}

