#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "TF_msg.h"


TF_msg::TF_msg(std::vector<string>& carmenLine, string& frame, bool transform_base_link_laser){

	double lenght = carmenLine.size();

	tf::Transform *odom_base_link = Message<tf::Transform>::getROSMsg();

	float x_laser_index;
	float y_laser_index;
	float angle_laser_index;

	float x_base_link_index;
	float y_base_link_index;
	float angle_base_link_index;

	if(carmenLine[0]=="ROBOTLASER1"){

		x_laser_index = lenght-14;
		y_laser_index = lenght-13;
		angle_laser_index = lenght-12;

		x_base_link_index = lenght-11;
		y_base_link_index = lenght-10;
		angle_base_link_index = lenght-9;

	}
	else if(carmenLine[0]=="FLASER"){

		x_laser_index = lenght-9;
		y_laser_index = lenght-8;
		angle_laser_index = lenght-7;

		x_base_link_index = lenght-6;
		y_base_link_index = lenght-5;
		angle_base_link_index = lenght-4;

	}

	float x_base_link;
	float y_base_link;
	float angle_base_link;

	if(transform_base_link_laser){

		x_base_link = lexical_cast<float>(carmenLine[x_base_link_index]);
		y_base_link = lexical_cast<float>(carmenLine[y_base_link_index]);
		angle_base_link = lexical_cast<float>(carmenLine[angle_base_link_index]);

	}
	else{

		x_base_link = lexical_cast<float>(carmenLine[x_laser_index]);;
		y_base_link = lexical_cast<float>(carmenLine[y_laser_index]);;;
		angle_base_link = lexical_cast<float>(carmenLine[angle_laser_index]);;;

	}

	odom_base_link->setOrigin(Vector3(x_base_link, y_base_link,	0));
	odom_base_link->setRotation(createQuaternionFromYaw(angle_base_link));
	
	
	// cout << carmenLine[lenght-2] << endl;
	// cout << "robot x: " << x << endl;
	// cout << "robot y: " << y << endl;
	// cout << "robot theta: " << theta << endl;

	//exit (1);

	// if(frame=="base_link"){

	// 	this->msg = odom_base_link;

	// }
	// elsep

	if(frame=="laser"){
		
		tf::Transform odom_laser;
		tf::Transform tmp;
		tf::Transform *base_link_laser;

		float x_laser;
		float y_laser;
		float angle_laser;

		x_laser = lexical_cast<float>(carmenLine[x_laser_index]);
		y_laser = lexical_cast<float>(carmenLine[y_laser_index]);
		angle_laser = lexical_cast<float>(carmenLine[angle_laser_index]);

		odom_laser.setOrigin(Vector3(x_laser, y_laser,	0));
		odom_laser.setRotation(createQuaternionFromYaw(angle_laser));

		tmp = odom_base_link->inverseTimes(odom_laser);
		
		//yeah, here just we are using odom_base_link too just to not use an extra variable
		odom_base_link->setOrigin(Vector3(tmp.getOrigin().x(),
										  tmp.getOrigin().y(),
										  0));
		odom_base_link->setRotation(tmp.getRotation());

	}


	setMsgType(2);

}

TF_msg::TF_msg(TF_msg& tf_msg){

	// this->msg_type = tf_msg.msg_type;
	// this->msg = (*tf_msg.getROSMsg());

}


// tf::Transform* TF_msg::getROSMsg()
// {
// 	return &this->msg;
// }
