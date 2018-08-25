#pragma once

#include "types/Variant.h"

namespace RTReflection
{
	class Object : public Variant
	{
	public:
		Object()
		{
			mValue.objectValue = (void*)this;
			mType = ObjectType;
		}

		static const char* getClassName() { return "RTReflection::Object"; }
		static const char* getSuperClassName() { return nullptr; }
	};
}