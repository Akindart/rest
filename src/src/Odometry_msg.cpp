#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>


#include "Odometry_msg.h"

Odometry_msg::Odometry_msg(std::vector<string>& carmenLine){

    nav_msgs::Odometry *msg = Message<nav_msgs::Odometry>::getROSMsg();

    double lv_x;
    double lv_y;
    double av_z;
    double angle;

    int lv_index;
    int av_z_index;
    int angle_index;
    int pos_x_index;
    int pos_y_index;

    double lenght = carmenLine.size();    

    if(carmenLine[0]=="ODOM"){

        pos_x_index = 1;
        pos_y_index = 2;
        angle_index = 3;
        lv_index = 4;
        av_z_index = 5;

    }
    else if(carmenLine[0]=="ROBOTLASER1"){

        pos_x_index = lenght-11;
        pos_y_index = lenght-10;
        angle_index = lenght-9;
        lv_index = lenght-5;
        av_z_index = lenght-4;

    }
    else if(carmenLine[0]=="FLASER"){

        pos_x_index = lenght-6;
        pos_y_index = lenght-5;
        angle_index = lenght-4;
        lv_index = -1;
        av_z_index = -1;

    }

    msg->pose.pose.position.x = lexical_cast<double>(carmenLine[pos_x_index]);
    msg->pose.pose.position.y = lexical_cast<double>(carmenLine[pos_y_index]);;

    angle = lexical_cast<double>(carmenLine[angle_index]);

    if(lv_index != -1 && av_z_index != -1){

        lv_x = lexical_cast<double>(carmenLine[lv_index])*cos(angle);
        lv_y = lexical_cast<double>(carmenLine[lv_index])*sin(angle);
        av_z = lexical_cast<double>(carmenLine[av_z_index]);

    }
    else {

        lv_x = 0;
        lv_y = 0;
        av_z = 0;

    }


    msg->pose.pose.position.z = 0;    

    msg->pose.pose.orientation = createQuaternionMsgFromRollPitchYaw(0,0,angle);

    vector<double> covMatrix;

    for(int i=0; i<36; i++){

        if(i==0||i==7) msg->pose.covariance[i] = 0.2;
        else if(i==35) msg->pose.covariance[i] = 0.03;
        else if(i==14||i==21||i==28) msg->pose.covariance[i] = 9999.0;
        else msg->pose.covariance[i] = 0.0;;

    }
    
    msg->twist.covariance = msg->pose.covariance;    

    msg->twist.twist.linear.x = lv_x;
    msg->twist.twist.linear.y = lv_y;
    msg->twist.twist.linear.z = 0;

    msg->twist.twist.angular.x = 0;
    msg->twist.twist.angular.y = 0;
    msg->twist.twist.angular.z = av_z;

    //this->msg.child_frame_id = string("bugabuga");

    //this->msg.header.frame_id = string("bugabuga");

    //cout << this->msg.header.frame_id << endl;

    setMsgType(0);
}

Odometry_msg::Odometry_msg(Odometry_msg& odom){

    // this->msg_type = odom.msg_type;
    // this->msg = (*odom.getROSMsg());

}
