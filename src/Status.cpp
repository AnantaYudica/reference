#include "Status.h"

namespace source
{

Status::Status() :
    m_flag(flag::Status::s_not_test)
{}

Status::Status(const Status& cpy) :
    m_flag(cpy.m_flag)
{}

Status::Status(Status&& mov) :
    m_flag(mov.m_flag)
{}

bool Status::operator=(flag::Status flag)
{
    return Set(flag);
}

Status& Status::operator=(const Status& cpy)
{
    m_flag = cpy.m_flag;
    return *this;
}
	
Status& Status::operator=(Status&& mov)
{
    m_flag = mov.m_flag;
    return *this;
}

bool Status::IsPass() const
{
	return m_flag == flag::Status::s_pass;
}

bool Status::IsError() const
{
	return m_flag == flag::Status::s_error;
}

bool Status::IsNotTest() const
{
	return m_flag == flag::Status::s_not_test;
}

bool Status::IsNotCompleted() const
{
	return m_flag == flag::Status::s_not_completed;
}

bool Status::SetPass()
{
    if (IsNotTest() || IsNotCompleted())
	{
		m_flag = flag::Status::s_pass;
		return true;
	}
	return false;
}

bool Status::SetError()
{
    if (IsNotTest() || IsNotCompleted() || IsPass())
	{
		m_flag = flag::Status::s_error;
		return true;
	}
	return false;
}

bool Status::SetNotTest()
{
    return false;
}

bool Status::SetNotCompleted()
{
    if (IsNotTest())
	{
		m_flag = flag::Status::s_not_completed;
		return true;
	}
	return false;
}

bool Status::Set(flag::Status flag)
{
    return flag == flag::Status::s_error ? SetError() :
		flag == flag::Status::s_not_completed ? SetNotCompleted() :
		flag == flag::Status::s_not_test ? SetNotTest() :
		flag == flag::Status::s_pass ? SetPass() : false;
}

Status::operator const flag::Status() const
{
    return m_flag;
}

} //!source
