#ifndef SOURCE_STATUS_H_
#define SOURCE_STATUS_H_

#include "flag/Status.h"

namespace source
{

class Status
{
private:
	flag::Status m_flag;
public:
	Status();
	Status(const Status& cpy);
	Status(Status&& mov);
public:
	bool operator=(flag::Status flag);
	Status& operator=(const Status& cpy);
	Status& operator=(Status&& mov);
public:
	bool IsPass() const;
	bool IsError() const;
	bool IsNotTest() const;
	bool IsNotCompleted() const;
	bool SetPass();
	bool SetError();
	bool SetNotTest();
	bool SetNotCompleted();
	bool Set(flag::Status flag);
public:
	operator const flag::Status() const;
};

} //!source

#endif //!SOURCE_STATUS_H_