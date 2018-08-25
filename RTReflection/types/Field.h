#pragma once

#include "types/Class.h"
#include "types/Variant.h"
#include "types/Object.h"
#include <memory>
#include <assert.h>

namespace RTReflection
{
	template<typename _dataType>
	class FieldAccessor
	{
	public:
		typedef _dataType AccessorType;

		FieldAccessor() {}

		Variant getValue(const Variant& object, size_t offset)
		{
			uint8_t* ptr = reinterpret_cast<uint8_t*>(object.getValue().objectValue);
			AccessorType& result = *(reinterpret_cast<AccessorType*>(ptr + offset));
			return result;
		}

		void setValue(const Variant& object, Variant data, size_t offset)
		{
			assert(isSame<AccessorType>(data) && "data Variant type isn't match the type of AccessorType in setValue!");

			if (std::is_pointer<AccessorType>())
			{
				return;
			}

			if(std::is_class<AccessorType>())
			{
				setObjectValue(object, data, offset);
			}
			else
			{
				if (data.getType() != Variant::Undefined)
				{
					uint8_t* ptr = reinterpret_cast<uint8_t*>(object.getValue().objectValue);
					AccessorType& result = *(reinterpret_cast<AccessorType*>(ptr + offset));
					result = data.get<AccessorType>();
				}
			}
		}

		void setObjectValue(const Variant& object ,const Variant& data, size_t offset)
		{
			uint8_t* ptr = reinterpret_cast<uint8_t*>(object.getValue().objectValue);
			if (data.getType() == Variant::String)
			{
				std::string& str = *(reinterpret_cast<std::string*>(ptr + offset));
				str = data.getValue().stringValue;

			}
			else if (data.getType() == Variant::ObjectType)
			{
				std::shared_ptr<Object>& obj = *(reinterpret_cast<std::shared_ptr<Object>*>(ptr + offset));
				obj = data.getObject();
			}
			else if (data.getType() == Variant::Array)
			{
				//AccessorType& obj = *(reinterpret_cast<AccessorType*>(ptr + offset));
				//obj = data.getArray();
			}
		}
	};

	template<typename _dataType>
	class Field: public Type
	{
	public:
		Field(const std::string& name,
			Type* classReference,
			size_t offset,
			FieldAccessor<_dataType> acc,
			AccessType accType)
		{
			mName = name;
			mOffset = offset;
			mClassReference = classReference;
			mAccessor = acc;
			mAccessType = accType;
		}

		virtual const std::string& getTypeName() { return mName; };

		virtual Variant getValue(const Variant& object)
		{
			return mAccessor.getValue(object, mOffset);
		}

		virtual void setValue(const Variant& object, Variant var)
		{
			mAccessor.setValue(object, var, mOffset);
		}
	private:
		Field() {};

		Type* mClassReference = nullptr;

		size_t mOffset = 0;

		FieldAccessor<_dataType> mAccessor;
	};
}