#ifndef MESSAGES__PUBLISHER_H
#define MESSAGES__PUBLISHER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <tf/transform_broadcaster.h>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>

#include <boost/thread.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/ptr_container/ptr_vector.hpp>


#include "Carmen_Decrypter.h"

using namespace std;
using namespace boost;
using namespace boost::program_options;


class Messages_Publisher
{
private:
	boost::thread odomThread;
	boost::mutex odom_mutex;

	boost::thread laserThread;
	boost::mutex laser_mutex;

	boost::thread tfThread_odom_base_link;
	boost::mutex tf_mutex_odom_base_link;

	boost::thread tfThread_base_link_laser;
	boost::mutex tf_mutex_base_link_laser;

	ros::Publisher odomPublisher;

	ros::Publisher laserPublisher;

	tf::TransformBroadcaster tfBroadcaster;

	variables_map* config;

	Carmen_Decrypter* carmen_Decrypter;
	
private:
	void publishOdom(ptr_vector<MessageInterface>* msgs);

	void publishLaser(ptr_vector<MessageInterface>* msgs);

	void broadcastTF_odom_base_link(ptr_vector<MessageInterface>* msgs);

	void broadcastTF_base_link_laser(ptr_vector<MessageInterface>* msgs);

public:
	Messages_Publisher(ros::NodeHandle& nh_, Carmen_Decrypter* decrypter, variables_map* config);

	Messages_Publisher();

	void publishMsgs();

};
#endif
