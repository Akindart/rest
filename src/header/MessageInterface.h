#ifndef MESSAGEINTERFACE_H
#define MESSAGEINTERFACE_H

class MessageInterface
{

private:

	/**
	 * msg_type value		meaning
	 * 0		odom msgs
	 * 1		laser msgs (coming from ROBOTLASER1)
	 * 2		tf msgs (coming from ROBOTLASER1)
	 * 	
	 * 
	 */

	int msg_type;

public:
	
	virtual int getMsgType(){ return msg_type; };

	virtual void setMsgType(int msg_type){ this->msg_type = msg_type; };

 	virtual ~MessageInterface(){};

};
#endif
