#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Message_Factory.h"
#include "Odometry_msg.h"


vector<MessageInterface *> Message_Factory::fabricateMsg(string& carmenLine)
{

	vector<MessageInterface *> msgVec;

	std::vector<string> tmpTokensVec;

	split(tmpTokensVec, carmenLine, boost::is_any_of(" "));

	//if(tmpTokensVec[0]=="ODOM")
			
	//else || tmpTokensVec[0]=="FLASER"
	if(tmpTokensVec[0]==this->sourceLine){

		string frame_base_link("base_link");
		string frame_laser("laser");
		
		msgVec.push_back((MessageInterface *)this->fabricateOdomMsg(tmpTokensVec));
		msgVec.push_back((MessageInterface *)this->fabricateLaserMsg(tmpTokensVec));
		msgVec.push_back((MessageInterface *)this->fabricateTFMsg(tmpTokensVec, frame_base_link));
		msgVec.push_back((MessageInterface *)this->fabricateTFMsg(tmpTokensVec, frame_laser));

	}
	
	return msgVec;

}

Laser_msg* Message_Factory::fabricateLaserMsg(std::vector<string>& carmenLine)
{
	Laser_msg *laser_msg = new Laser_msg(carmenLine);

	return laser_msg;
}

TF_msg* Message_Factory::fabricateTFMsg(std::vector<string>& carmenLine, string& frame)
{

	TF_msg *tf_msg = new TF_msg(carmenLine, frame, this->transform_base_link_laser);

	return tf_msg;
}

Odometry_msg* Message_Factory::fabricateOdomMsg(std::vector<string>& carmenLine)
{
	Odometry_msg *odometry_msg = new Odometry_msg(carmenLine);

	return odometry_msg;
}

void Message_Factory::setConfigs(variables_map &config){

	this->sourceLine = config.at("source_line").as<string>();
	this->transform_base_link_laser = config.at("transform_base_link_laser").as<bool>();
	
	//cout << "BOOL " << this->transform_base_link_laser << endl;

	return;

}