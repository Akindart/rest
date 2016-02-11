#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Carmen_Decrypter.h"


Carmen_Decrypter::Carmen_Decrypter()
{
}

Carmen_Decrypter::Carmen_Decrypter(variables_map &config)
{

	this->message_Factory.setConfigs(config);

}

void Carmen_Decrypter::carmenLogFileReader(string& fileName)
{

	ifstream carmenLog;

	carmenLog.open(fileName.c_str());

	if(carmenLog.is_open()){

		string tmpLine;
		
		while(getline(carmenLog, tmpLine)){

			//cout << "here1" << endl;

			readLine(tmpLine);

			//cout << "here2" << endl;

		}	

		//cout << "here3" << endl;

	}

	else {

		cerr << "There was an error while trying to open " << fileName << endl;
		exit(1);

	}

	//cout << "here4" << endl;


}

ptr_vector<MessageInterface> *Carmen_Decrypter::getOdomMsgs()
{
	return &OdomMsgs;
}

ptr_vector<MessageInterface> *Carmen_Decrypter::getLaserMsgs()
{
	return &LaserMsgs;
}

ptr_vector<MessageInterface> *Carmen_Decrypter::getTFMsgs()
{
	return &TFMsgs;
}

void Carmen_Decrypter::readLine(string& str)
{

	vector<MessageInterface *> msgVec;

	msgVec = this->message_Factory.fabricateMsg(str);

	addMsgToVector(msgVec);	

}

void Carmen_Decrypter::addMsgToVector(vector<MessageInterface *>& msgs)
{

	if(msgs.size() > 0 && msgs.at(0)->getMsgType() == 0){

		this->OdomMsgs.push_back(msgs[0]);
}
	if(msgs.size() > 1 && msgs.at(1)->getMsgType() == 1){

		this->LaserMsgs.push_back(msgs[1]);
		this->TFMsgs.push_back(msgs[2]);
		this->TFMsgs.push_back(msgs[3]);

	}

}
