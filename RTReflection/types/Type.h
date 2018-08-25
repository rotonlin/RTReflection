#pragma once

#include "types/Variant.h"

namespace RTReflection
{
	enum AccessType
	{
		PUBLIC,
		PROTECTED,
		PRIVATE
	};

	class Type
	{
	public:
		virtual const std::string& getTypeName() { return mName; };
		virtual Variant getValue(const Variant& object) { return Variant(); }
		virtual void setValue(const Variant& object, Variant var) {}

	protected:
		std::string mName = "RTReflection::Type";
		AccessType mAccessType = PUBLIC;
	};

	//typedefs
	typedef std::shared_ptr<Type> RTField;
	typedef std::shared_ptr<Type> RTMethod;
	typedef std::unordered_map<std::string, RTField> FieldList;
	typedef std::unordered_map<std::string, RTMethod> MethodList;
	typedef std::map<std::string, RTField> SortedFieldList;
	typedef std::map<std::string, RTMethod>  SortedMethodList;
}