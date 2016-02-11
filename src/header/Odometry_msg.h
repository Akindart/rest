#ifndef ODOMETRY_MSG_H
#define ODOMETRY_MSG_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <nav_msgs/Odometry.h>

#include "Message.h"

class Odometry_msg : public Message<nav_msgs::Odometry>
{
private:
	//nav_msgs::Odometry msg;

	void constructor_odomReading(std::vector<string>& carmenLine);
	void constructor_robotlaserReading(std::vector<string>& carmenLine);

public:

	Odometry_msg(std::vector<string>& carmenLine);

	Odometry_msg(Odometry_msg& odom);

	//nav_msgs::Odometry* getROSMsg();

	//virtual void foo(){}; 

	~Odometry_msg(){};

};
#endif
