#pragma once

#include "MyObject.h"

class MySubObject : public MyObject
{
public:
	RTRELECTION_REGISTER_CLASS(MySubObject, MyObject);

	MySubObject()
	{
		vec2.push_back(std::vector<float>());
		vec2.push_back(std::vector<float>());
		vec2[0].push_back(2.6f);
		vec2[0].push_back(23.6f);
		vec2[1].push_back(2233.6f);
	}

	MySubObject(int a, int b, float c, std::string d)
	{
	}

	MySubObject(const std::vector<int>& d)
	{

	}

	virtual int function3(const std::string& a1)
	{
		return 0;
	}

	virtual int function4(const std::string& a1, const std::vector<int> a2)
	{
		return 0;
	}

	static int function5(int a, int b, float c)
	{
		return 0;
	}

	static void function6(int a)
	{

	}

public:
	std::shared_ptr< MySubObject> myobj = nullptr;

	std::vector<int> vec = {1, 2, 3};

	std::vector< std::vector<float> > vec2;
private:
	int a = 10;
	std::string b = "hello";
};