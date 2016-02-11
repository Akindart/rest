#ifndef CARMEN__DECRYPTER_H
#define CARMEN__DECRYPTER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>
#include <boost/ptr_container/ptr_vector.hpp>

#include "Message_Factory.h"
#include "Message.h"

using namespace std;
using namespace boost;


class Carmen_Decrypter
{
private:

	ptr_vector<MessageInterface> OdomMsgs;

	ptr_vector<MessageInterface> LaserMsgs;

	ptr_vector<MessageInterface> TFMsgs;

	Message_Factory message_Factory;
	

private:
	
	void readLine(string& str);
	/**
	 * Verifies the type of the message and then downcasts the message received to add it to the respective list of msgs.
	 */
	void addMsgToVector(vector<MessageInterface *>& msgs);

public:
	Carmen_Decrypter();

	Carmen_Decrypter(variables_map &config);

	void carmenLogFileReader(string& fileName);

	ptr_vector<MessageInterface>* getOdomMsgs();

	ptr_vector<MessageInterface>* getLaserMsgs();

	ptr_vector<MessageInterface>* getTFMsgs();

	
	
};
#endif
