#pragma once

#include <string>
#include <memory>

namespace RTReflection
{
	class Object;

	class Variant
	{
	public:
		Variant()
		{
			reset();
		}

		Variant(const std::nullptr_t)
		{
			reset();
			mObjectRef = nullptr;
			mValue.objectValue = nullptr;
			mType = ObjectType;
		}
		
		Variant(const std::shared_ptr<Object>& object)
		{
			reset();
			mObjectRef = object;
			mValue.objectValue = object.get();
			mType = ObjectType;
		}

		Variant(const std::string& value)
		{
			reset();
			mStringValueCopy = value;
			mValue.stringValue = const_cast<char*>(mStringValueCopy.c_str());
			mType = String;
		}

		Variant(const char* value)
		{
			reset();
			mStringValueCopy = value;
			mValue.stringValue = const_cast<char*>(mStringValueCopy.c_str());
			mType = String;
		}

		Variant(const Variant& value)
		{
			reset();
			mValue = value.mValue;
			mObjectRef = value.mObjectRef;
			mStringValueCopy = value.mStringValueCopy;
			mArray = std::move(value.mArray);
			mType = value.mType;
		}

		Variant(const uint8_t& value)
		{
			reset();
			memcpy(mValue.holder, &value, sizeof(uint8_t));
			mType = Integer8;
		}

		Variant(const int8_t& value)
		{
			reset();
			memcpy(mValue.holder, &value, sizeof(int8_t));
			mType = Integer8;
		}

		Variant(const uint16_t& value)
		{
			reset();
			memcpy(mValue.holder, &value, sizeof(int16_t));
			mType = Integer16;
		}

		Variant(const int16_t& value)
		{
			reset();
			memcpy(mValue.holder, &value, sizeof(uint16_t));
			mType = Integer16;
		}

		Variant(const int32_t& value) 
		{
			reset();
			memcpy(mValue.holder, &value, sizeof(int32_t));
			mType = Integer32;
		}

		Variant(const uint32_t& value)
		{
			reset();
			memcpy(mValue.holder, &value, sizeof(uint32_t));
			mType = Integer32;
		}

		Variant(const int64_t& value)
		{
			reset();
			memcpy(mValue.holder, &value, sizeof(int64_t));
			mType = Integer32;
		}

		Variant(const uint64_t& value)
		{
			reset();
			memcpy(mValue.holder, &value, sizeof(uint64_t));
			mType = Integer32;
		}

		Variant(const float& value)
		{
			reset();
			memcpy(mValue.holder, &value, sizeof(float));
			mType = Float;
		}

		Variant(const double& value)
		{
			reset();
			memcpy(mValue.holder, &value, sizeof(double));
			mType = Double;
		}

		template<typename _ArrayType>
		Variant(const std::vector<_ArrayType>& array)
		{
			makeArray<_ArrayType>(array, mArray);
			mType = Array;
		}

		Variant(const std::vector<Variant>& array)
		{
			mArray = std::move(array);
			mType = Array;
		}

		template<typename _ArrayType>
		void makeArray(const std::vector<_ArrayType>& array, std::vector<Variant>& outArray)
		{
			for (auto iter = array.begin(); iter != array.end(); ++iter)
			{
				Variant var = *iter;
				outArray.push_back(var);
			}
		}

		template<typename _ArrayType>
		void toStdVector(const std::vector<Variant>& array, std::vector<_ArrayType>& outArray)
		{
			//TODO: convert to std::vector;

			//for (auto iter = array.begin(); iter != array.end(); ++iter)
			//{
			//	Variant& var = *iter;
			//	if(var.getType() == ObjectType)
			//	outArray.push_back(var);
			//}
		}

		//get typed value
		template<typename _DataType>
		_DataType& get()
		{
			return *((_DataType*)&mValue.holder[0]);
		}


		virtual ~Variant()
		{
			reset();
		}

		void reset()
		{
			mObjectRef = nullptr;
			mType = Undefined;
			mValue.objectValue = nullptr;
		}

		enum Type
		{
			Undefined = 0,
			Array,
			Dictionary,
			ObjectType ,
			Float,
			Double,
			Integer8,
			Integer16,
			Integer32,
			Integer64,
			String,
			TYPE_MAX
		};

		union Value
		{
			uint8_t uint8Value;
			int8_t int8Value;
			uint16_t uint16Value;
			int16_t int16Value;
			uint32_t uintValue;
			int32_t intValue;
			float floatValue;
			double doubleValue;
			uint64_t uint64Value;
			int64_t int64Value;
			void* objectValue;
			char* stringValue;
			uint8_t holder[8];
		};

		const Value& getValue() const { return mValue; }

		const Type& getType() const { return mType; }

		const std::shared_ptr<Object>& getObject() const { return mObjectRef; }

		const std::string& getString() const { return mStringValueCopy; }

		void setString(const std::string& value)
		{
			mStringValueCopy = value;
			mValue.stringValue = const_cast<char*>(mStringValueCopy.c_str());
			mType = String;
		}

		std::vector<Variant>& getArray() { return mArray; }
	protected:
		//8 bytes for every value
		Value mValue;

		//hold string
		std::string mStringValueCopy;

		Type mType = Undefined;

		std::shared_ptr<Object> mObjectRef = nullptr;

		//hold array
		std::vector<Variant> mArray;
	};


	template <typename _TypeToCheck>
	bool isSame(const Variant& var)
	{
		Variant::Type type = var.getType();
		bool result = false;
		switch (type)
		{
		case RTReflection::Variant::Undefined:
			result = false;
			break;
		case RTReflection::Variant::Array:
			result = true;//array shold process in set value
			break;
		case RTReflection::Variant::Dictionary:
			result = true;//map shold process in set value
			break;
		case RTReflection::Variant::ObjectType:
			result = true;//object shold process in set value
			break;
		case RTReflection::Variant::Float:
		case RTReflection::Variant::Double:
			result = std::is_floating_point<_TypeToCheck>();
			break;
		case RTReflection::Variant::Integer8:
		case RTReflection::Variant::Integer16:
		case RTReflection::Variant::Integer32:
		case RTReflection::Variant::Integer64:
			result = std::is_integral<_TypeToCheck>();
			break;
		case RTReflection::Variant::String:
			result = true;//string shold process in set value
			break;
		default:
			break;
		}
		return result;
	}
}