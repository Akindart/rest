#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Laser_msg.h"

#define PI 3.14159265359

Laser_msg::Laser_msg(std::vector<string>& carmenLine){

	sensor_msgs::LaserScan *msg = this->Message<sensor_msgs::LaserScan>::getROSMsg();

	int angle_min_index;
	int field_of_view_index;
	int angle_increment_index;
	int range_max_index;
	int num_readings_index;
	int first_reading_index;

	float range_max;
	float range_min;

	if(carmenLine[0]=="ROBOTLASER1"){

		angle_min_index = 2;
		field_of_view_index = 3;
		angle_increment_index = 4;
		range_max_index = 5;
		num_readings_index = 8;
		first_reading_index = 9;

	}
	else if(carmenLine[0]=="FLASER"){
 
		angle_min_index = -1;
		field_of_view_index = -1;
		angle_increment_index = -1;
		range_max_index = -1;
		num_readings_index = 1;
		first_reading_index = 2;

	}

	int num_readings = lexical_cast<int>(carmenLine[num_readings_index]);

	if(angle_min_index != -1){
		msg->angle_min = lexical_cast<float>(carmenLine[angle_min_index]);
	
		if(msg->angle_min < 0)
			msg->angle_max = msg->angle_min + lexical_cast<float>(carmenLine[field_of_view_index]);
		else msg->angle_max = msg->angle_min - lexical_cast<float>(carmenLine[field_of_view_index]);
	
	}
	else{

		msg->angle_min = -(lexical_cast<float>(carmenLine[num_readings_index])/2)*PI/180;

		if(msg->angle_min < -(PI/2 + 0.008726646)) msg->angle_min = -(lexical_cast<float>(carmenLine[num_readings_index])/4)*PI/180;

		if(num_readings <= 181)
			msg->angle_max = msg->angle_min + num_readings*PI/180;
		else msg->angle_max = msg->angle_min + (num_readings/2)*PI/180;

	}
	
	if(angle_increment_index != -1)
		msg->angle_increment = lexical_cast<float>(carmenLine[angle_increment_index]);
	else msg->angle_increment = (abs(msg->angle_max) + abs(msg->angle_min))/num_readings;

	msg->time_increment = 0.0;

	msg->scan_time = 0.0;

	if(range_max_index != -1)
		range_max = lexical_cast<float>(carmenLine[range_max_index]);


	for(int i=0; i<num_readings; i++){

		float reading;
		reading = lexical_cast<float>(carmenLine[first_reading_index+i]);

		if(msg->angle_min < 0)
		 	msg->ranges.push_back(reading);
		else		
			msg->ranges.insert(msg->ranges.begin(), reading);
	
		if(i==0){

			if(range_max_index == -1)
				range_max = reading;
			
			range_min = reading;

		}
		else{

			if(reading > range_max && range_max_index == -1) range_max = reading;
			if(reading < range_min) range_min = reading;

		}

	}

	if(range_max_index == -1) 
		range_max=60;
	
	if(range_min > 0.4) 
		range_min -=0.2;
		
	msg->range_max = range_max;
	msg->range_min = range_min;

	setMsgType(1);

}

Laser_msg::Laser_msg(Laser_msg& laser){

	// this->msg_type = laser.msg_type;
	// this->msg = (*laser.getROSMsg());

}

// sensor_msgs::LaserScan* Laser_msg::getROSMsg()
// {
// 	return &this->msg;
// }
