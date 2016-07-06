//
// title:     UBLOX.h
// author:    Taylor, Brian R.
// email:     brian.taylor@bolderflight.com
// date:      2016-07-06 
// license: 
//

#ifndef UBLOX_h
#define UBLOX_h

#include "Arduino.h"				

#define PAYLOAD_SIZE	96

struct gpsData {
  unsigned long   iTOW;			  ///< [ms], GPS time of the navigation epoch
  unsigned short  utcYear;		  ///< [year], Year (UTC)
  unsigned char   utcMonth;		  ///< [month], Month, range 1..12 (UTC)
  unsigned char   utcDay;		  ///< [day], Day of month, range 1..31 (UTC)
  unsigned char   utcHour;		  ///< [hour], Hour of day, range 0..23 (UTC)
  unsigned char   utcMin;		  ///< [min], Minute of hour, range 0..59 (UTC)
  unsigned char   utcSec;		  ///< [s], Seconds of minute, range 0..60 (UTC)
  unsigned char   valid;		  ///< [ND], Validity flags
  unsigned long   tAcc;			  ///< [ns], Time accuracy estimate (UTC)
  long            utcNano;		  ///< [ns], Fraction of second, range -1e9 .. 1e9 (UTC)
  unsigned char   fixType;		  ///< [ND], GNSSfix Type: 0: no fix, 1: dead reckoning only, 2: 2D-fix, 3: 3D-fix, 4: GNSS + dead reckoning combined, 5: time only fix
  unsigned char   flags;		  ///< [ND], Fix status flags
  unsigned char   flags2;		  ///< [ND], Additional flags
  unsigned char   numSV;		  ///< [ND], Number of satellites used in Nav Solution
  double          lon;			  ///< [deg], Longitude
  double          lat;			  ///< [deg], Latitude
  double          height;		  ///< [m], Height above ellipsoid 
  double          hMSL;			  ///< [m], Height above mean sea level
  double          hAcc;			  ///< [m], Horizontal accuracy estimate
  double          vAcc;			  ///< [m], Vertical accuracy estimate
  double          velN;			  ///< [m/s], NED north velocity
  double          velE;			  ///< [m/s], NED east velocity
  double          velD;			  ///< [m/s], NED down velocity
  double          gSpeed;		  ///< [m/s], Ground Speed (2-D)
  long            heading;		  ///< [deg], Heading of motion (2-D)
  double          sAcc;			  ///< [m/s], Speed accuracy estimate
  unsigned long   headingAcc;	  ///< [deg], Heading accuracy estimate (both motion and vehicle)
  unsigned short  pDOP;			  ///< [ND], Position DOP
  long			  headVeh;		  ///< [deg], Heading of vehicle (2-D)
};

class UBLOX{
  public:
    UBLOX(int bus);
    void begin(int baud);
    bool read(gpsData *gpsData_ptr);
  private:
  	int _bus;
  	int _fpos;
  	uint8_t _gpsPayload[PAYLOAD_SIZE];
  	HardwareSerial* _port;
	bool parse();
	void calcChecksum(unsigned char* CK, unsigned char* payload, int length);
};

#endif