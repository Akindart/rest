#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <boost/lexical_cast.hpp>
#include <tf/transform_datatypes.h>
#include <boost/algorithm/string.hpp>

#include "MessageInterface.h"

using namespace std;
using namespace boost;
using namespace tf;

template <class T>
class Message : public MessageInterface
{

private:

	T msg;

public:

	Message(){};

	inline virtual T* getROSMsg(){return &msg;}	

};

#endif
