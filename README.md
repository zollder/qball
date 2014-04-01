##Objective: Manoeuvre Qball by Joystick
- Use ctimer class and cjoystick class to readback the joystick X,Y,Z and RZ data
- Develop a cqstreamsrv class to send the joystick data to qball (Wrapper)
- Use ctimer class and cqstreamclient class to read the qball sensors and display it
- Use qball_motor_control Simulink model to send the sensors data to SPC and receive commands from SPC to 
	control the motors speeds.

###cqstreamsrv class
	Using ctimer class and cjoystick class readback the joystick X,Y,Z and RZ data
	Send Joystick data to qball
	Using ctimer class and cqstreamclient to read qball sensor and display it
	Send sensor data qball_motor_control Simulink model to SPC
	Receive commands from SPC to control the motors speeds.
	
control the speed of qball propellers using the joystick

Lab Step 1: Turn on the qball and check that it is connected the workstation as you did in first experiment
Lab Step 2: Run matlab/ simulink and open the qball_motor_control simulink model developed in first experiment.
		After you load and compile it into the qball, it sends the sensors data via wireless connection to the qstream clients.

Step 1: Use cqstreamclient class to connect to qstream server on qball at TCP/IP port 18000 and read and 
		display sensors data every 5 msec.
Step 2: Use cjoystick class to read joystick data and develop a cqstreamsrv class to send the joystick data 
		to the qball every 5 msec.
	  : The cqstreamsrv class should bind to TCP/IP port 18005 and accept the connection requests from 
		the qstream client on the qball side.
	  : Data send by server should be an array of 8 doubles:
###Joystick array
	Array index 		Data description
	0			Joystick X-axis
	1			Joystick Y-axis
	2			Joystick Z-axis
	3			Joystick RZ-axis
	4			0
	5			0
	6			0
	7			0

###Check Points:
	Receive and display the received data

=====================================================

##Qball-X4 (quadrotor helicopter) real-time project.

###Lab4 - Build cjoystick class

read back the joystick X,Y,Z and RZ data and display the data.

1. “hiddi” library in the library list
	project->properties menu
	QNX C/C++ Project”-> goto “Linker”->select “Extra libraries” in the “Category”-> Click on “Add” button and add “hiddi

2. ensure (devu-uhci or devu-ohci) and manager for HID devices (io-hid) are running.
	/sbin/devu-uhci & (or /sbin/devu-ohci &)
	/sbin/io-hid &
	mount -Tio-hid devh-usb.so &
	
Please note that range of data sent by joystick is between 0x25 and 0xC4 and you should rescale it in the range of -1 and 1.

:solution - Linear Interpolation:
	
	y1|-----x
	  |    /|
	  |   /	|
	y0|--x 	|
	  |  |	|
	  |__|__|__
	    x0	x1
	
	y - y0 	 y1 - y0
	------ = ------- ==> y = y0 + ( y1 - y0 )( x - x0 / x1 - x0 )
	x - x0	 x1 - x0
	
	y1 = 0xc4 = 196
	y0 = 0x25 = 37
	x1 = 1
	x0 = -1
	
	y = 37 + 159( x + 1 )/2
	y = 37 + 79.5( x + 1 )
	
	y:: hex output from joystick
	x:: conversion of the hex into floating decimal
	
####Check points
Your performance in this lab will be evaluated based on the following operations properly being implemented.
Read the joystick data and display the X,Y,Z and RZ values


###Lab 3 - Objectives
- Develop cqstreamclient class
- Connect to the qball qsreamserver
- Receive and display the sensors value every 5 msec.
