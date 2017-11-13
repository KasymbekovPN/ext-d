//#pragma once 
//
//#include "jsonItem.h"
//
//class JsonSimple: public JsonItem
//{
//public:
//
//	enum SimpleType
//	{
//		simpleNill,
//		simpleFalse,
//		simpleTrue,
//
//		simpleSIZE
//	};
//	
//	JsonSimple();
//	JsonSimple(SimpleType);
//	JsonSimple(SimpleType, const string&);
//	virtual ~JsonSimple();
//
//	virtual void test() const;
//
//	SimpleType get() const override;
//	void set(SimpleType);
//
//private:
//
//	SimpleType m_value;
//};