#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <map>
#include "types/Type.h"
#include "types/Method.h"

namespace RTReflection
{
	template<typename _classType>
	class Class : public Type
	{
	public:
		Class()
		{
			getTypeName();
			getSuperClassName();
		}

		virtual const std::string& getTypeName()
		{
			return getClassName();
		}

		const std::string& getClassName()
		{
			if (mName.size() <= 0) 
				mName = _classType::getClassName();
			return mName;
		}

		const std::string& getSuperClassName()
		{
			if (mSuperClassName.size() <= 0)
				mSuperClassName = _classType::getSuperClassName();
			return mSuperClassName;
		}

		const FieldList& getFields() const
		{
			return mFeilds;
		}

		const MethodList& getMethods() const
		{
			return mMethods;
		}

		template<typename _fieldType>
		Class<_classType>& field(const std::string& name, size_t fieldOffset , AccessType acctype)
		{
			std::shared_ptr<Type> field(static_cast<Type*>(new Field<_fieldType>(
															name,
															this,
															fieldOffset,
															FieldAccessor<_fieldType>(),
															acctype)));
			mFeilds[name] = field;
			mSortedFeilds[name] = field;

			return *this;
		}

		template<typename... _paramTypes>
		Class<_classType>& constructor(const std::string& name, size_t functionAddress, AccessType acctype)
		{


			return *this;
		}

		template<typename _functionType>
		Class<_classType>& method(const std::string& name, _functionType functionAddress, AccessType acctype)
		{
			std::shared_ptr<Type> method(static_cast<Type*>(new Method <_classType, _functionType>(
				name,
				functionAddress,
				acctype)));
			mMethods[name] = method;
			mSortedMethods[name] = method;

			return *this;
		}


		const RTField& getField(const std::string& name)
		{
			return mFeilds.at(name);
		}

		template<typename _functionType>
		Method<_classType, _functionType> geMethod(const std::string& name, _functionType)
		{
			return *((Method<_classType, _functionType>*)(mMethods.at(name).get()));
		}

	private:
		FieldList mFeilds;
		MethodList mMethods;

		SortedFieldList mSortedFeilds;
		SortedMethodList mSortedMethods;

		std::string mNamespace;
		std::string mSuperClassName = "";
	};

	template<typename _classType>
	Class<_classType>& RTClass()
	{
		static Class<_classType> cls;
		return cls;
	}
}