void Messages_Publisher::publishOdom(ptr_vector<MessageInterface>* msgs)
{

	double frequency = this->config->at("odom_hz").as<float>();

	ros::Rate r(frequency);

	ptr_vector<MessageInterface>::iterator it = msgs->begin();
	int i=0;

	Odometry_msg* tmp;

	while(ros::ok() && it!=msgs->end()){

		tmp = static_cast<Odometry_msg *>(&msgs->at(i));

		tmp->getROSMsg()->header.seq = (uint) i;
		tmp->getROSMsg()->header.stamp = ros::Time::now();		

		tmp->getROSMsg()->header.frame_id = string(this->config->at("odom_link_id").as<string>());

		tmp->getROSMsg()->child_frame_id = string(this->config->at("base_link_id").as<string>());				

		this->odom_mutex.lock();
		
			this->odomPublisher.publish((*tmp->getROSMsg()));

		this->odom_mutex.unlock();

		ros::spinOnce();

		it++;
		i++;

		r.sleep();

	}	
	

}

void Messages_Publisher::publishLaser(ptr_vector<MessageInterface>* msgs)
{

	//cout << "laser" << endl;

	double frequency = this->config->at("laser1_hz").as<float>();

	//cout << "laser2" << endl;

	ros::Rate r(frequency);

	ptr_vector<MessageInterface>::iterator it = msgs->begin();
	int i=0;

	Laser_msg* tmp;

	while(ros::ok() && it!=msgs->end()){

		tmp = static_cast<Laser_msg *>(&msgs->at(i));

		tmp->getROSMsg()->header.seq = (uint) i;
		tmp->getROSMsg()->header.stamp = ros::Time::now();		

		tmp->getROSMsg()->header.frame_id = string(this->config->at("laser1_link_id").as<string>());

		this->laser_mutex.lock();
		
			this->laserPublisher.publish((*tmp->getROSMsg()));

		this->laser_mutex.unlock();

		ros::spinOnce();

		it++;
		i++;

		r.sleep();

	}	

}

void Messages_Publisher::broadcastTF_odom_base_link(ptr_vector<MessageInterface>* msgs)
{
 
    ros::Time tf_expiration;    

    //cout << "tf" << endl;
    
    double frequency = this->config->at("tf1_hz").as<float>();

    //cout << "tf2" << endl;

	ros::Rate r(frequency);

	ptr_vector<MessageInterface>::iterator it = msgs->begin();
	int i=0;

	TF_msg *tmp;

	string *odom_link_id = &this->config->at("odom_link_id").as<string>();
	string *base_link_id = &this->config->at("base_link_id").as<string>();

	while(ros::ok() && it!=msgs->end() && i<msgs->size()){

		tmp = static_cast<TF_msg *>(&msgs->at(i));

		tf_expiration = ros::Time::now() + ros::Duration(0.01);

		this->tf_mutex_odom_base_link.lock();

				tfBroadcaster.sendTransform(tf::StampedTransform((*tmp->getROSMsg()), tf_expiration, 
	        		*odom_link_id, *base_link_id));

		this->tf_mutex_odom_base_link.unlock();

		ros::spinOnce();

		it++;
		it++;
		i+=2;	

		r.sleep();
		
	}	

}

void Messages_Publisher::broadcastTF_base_link_laser(ptr_vector<MessageInterface>* msgs)
{
 
    ros::Time tf_expiration;    

    //cout << "tf" << endl;
    
    double frequency = this->config->at("tf1_hz").as<float>();

    //cout << "tf2" << endl;

	ros::Rate r(frequency);

	ptr_vector<MessageInterface>::iterator it = msgs->begin();
	int i=1;

	TF_msg *tmp;

	string *laser1_link_id = &this->config->at("laser1_link_id").as<string>();
	string *base_link_id = &this->config->at("base_link_id").as<string>();

	it++;

	while(ros::ok() && it!=msgs->end() && i<msgs->size()){

		tmp = static_cast<TF_msg *>(&msgs->at(i));

		tf_expiration = ros::Time::now() + ros::Duration(0.01);

		this->tf_mutex_base_link_laser.lock();

			tfBroadcaster.sendTransform(tf::StampedTransform((*tmp->getROSMsg()), tf_expiration, 
	        	*base_link_id, *laser1_link_id));

		this->tf_mutex_base_link_laser.unlock();

		ros::spinOnce();	

		it++;
		it++;
		i+=2;	

		r.sleep();
		
	}	

}
