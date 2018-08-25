#pragma once

#include "types/Field.h"
#include "types/Class.h"
#include "types/Variant.h"
#include "types/Object.h"
#include <memory>
#include <assert.h>
#include <functional>

namespace RTReflection
{
	template<typename _classType,
			typename _functionType>
	class Method : public Type
	{
	public:
		Method(const std::string& name, _functionType funcType, AccessType acc)
		{
			mName = name;
			mFuncPointer = funcType;
			mAccessType = acc;
		}

		~Method()
		{
			mFuncPointer = nullptr;
		}

		//invok static function
		template<typename _returnType, typename..._paramTypes>
		_returnType invok(_paramTypes... params)
		{
			if (std::is_void<_returnType>())
			{
				(mFuncPointer)(params...);
			}
			else
			{
				return (mFuncPointer)(params...);
			}

			return _returnType();
		}

		//invok member function
		template<typename _returnType, typename..._paramTypes>
		_returnType invok(_classType* object, _paramTypes... params)
		{
			if (std::is_void<_returnType>())
			{
				(object->*mFuncPointer)(params...);
			}
			else
			{
				return (object->*mFuncPointer)(params...);
			}
			return _returnType();
		}
	private:
		//std::function<_returnType(_paramTypes...)> mFunction = nullptr;
		_functionType mFuncPointer;
	};
}