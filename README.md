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
	
		    ( x + 1 )
	y = 37 + 159 -------
			2
	y:: hex output from joystick
	x:: conversion of the hex into floating decimal
	
####Check points
Your performance in this lab will be evaluated based on the following operations properly being implemented.
Read the joystick data and display the X,Y,Z and RZ values


###Lab 3 - Objectives
- Develop cqstreamclient class
- Connect to the qball qsreamserver
- Receive and display the sensors value every 5 msec.
