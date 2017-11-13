//#pragma once
//
//#include <iostream>
//#include <vector>
//#include <string>
//
//#include "jsonItem.h"
//
//using std::cout;
//using std::endl;
//using std::vector;
//using std::string;
//
//class JsonArray: public JsonItem
//{
//public:
//	JsonArray();
//	JsonArray(const string&);
//	virtual ~JsonArray();
//
//	void push_back(const JsonItem&);
//	JsonItem* at(int);
//
//	virtual void test() const;
//
//private:
//
//	vector<JsonItem*> m_value;
//
//};