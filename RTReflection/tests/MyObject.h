#pragma once

#include "stdio.h"
#include "RTReflection.h"
#include "types/Object.h"

class MyObject: public RTReflection::Object
{
public:
	RTRELECTION_REGISTER_CLASS(MyObject, RTReflection::Object);

	void function1()
	{
		printf("MyObject function1\n");
	}

	virtual void function2(const std::string& a1)
	{

	}

	virtual int function3(const std::string& a1) = 0;

	virtual int function4(const std::string& a1, const std::vector<int> a2) = 0;

	int a;
protected:

	int function5(const std::string& a1)
	{
		return 0;
	}

	int b;
private:
	int function6(const std::string& a1)
	{
		return 0;
	}

	std::string c;
};