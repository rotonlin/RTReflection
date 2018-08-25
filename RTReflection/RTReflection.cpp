// RTReflection.cpp : Defines the entry point for the application.
//

#include "RTReflection.h"

#include "types/Class.h"
#include "tests/MySubObject.h"
#include "tests/Register.h"
#include "types/Method.h"

#include <functional>

using namespace RTReflection;

template<typename _objectType, typename _functionType>
void test(_objectType* obj, _functionType funcType)
{
	//std::function<int(const std::string&,const std::vector<int>)> func =
	//	std::bind(funcType, obj, std::placeholders::_1, std::placeholders::_2);

	std::string a1 = "ddd";
	std::vector<int> xx = { 1, 20 };

	//func(a1, xx);
	int res = (obj->*vv)(a1, xx);
}

void testConstructor()
{
	std::shared_ptr<MySubObject> obj(new MySubObject());

	Class<MySubObject> subClass = RTClass<MySubObject>();

	//subClass.geMethod("ddd")->invv
	//test<MySubObject>(obj.get(), &MySubObject::function4);
	//auto method = new Method<MySubObject>("function4", &MySubObject::function4, AccessType::PUBLIC);

	auto method4 = subClass.geMethod("function4", &MySubObject::function4);
	std::string a1 = "ddd";
	std::vector<int> xx = { 1, 20 };
	int res = method4.invok<int>(obj.get(), a1, xx);

	//call static functions
	auto method5 = subClass.geMethod("function5", &MySubObject::function5);
	res = method5.invok<int>(1, 2, 3.3f);

	auto method6 = subClass.geMethod("function6", &MySubObject::function6);
	method6.invok<void>(1);
}

void testFieldAcc()
{
	std::shared_ptr<MySubObject> obj(new MySubObject());

	Class<MySubObject> subClass = RTClass<MySubObject>();

	//const FieldList& fields = subClass.getFields();

	Variant var1 = 100.5;

	var1 = 200;

	Variant aaa;
	aaa = var1;

	Variant objVar = obj;


	Variant result = subClass.getField("a")->getValue(objVar);

	Variant result2 = subClass.getField("b")->getValue(objVar);

	subClass.getField("a")->setValue(objVar, 3238);
	subClass.getField("b")->setValue(objVar, "hehehaha");

	printf("%d %d\n", sizeof(std::shared_ptr<MySubObject>), sizeof(std::shared_ptr<Object>));

	//static_assert(sizeof(void *) ==2, "64-bit code generation is not supported.");

	std::shared_ptr<MySubObject> objnext(new MySubObject());
	Variant objnextV = objnext;
	subClass.getField("myobj")->setValue(objVar, objnextV);


	//test vector
	Variant arrayVar = subClass.getField("vec")->getValue(objVar);
	std::vector<Variant>& arrayAcc = arrayVar.getArray();
	arrayAcc[0] = 100;

	//TODO
	//set vector
	subClass.getField("vec")->setValue(objVar, arrayAcc);

	//get 2d vector
	Variant arrayVar2 = subClass.getField("vec2")->getValue(objVar);
	std::vector<Variant>& arrayAcc2 = arrayVar.getArray();
}

int main()
{
	testConstructor();
	testFieldAcc();


	return 0;
}


