##build cjoystick class

##read back the joystick X,Y,Z and RZ data and display the data.

1. “hiddi” library in the library list
	project->properties menu
	QNX C/C++ Project”-> goto “Linker”->select “Extra libraries” in the “Category”-> Click on “Add” button and add “hiddi

2. ensure (devu-uhci or devu-ohci) and manager for HID devices (io-hid) are running.
	/sbin/devu-uhci & (or /sbin/devu-ohci &)
	/sbin/io-hid &
	mount -Tio-hid devh-usb.so &
	
Please note that range of data sent by joystick is between 0x25 and 0xC4 and you should rescale it in the range of -1 and 1.

###Check points
Your performance in this lab will be evaluated based on the following operations properly being implemented.
Read the joystick data and display the X,Y,Z and RZ values
