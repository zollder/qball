/*cjoystick.h : XFX Game Controller HID Joystick Interface
 * Version 1.0 cjoystick.h
 *
 * Author 		: 	Vilas Kumar Chitrakaran <cvilas@ces.clemson.edu>
 * Modified by 	:	Iman Saboori
 * Revised by 	:	Eugen Simon, Oleg Tarassov
 *
 * Date: March 18 2014
 * Please note that range of data sent by joystick is between 0x25 and 0xC4 and you should rescale it in the range of -1 and 1.
 */

#ifndef CJoystick_H_
#define CJoystick_H_

#include <sys/hiddi.h>

/*========================================================================
	struct joystick_data
	brief A structure for holding joystick data
 =======================================================================*/
typedef struct joystick_data
{
	bool status_flag; 			// 'true' if device status is OK.
	char status_msg_buff[80]; 	// Char buffer to hold device status message.
	float x;
	float y;
	float z;
	float rx;
	float ry;
	float rz;
}joystick_data_t;

/*========================================================================
	struct joystick_report
	brief A structure for device reports (for driver internal use)
 =======================================================================*/
typedef struct joystick_report
{
	struct hidd_report_instance *creport_instance;
	struct hidd_report *creport;
	_uint16 *cbtnbuf; 			// current button buffer
}joystick_report_t;

/*========================================================================
	joystick_device structure (used internally, by the driver)
	Holds information about device data, device info and device instance.
 =======================================================================*/
typedef struct joystick_device
{
	joystick_data_t data; 		// device current data.
	joystick_report_t *report;
	hidd_device_instance_t *device_instance;
}joystick_device_t;


class CJoystick
{
	public:

	/**-----------------------------------------------------------------------------------------
	 * Default constructor.
	 * - establishes connection with the HID driver
	 * @param devNum - address of the target joystick device (default = 0)
	 * -----------------------------------------------------------------------------------------*/
	CJoystick();

	/**-----------------------------------------------------------------------------------------
	 * Default destructor.
	 * - disconnet from the HID driver
	 * - clean-up
	 * -----------------------------------------------------------------------------------------*/
	~CJoystick();


	float getX() const; 		// return The X position
	float getY() const; 		// return The Y position
	float getZ() const; 		// return The Y position

	float getRX() const; 		// return The Y position
	float getRY() const; 		// return The Y position
	float getRZ() const; 		// return The Y position

	bool is_status_ok() const; // return true if no error, else false.

	char *get_status_msg() const;
	// return A string carrying current status of the device. This string
	// also carries error messages when is_status_ok() returns false.

	void print_device_info(int verbosity = 1) const;
	// Print information about the device to stdout. Higher values of
	// a verbosity mean more detailed information.

	protected:
	joystick_data_t get_joystick_data() const;
	// return The whole data structure for device
	// with current joystick data

	private:
	struct hidd_connection *d_connection;
	// connection handle to HID server

	// ----- HID server connection functions ------
	static joystick_device_t s_joystick;
	static void on_insertion(struct hidd_connection *connection, hidd_device_instance_t *instance);
	static void on_removal(struct hidd_connection *connection, hidd_device_instance_t *instance);
	static void on_hid_report(struct hidd_connection *connection, struct hidd_report *handle, void *report_data, _uint32 report_len, _uint32 flags, void *user);
};
#endif /* CJoystick_H_*/
