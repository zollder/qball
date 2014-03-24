/*cjoystick.cpp : XFX Game Controller HID Joystick Interface
 * Version 1.0 cjoystick.h
 *
 * Author 		: 	Vilas Kumar Chitrakaran <cvilas@ces.clemson.edu>
 * Modified by 	:	Iman Saboori
 * Revised by 	:	Eugen Simon, Oleg Tarassov
 *
 * Date: March 18 2014
 */

#include "cjoystick.h"
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

joystick_device_t Cjoystick::s_joystick;

//========================================================================
// cjoystick::cjoystick
//========================================================================
Cjoystick::Cjoystick()
{
	s_joystick.data.status_flag = true;
	strncpy(s_joystick.data.status_msg_buff, "cjoystick : not initialized", 80);
	d_connection = NULL;
	s_joystick.device_instance = NULL;

	if (geteuid() != 0)
	{
		s_joystick.data.status_flag = false;
		strncpy(s_joystick.data.status_msg_buff, "cjoystick : Requires superuser privileges", 80);

		return;
	}

	hidd_device_ident_t interest = {HID_VENDOR_XFX, HIDD_CONNECT_WILDCARD /* HID_PRODUCT_XFX */, (_uint32)HIDD_CONNECT_WILDCARD /* HID_VERSION */};

	hidd_funcs_t funcs = {_HIDDI_NFUNCS,
						on_insertion,
						on_removal,
						on_hid_report,
						NULL};

	hidd_connect_parm_t parm = { NULL,
								HID_VERSION,
								HIDD_VERSION,
								0,
								0,
								&interest,
								&funcs,
								HIDD_CONNECT_WAIT};

	if ( hidd_connect(&parm, &d_connection) != EOK )
	{
		s_joystick.data.status_flag = false;
		strncpy(s_joystick.data.status_msg_buff, "cjoystick : Connection with HID driver failed: ", 80);
		strncat(s_joystick.data.status_msg_buff, strerror(errno), 80 - strlen(s_joystick.data.status_msg_buff));
		return;
	}

	strncpy(s_joystick.data.status_msg_buff, "cjoystick : Waiting for Joystick", 80);
}

//========================================================================
// cjoystick::~cjoystick
//========================================================================
Cjoystick::~Cjoystick()
{
	if(d_connection)
		hidd_disconnect( d_connection );
}

//========================================================================
// cjoystick::getX()
//========================================================================
int Cjoystick::getX() const
{
	// return X-axis value
	return s_joystick.data.x;
}

//========================================================================
// cjoystick::getY()
//========================================================================
int Cjoystick::getY() const
{
	// return Y-axis value
	return s_joystick.data.y;
}

//========================================================================
// cjoystick::getZ()
//========================================================================
int Cjoystick::getZ() const
{
	// return Z-axis value
	return s_joystick.data.z;
}

//========================================================================
// cjoystick::getRX()
//========================================================================
int Cjoystick::getRX() const
{
	// return RX-axis value
	return s_joystick.data.rx;
}

//========================================================================
// cjoystick::getRY()
//========================================================================
int Cjoystick::getRY() const
{
	// return RY-axis value
	return s_joystick.data.ry;
}

//========================================================================
// cjoystick::getRZ()
//========================================================================
int Cjoystick::getRZ() const
{
	// return RZ-axis value
	return s_joystick.data.rz;
}

//========================================================================
// cjoystick::is_status_ok()
//========================================================================
bool Cjoystick::is_status_ok() const
{
	return s_joystick.data.status_flag;
}

//========================================================================
// cjoystick::get_status_msg()
//========================================================================
char * Cjoystick::get_status_msg() const
{
	return (char *)s_joystick.data.status_msg_buff;
}

//========================================================================
// cjoystick::print_device_info
//========================================================================
void Cjoystick::print_device_info(int verbosity) const
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

//========================================================================
// cjoystick::get_joystick_data
//========================================================================
joystick_data_t Cjoystick::get_joystick_data() const
{
	return s_joystick.data;
}

