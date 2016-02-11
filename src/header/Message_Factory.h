#ifndef MESSAGE__FACTORY_H
#define MESSAGE__FACTORY_H

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <boost/program_options/variables_map.hpp>


#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <boost/algorithm/string.hpp>


#include "Laser_msg.h"
#include "TF_msg.h"
#include "Odometry_msg.h"

using namespace std;
using namespace boost;
using namespace boost::program_options;

class Message_Factory
{
private:

	string sourceLine;

	bool transform_base_link_laser;

	Laser_msg* fabricateLaserMsg(std::vector<string>& carmenLine);

	TF_msg* fabricateTFMsg(std::vector<string>& carmenLine, string& frame);

	Odometry_msg* fabricateOdomMsg(std::vector<string>& carmenLine);

public:

	void setConfigs(variables_map &config);

	vector<MessageInterface *> fabricateMsg(string& carmenLine);

	//void setConfig(variables_map& config);

};
#endif
