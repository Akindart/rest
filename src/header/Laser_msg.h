#ifndef LASER_MSG_H
#define LASER_MSG_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <sensor_msgs/LaserScan.h>

#include "Message.h"


class Laser_msg : public Message<sensor_msgs::LaserScan 	>
{
private:
	//sensor_msgs::LaserScan msg;


public:
	Laser_msg(std::vector<string>& carmenLine);

	Laser_msg(Laser_msg& laser);

	//sensor_msgs::LaserScan* getROSMsg();

	//virtual void foo(){};

	~Laser_msg(){};

};
#endif