//========================================================================
// cjoystick::on_insertion
//========================================================================
void Cjoystick::on_insertion(struct hidd_connection *connection, hidd_device_instance_t *device_instance)
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
			if( hidd_report_attach( connection, device_instance, report_instance, 0,
					sizeof(joystick_report_t) + (max_but * sizeof(_int32)) , &report ) == EOK )
			{
				jstk_report = (joystick_report_t *)hidd_report_extra( report );
				jstk_report->creport = report;
				jstk_report->creport_instance = report_instance;
				jstk_report->cbtnbuf = (_uint16 *) (jstk_report + 1); // setup pointer to button data
				s_joystick.report = jstk_report; break;
			}
		}

		// *** The following is a bad hack. Fix it as recursive search for report ****
		hidd_get_collections( NULL, hidd_collections[i], &hidd_mcollections, &num_mcol);

		if ( num_col && hidd_get_report_instance( hidd_mcollections[0], 0 , HID_INPUT_REPORT, &report_instance ) == EOK )
		{
			hidd_num_buttons( report_instance, &max_but );

			if( hidd_report_attach( connection, device_instance, report_instance, 0,
					sizeof(joystick_report_t) + (max_but * sizeof(_int32)) , &report ) == EOK )
			{
				jstk_report = (joystick_report_t *)hidd_report_extra( report );
				jstk_report->creport = report;
				jstk_report->creport_instance = report_instance;
				jstk_report->cbtnbuf = (_uint16 *) (jstk_report + 1); 			// setup pointer to button data
				s_joystick.report = jstk_report; break;
			}
		}

		hidd_get_collections( NULL, hidd_mcollections[i], &hidd_ncollections, &num_ncol);

		if ( num_mcol && hidd_get_report_instance( hidd_ncollections[0], 0 , HID_INPUT_REPORT,
				&report_instance ) == EOK )
		{
			hidd_num_buttons( report_instance, &max_but );

			if( hidd_report_attach( connection, device_instance, report_instance, 0,
					sizeof(joystick_report_t) + (max_but * sizeof(_int32)) , &report ) == EOK )
			{
				jstk_report = (joystick_report_t *)hidd_report_extra( report );
				jstk_report->creport = report;
				jstk_report->creport_instance = report_instance;
				jstk_report->cbtnbuf = (_uint16 *) (jstk_report + 1); 			// setup pointer to button data
				s_joystick.report = jstk_report;
				break;
			}
		}
	}

	s_joystick.data.status_flag = true;
	strncpy(s_joystick.data.status_msg_buff, "cjoystick : Joystick present", 80);
}

//========================================================================
// cjoystick::on_removal
//========================================================================
void Cjoystick::on_removal(struct hidd_connection *connection, hidd_device_instance_t *instance)
{
	hidd_reports_detach( connection, instance);
	s_joystick.data.status_flag = true;
	strncpy(s_joystick.data.status_msg_buff, "cjoystick : Joystick unplugged", 80);
}

//=======================================================================
// Convert Hexadecimal to integer to fall in range of -1 and 1
//=======================================================================
int Cjoystick::hextodec_translator( char h )
{
	long int y;
	int x;
	const char * hex = &h;

	y = strtol( hex, NULL , 16);

	//y = 37 + 79.5( x + 1 )

	x = ( y - 37)/79.5 - 1;

	return x;
}

//========================================================================
// cjoystick::on_hid_report
//========================================================================
void Cjoystick::on_hid_report(struct hidd_connection *connection,
							struct hidd_report *handle, void *report_data,
							_uint32 report_len, _uint32 flags, void *user)
{
	_uint32 xval, yval, zval, rxval, ryval, rzval;

	struct hidd_collection *collection;
	struct hidd_report_instance *report_instance;

	report_instance = s_joystick.report->creport_instance;
	hidd_report_collection( report_instance, &collection );

	// Read the joystick data
	hidd_get_usage_value( report_instance, NULL, HIDD_PAGE_DESKTOP, HIDD_USAGE_X, report_data, &xval);
	hidd_get_usage_value( report_instance, NULL, HIDD_PAGE_DESKTOP, HIDD_USAGE_Y, report_data, &yval);
	hidd_get_usage_value( report_instance, NULL, HIDD_PAGE_DESKTOP, HIDD_USAGE_Z, report_data, &zval);
	hidd_get_usage_value( report_instance, NULL, HIDD_PAGE_DESKTOP, HIDD_USAGE_RX, report_data, &rxval);
	hidd_get_usage_value( report_instance, NULL, HIDD_PAGE_DESKTOP, HIDD_USAGE_RY, report_data, &ryval);
	hidd_get_usage_value( report_instance, NULL, HIDD_PAGE_DESKTOP, HIDD_USAGE_RZ, report_data, &rzval);

	//transfer the joystick data
	s_joystick.data.x = xval;
	s_joystick.data.y = yval;
	s_joystick.data.z = zval;
	s_joystick.data.rx = rxval;
	s_joystick.data.ry = ryval;
	s_joystick.data.rz = rzval;

	/*
	s_joystick.data.x = hextodec_translator( xval );
	s_joystick.data.y = hextodec_translator( yval );
	s_joystick.data.z = hextodec_translator( zval );
	s_joystick.data.rx = hextodec_translator( rxval );
	s_joystick.data.ry = hextodec_translator( ryval );
	s_joystick.data.rz = hextodec_translator( rzval );
	*/

}
