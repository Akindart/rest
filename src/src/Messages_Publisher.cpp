#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Messages_Publisher.h"


Messages_Publisher::Messages_Publisher(ros::NodeHandle& nh_, Carmen_Decrypter* decrypter, variables_map* config)
{

	
	this->carmen_Decrypter = decrypter;

	this->odomPublisher = nh_.advertise<nav_msgs::Odometry>(config->at("odom_topic").as<string>().c_str(), 100);
	this->laserPublisher = nh_.advertise<sensor_msgs::LaserScan>(config->at("laser1_topic").as<string>().c_str(), 100);
	this->config = config;

}

void Messages_Publisher::publishMsgs()
{

	double frequency = this->config->at("odom_hz").as<float>();
	int i=0, tf_i=0;

	ptr_vector<MessageInterface>::iterator it = this->carmen_Decrypter->getOdomMsgs()->begin();

	Odometry_msg* tmpOdom;
	Laser_msg* tmpLaser;
	TF_msg* tmpTF1;
	TF_msg* tmpTF2;

	ros::Time tf_expiration;

	ros::Rate r(frequency);

	while(ros::ok() && it!=this->carmen_Decrypter->getOdomMsgs()->end()){

		tmpOdom = static_cast<Odometry_msg *>(&this->carmen_Decrypter->getOdomMsgs()->at(i));
		tmpLaser = static_cast<Laser_msg *>(&this->carmen_Decrypter->getLaserMsgs()->at(i));
		tmpTF1 = static_cast<TF_msg *>(&this->carmen_Decrypter->getTFMsgs()->at(tf_i));
		tmpTF2 = static_cast<TF_msg *>(&this->carmen_Decrypter->getTFMsgs()->at(tf_i+1));

		tmpOdom->getROSMsg()->header.seq = (uint) i;
		tmpOdom->getROSMsg()->header.stamp = ros::Time::now();	
		tmpOdom->getROSMsg()->header.frame_id = string(this->config->at("odom_link_id").as<string>());
		tmpOdom->getROSMsg()->child_frame_id = string(this->config->at("base_link_id").as<string>());

		tmpLaser->getROSMsg()->header.seq = (uint) i;
		tmpLaser->getROSMsg()->header.stamp = ros::Time::now();
		tmpLaser->getROSMsg()->header.frame_id = string(this->config->at("laser1_link_id").as<string>());

		tf_expiration = ros::Time::now() + ros::Duration(0.02);

		string *odom_link_id = &this->config->at("odom_link_id").as<string>();
		string *base_link_id = &this->config->at("base_link_id").as<string>();
		string *laser1_link_id = &this->config->at("laser1_link_id").as<string>();

		this->odom_mutex.lock();
		
		this->odomPublisher.publish((*tmpOdom->getROSMsg()));
	
		this->laserPublisher.publish((*tmpLaser->getROSMsg()));

		tfBroadcaster.sendTransform(tf::StampedTransform((*tmpTF1->getROSMsg()), tf_expiration, 
	        		*odom_link_id, *base_link_id));

		tfBroadcaster.sendTransform(tf::StampedTransform((*tmpTF2->getROSMsg()), tf_expiration, 
	        	*base_link_id, *laser1_link_id));

		ros::spinOnce();

		this->odom_mutex.unlock();		

		it++;
		i++;
		tf_i+=2;

		r.sleep();

	}

}

