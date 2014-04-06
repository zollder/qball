/*cjoystick.cpp : XFX Game Controller HID Joystick Interface
 * Version 1.0 cjoystick.h
 *
 * Author 		: 	Vilas Kumar Chitrakaran <cvilas@ces.clemson.edu>
 * Modified by 	:	Iman Saboori
 * Revised by 	:	Eugen Simon, Oleg Tarassov
 *
 * Date: March 18 2014
 */

#include "CJoystick.h"
#include <sys/hidut.h>
#include <sys/hiddi.h>
#include <unistd.h>
#include <iostream.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


	#define HID_VENDOR_XFX 0x0E8F
	#define HID_PRODUCT_XFX 0x0003
	#define JOYSTICK_MIN_VAL 0x25
	#define JOYSTICK_MAX_VAL 0xC4

	joystick_device_t CJoystick::s_joystick;

	/**-----------------------------------------------------------------------------------------
	 *  Constructor.
	 * -----------------------------------------------------------------------------------------*/
	CJoystick::CJoystick()
	{
		// initialize an array to zeros
		joystickData = new double[dataSize];
		for(unsigned int i = 0; i < dataSize; i++)
			joystickData[i] = 0;

		s_joystick.data.status_flag = true;
		strncpy(s_joystick.data.status_msg_buff, "CJoystick : not initialized", 80);
		d_connection = NULL;
		s_joystick.device_instance = NULL;

		// make sure a user has required access rights
		if (geteuid() != 0)
		{
			s_joystick.data.status_flag = false;
			strncpy(s_joystick.data.status_msg_buff, "CJoystick : Requires superuser privileges", 80);

			return;
		}

		// identify and initialize the device
		hidd_device_ident_t interest = {HID_VENDOR_XFX, HIDD_CONNECT_WILDCARD /* HID_PRODUCT_XFX */, (_uint32)HIDD_CONNECT_WILDCARD /* HID_VERSION */};
		hidd_funcs_t funcs = {_HIDDI_NFUNCS, on_insertion, on_removal, on_hid_report, NULL};
		hidd_connect_parm_t parm = { NULL, HID_VERSION, HIDD_VERSION, 0, 0, &interest, &funcs, HIDD_CONNECT_WAIT};

		if (hidd_connect(&parm, &d_connection) != EOK)
		{
			s_joystick.data.status_flag = false;
			strncpy(s_joystick.data.status_msg_buff, "CJoystick : Connection with HID driver failed: ", 80);
			strncat(s_joystick.data.status_msg_buff, strerror(errno), 80 - strlen(s_joystick.data.status_msg_buff));
			return;
		}

		strncpy(s_joystick.data.status_msg_buff, "CJoystick : Waiting for Joystick", 80);
	}

	/**-----------------------------------------------------------------------------------------
	 *  Destructor.
	 * -----------------------------------------------------------------------------------------*/
	CJoystick::~CJoystick()
	{
		if(d_connection)
			hidd_disconnect( d_connection );

		delete joystickData;
	}

	/**-----------------------------------------------------------------------------------------
	 *  Returns device status (true or false).
	 * -----------------------------------------------------------------------------------------*/
	bool CJoystick::isStatusOk() const
	{
		return s_joystick.data.status_flag;
	}

	/**-----------------------------------------------------------------------------------------
	 *  Returns device status message.
	 * -----------------------------------------------------------------------------------------*/
	char * CJoystick::getStatusMessage() const
	{
		return (char *)s_joystick.data.status_msg_buff;
	}

	/**-----------------------------------------------------------------------------------------
	 *  Prints device information.
	 * -----------------------------------------------------------------------------------------*/
	void CJoystick::printDeviceInfo(int verbosity) const
	{
		hidd_device_instance_t *device_instance = s_joystick.device_instance;

		if(device_instance == NULL)
			return;

		char buffer[100];

		hidd_get_manufacturer_string(d_connection, device_instance, buffer, 100);
		cout << "Manufacturer : " << buffer << endl;

		hidd_get_product_string(d_connection, device_instance, buffer, 100);
		cout << "Product : " << buffer << endl;

		if(verbosity < 2)
			return;

		cout << "Software Version : 1.0, June 2011" << endl;
		cout << "Status message : " << s_joystick.data.status_msg_buff << endl;
	}

	/**-----------------------------------------------------------------------------------------
	 *  CJoystick::on_insertion
	 * -----------------------------------------------------------------------------------------*/
	void CJoystick::on_insertion(struct hidd_connection *connection, hidd_device_instance_t *device_instance)
	{
		struct hidd_collection **hidd_collections, **hidd_mcollections, **hidd_ncollections;
		struct hidd_report_instance *report_instance;
		struct hidd_report *report; joystick_report_t *jstk_report = NULL;

		_uint16 num_col, num_mcol, num_ncol;
		_uint16 usage_page, usage;
		_uint16 max_but=0;
		int i;

		s_joystick.device_instance = device_instance;

		// Get root level HID collections
		hidd_get_collections( device_instance, NULL, &hidd_collections, &num_col);

		// for each top level collection
		for(i = 0; i < num_col; i++)
		{
			// Get usage for the collection
			hidd_collection_usage( hidd_collections[i], &usage_page, &usage);

			// Ignore collection if it doesn't describe joystick functionality
			if( usage_page != HIDD_PAGE_DESKTOP || usage != HIDD_USAGE_JOYSTICK)
				continue;

			if( hidd_get_report_instance(hidd_collections[i], 0, HID_INPUT_REPORT, &report_instance) == EOK )
			{
				hidd_num_buttons( report_instance, &max_but );
				if (hidd_report_attach( connection, device_instance, report_instance, 0,
						sizeof(joystick_report_t) + (max_but * sizeof(_int32)) , &report ) == EOK)
				{
					jstk_report = (joystick_report_t *) hidd_report_extra(report);
					jstk_report->creport = report;
					jstk_report->creport_instance = report_instance;
					jstk_report->cbtnbuf = (_uint16 *) (jstk_report + 1); // setup pointer to button data
					s_joystick.report = jstk_report; break;
				}
			}

			// *** The following is a bad hack. Fix it as recursive search for report ****
			hidd_get_collections( NULL, hidd_collections[i], &hidd_mcollections, &num_mcol);

			if (num_col && hidd_get_report_instance(hidd_mcollections[0], 0, HID_INPUT_REPORT, &report_instance) == EOK)
			{
				hidd_num_buttons( report_instance, &max_but );

				if (hidd_report_attach(connection, device_instance, report_instance, 0,
						sizeof(joystick_report_t) + (max_but * sizeof(_int32)), &report) == EOK)
				{
					jstk_report = (joystick_report_t *) hidd_report_extra(report);
					jstk_report->creport = report;
					jstk_report->creport_instance = report_instance;
					jstk_report->cbtnbuf = (_uint16 *) (jstk_report + 1); 			// setup pointer to button data
					s_joystick.report = jstk_report;
					break;
				}
			}

			hidd_get_collections( NULL, hidd_mcollections[i], &hidd_ncollections, &num_ncol);

			if (num_mcol && hidd_get_report_instance(hidd_ncollections[0], 0, HID_INPUT_REPORT, &report_instance) == EOK)
			{
				hidd_num_buttons(report_instance, &max_but);

				if (hidd_report_attach( connection, device_instance, report_instance, 0,
						sizeof(joystick_report_t) + (max_but * sizeof(_int32)), &report) == EOK)
				{
					jstk_report = (joystick_report_t *) hidd_report_extra(report);
					jstk_report->creport = report;
					jstk_report->creport_instance = report_instance;
					jstk_report->cbtnbuf = (_uint16 *) (jstk_report + 1); 			// setup pointer to button data
					s_joystick.report = jstk_report;
					break;
				}
			}
		}

		s_joystick.data.status_flag = true;
		strncpy(s_joystick.data.status_msg_buff, "CJoystick : Joystick present", 80);
	}

	/**-----------------------------------------------------------------------------------------
	 *  CJoystick::on_removal
	 * -----------------------------------------------------------------------------------------*/
	void CJoystick::on_removal(struct hidd_connection *connection, hidd_device_instance_t *instance)
	{
		hidd_reports_detach(connection, instance);
		s_joystick.data.status_flag = true;
		strncpy(s_joystick.data.status_msg_buff, "CJoystick : Joystick unplugged", 80);
	}

	/**-----------------------------------------------------------------------------------------
	 *  Converts HEX values read from the joystick to integers.
	 *  Normalises converted values to fall in range from -1 to 1.
	 * -----------------------------------------------------------------------------------------*/
	float hextodec_translator( _uint32 value )
	{
		// reset unused word values with a mask
		float y = value & 0x000000FF;

		// convert and normalise
		return ((y - JOYSTICK_MIN_VAL) / (JOYSTICK_MAX_VAL - JOYSTICK_MIN_VAL)) * 2 - 1;
	}

	/**-----------------------------------------------------------------------------------------
	 *  Reads joystick control values, promotes them to doubles and inserts them into array
	 *  as follows: {x, y, z, rx, ry, rz, reserved, reserved}
	 * -----------------------------------------------------------------------------------------*/
	void CJoystick::on_hid_report(struct hidd_connection *connection, struct hidd_report *handle,
			void *report_data, _uint32 report_len, _uint32 flags, void *user)
	{
		_uint32 xval, yval, zval, rxval, ryval, rzval;

		struct hidd_collection *collection;
		struct hidd_report_instance *report_instance;

		report_instance = s_joystick.report->creport_instance;
		hidd_report_collection( report_instance, &collection );

		// Read the joystick data
		hidd_get_usage_value(report_instance, NULL, HIDD_PAGE_DESKTOP, HIDD_USAGE_X, report_data, &xval);
		hidd_get_usage_value(report_instance, NULL, HIDD_PAGE_DESKTOP, HIDD_USAGE_Y, report_data, &yval);
		hidd_get_usage_value(report_instance, NULL, HIDD_PAGE_DESKTOP, HIDD_USAGE_Z, report_data, &zval);
		hidd_get_usage_value(report_instance, NULL, HIDD_PAGE_DESKTOP, HIDD_USAGE_RX, report_data, &rxval);
		hidd_get_usage_value(report_instance, NULL, HIDD_PAGE_DESKTOP, HIDD_USAGE_RY, report_data, &ryval);
		hidd_get_usage_value(report_instance, NULL, HIDD_PAGE_DESKTOP, HIDD_USAGE_RZ, report_data, &rzval);

		// convert and save joystick data into the local data holder
		s_joystick.data.x = hextodec_translator(xval);
		s_joystick.data.y = hextodec_translator(yval);
		s_joystick.data.z = hextodec_translator(zval);
		s_joystick.data.rx = hextodec_translator(rxval);
		s_joystick.data.ry = hextodec_translator(ryval);
		s_joystick.data.rz = hextodec_translator(rzval);
	}


	/**-----------------------------------------------------------------------------------------
	 *  Returns an array with joystick data
	 * -----------------------------------------------------------------------------------------*/
	double* CJoystick::getData()
	{
		joystickData[0] = (double) s_joystick.data.x;
		joystickData[1] = (double) s_joystick.data.y;
		joystickData[2] = (double) s_joystick.data.z;
		joystickData[3] = (double) s_joystick.data.rx;
		joystickData[4] = (double) s_joystick.data.ry;
		joystickData[5] = (double) s_joystick.data.rz;

		return joystickData;
	}
