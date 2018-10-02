#ifndef SOURCE_FLAG_STATUS_H_
#define SOURCE_FLAG_STATUS_H_

namespace source
{
namespace flag
{

typedef unsigned char StatusIntegerType;

enum Status : StatusIntegerType
{
	s_undefined,
    s_pass,
	s_error,
	s_not_test,
	s_not_completed
};

} //!flag

} //!source

#endif //!SOURCE_FLAG_STATUS_H_
