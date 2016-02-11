#ifndef T_F_MSG_H
#define T_F_MSG_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <tf/transform_datatypes.h>
//#include <tf/transform_broadcaster.h>

#include "Message.h"


class TF_msg : public Message<tf::Transform>
{
private:
	//tf::Transform msg;


public:
	TF_msg(std::vector<string>& carmenLine, string& frame, bool transform_base_link_laser);

	TF_msg(TF_msg& tf_msg);

	//tf::Transform* getROSMsg();

	//virtual void foo(){};

	~TF_msg(){};
	
};
#endif
