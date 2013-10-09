#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
Program that sends output to Pololu motor controllers over a serial connection.
Command-line arguments:
	-h:	Displays a help message
	-d:	Specify a device number (Default is 11)
	-o:	Sends the "Motor Off" command
	-f: Go forwards with specified magnitude (low-resolution mode)
	-r:	Go backwards with specified magnitude (low-resolution mode)
*/
	static const char *optstring = "hd:of:r:";

	int output_length = 2;
	unsigned int device_number = 11; /* Default device number according to the Pololu documentation */
	char output_mode; /* What command the program should send */
	int target = 0; /*  */
	
	int i;
	int option = 0;

void show_help()
{
	printf("\
	pololu_control: Sends commands to a Pololu motor controller.\n\
	Command-line arguments:\n\
	\t-h:\tDisplays a help message (You're reading it!)\n\
	\t-d:\tSpecify a device number (Default is 11)\n\
	\t-o:\tSend the \"Motor Off\" command\n\
	\t-f:\tGo forwards with specified magnitude (0-127)\n\
	\t-r:\tGo backwards with specified magnitude (0-127)\n\
	\t\tBoth movement commands use low-resolution mode.\n\
	");
}
	
int main(int argc, char *argv[])
{
	option = getopt(argc, argv, optstring);
	
	if (option == -1)
	{
		show_help();
		exit(0);
	}
	
	while (option != -1)
	{
		switch(option)
		{
			case 'h':
				show_help();
				exit(0);
				break;
				
			case 'd':
				device_number = atoi(optarg);
				break;
			
			case 'r':
				output_mode = 'r';
				target = atoi(optarg);
				break;
				
			case 'f':
				output_mode = 'f';
				target = atoi(optarg);
				break;
				
			case 'o':
				output_mode = 'o';
				break;
				
			default:
				show_help();
				exit(0);
				break;
		}
		option = getopt(argc, argv, optstring);
	}
	
	if (target < 0 || target > 127)
	{
		fprintf(stderr, "Target out of range.");
		exit(1);
	}
	
	if (device_number > 127)
	{
		fprintf(stderr, "Device number out of range.");
		exit(1);
	}
	
	if (output_mode == 'o')
	{
		output_length += 1;
	}
	else if (output_mode == 'f' || output_mode == 'r')
	{
		output_length += 2;
	}
	else
	{
		fprintf(stderr,"No command specified.");
		exit(1);
	}
	
	unsigned int *output = malloc(sizeof(int)*(output_length));
	
	output[0] = 0xAA;
	output[1] = device_number;
	
	if (output_mode == 'o')
	{
		output[2] = 0x7F;
	}
	else if (output_mode == 'f')
	{
		output[2] = 0x61;
		output[3] = target;
	}
	else if (output_mode == 'r')
	{
		output[2] = 0x60;
		output[3] = target;
	}
	else
	{
		fprintf(stderr,"Invalid output mode.");
		exit(1);
	}
	
	for (i=0; i < output_length; i++)
	{
		printf("0x%.2X ",output[i]);
	}
	printf("\n");
	
	free(output);
	return 0;
}