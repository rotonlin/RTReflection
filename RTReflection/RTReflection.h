#pragma once

#include "types/Class.h"
#include "types/Method.h"
#include "types/Field.h"

#define RTRELECTION_REGISTER_CLASS(classType, superClassType)\
friend void rt_register_reflection_function();\
static const char* getClassName() { return #classType; }\
static const char* getSuperClassName() {  return #superClassType; }


#define CAT_IMPL(a, b) a##b
#define CAT(a, b) CAT_IMPL(a, b)

#define RTRELECTION_DEFINE \
static void rt_register_reflection_function(); \
namespace \
{ \
    struct rtRegister \
    { \
        rtRegister()\
        {\
            rt_register_reflection_function();\
        }\
    }; \
}\
static const rtRegister CAT(auto_register__, __LINE__);\
static void rt_register_reflection_function()


namespace RTReflection
{
	//class ClassFactory
	//{
	//public:
	//private:
	//	ClassFactory() {}
	//	~ClassFactory() {}

	//	std::vector<ClassBase> mClassList;
	//};
}