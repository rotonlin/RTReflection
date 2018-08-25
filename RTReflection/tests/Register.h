#pragma once

#include <stddef.h>
#include "RTReflection.h"
#include "types/Class.h"
#include "types/Field.h"
#include "types/Method.h"
#include "tests/MySubObject.h"


RTRELECTION_DEFINE
{
	RTReflection::RTClass<MySubObject>()
	.method("function4", &MySubObject::function4, RTReflection::AccessType::PUBLIC)
	.method("function5", &MySubObject::function5, RTReflection::AccessType::PUBLIC)
	.method("function6", &MySubObject::function6, RTReflection::AccessType::PUBLIC)
	.field<int>("a", offsetof(MySubObject, a), RTReflection::AccessType::PRIVATE)
	.field<std::string>("b", offsetof(MySubObject, b) , RTReflection::AccessType::PRIVATE)
	.field<std::shared_ptr<MySubObject>>("myobj", offsetof(MySubObject, myobj), RTReflection::AccessType::PUBLIC)
	.field<std::vector<int>>("vec", offsetof(MySubObject, vec), RTReflection::AccessType::PUBLIC)
	.field<std::vector< std::vector<float> >>("vec2", offsetof(MySubObject, vec2), RTReflection::AccessType::PUBLIC);

	printf("hello\n");
}