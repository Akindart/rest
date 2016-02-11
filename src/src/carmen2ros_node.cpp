#include <ros/ros.h>
//C
#include <stdio.h>
#include <stdlib.h>
//C++
#include <iostream>
#include <sstream>
//boost
#include <boost/program_options.hpp>
#include <boost/unordered_map.hpp>


#include "Carmen_Decrypter.h"
#include "Messages_Publisher.h" 

#define PI 3.14159265359

//typedef boost::program_options po;

namespace po = boost::program_options;

using namespace boost::program_options;
using namespace std;



int programInputValidation(int argc, char *argv[], variables_map& vm){

	po::options_description desc("Here follows what this program expects as input options");
	// First parameter describes option name/short name
    // The second is parameter to option
    // The third is description
	desc.add_options()

		("help,h", "print usage message")
		// ("laser1_hz", value<float>()->default_value(11.0),
		// 	"specifies the frequency the laser msg from ROBOTLASER1 is going to be published")
		// ("tf1_hz", value<float>()->default_value(60.0), 
		// 	"specifies the frequency the tf msg from ROBOTLASER1 is going to be broadcasted")
		("odom_hz", value<float>()->default_value(11.0), 
			"specifies the frequency the odom msg from ODOM is going to be published")
		("laser1_topic", value<string>()->default_value("scan1"), 
			"defines the name of the which the laser from ROBOTLASER1 is going to be published")
		("odom_topic", value<string>()->default_value("odom"), 
			"specifies the name of the which the odometry from ODOM is going to be published")
		("laser1_link_id", value<string>()->default_value("laser1"), 
			"specifies the id of the laser, w.r.t to base_link, from ROBOTLASER1 that will be used by tf")
		("odom_link_id", value<string>()->default_value("odom"), 
			"specifies the id of the odom from ODOM that will be used by tf")
		("base_link_id", value<string>()->default_value("base_link"), 
			"specifies the id of the base_link, w.r.t odom calculated from ROBOTLASER1, that will be used by tf")
		("source_line,s", value<string>()->default_value("ROBOTLASER1"),
			"specifies which line will be used as source od information, the user can choose between FLASER or ROBOTLASER1")
		("transform_base_link_laser,t", value<bool>()->default_value(false),
			"defines if there is a transformation needed to be made, i.e., laser w.r.t. base_link, if not, the program considers the base_link to have the same pose of the laser")
		("laser_field_of_view", value<double>()->default_value(PI),
			"if using FLASER line as source of information, set this flag with your laser field of view in DEGREES")
		("laser_max_range", value<double>()->default_value(80.0),
			"if using FLASER line as source of information, set this flag with your laser max range in METERS")


	;

	po::options_description hiddenOpts("Hidden Options");

	hiddenOpts.add_options()
		("input-file,i", value<string>(), "a carmen log file to be translated to ros msgs")
	;

	po::options_description allOpts("All options, visible and invisible");

	allOpts.add(desc).add(hiddenOpts);

	po::positional_options_description p;
	p.add("input-file", -1);

	po::store(parse_command_line(argc, argv, allOpts), vm);

	po::store(po::command_line_parser(argc, argv).
	          options(allOpts).positional(p).run(), vm);
	po::notify(vm);
	
    if (vm.count("help")) {  
            cout << desc << "\n";
            return 0;
    }

	return 1;

}

int main(int argc, char* argv[])
{

	ros::init(argc, argv, "carmen2ros");

	ros::NodeHandle n;

	po::variables_map vm;

	boost::unordered_map<std::string, int> map;

	if(programInputValidation(argc, argv, vm)){

		if(vm.count("input-file")){

			string carmenLogFile(vm["input-file"].as<string>());

			Carmen_Decrypter carmen_decrypter(vm);

			carmen_decrypter.carmenLogFileReader(carmenLogFile);

			Messages_Publisher messages_publisher(n, &carmen_decrypter, &vm);

			messages_publisher.publishMsgs();

		}

	}

    return 0;

}
