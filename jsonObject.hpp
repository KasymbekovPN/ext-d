#pragma once

#include <iostream>
#include <string>
#include <string>
#include <variant>
#include <iterator>

#include "jsonBase.hpp"
#include "jsonArray.hpp"
#include "jsonNumber.hpp"
#include "jsonSimple.hpp"
#include "jsonString.hpp"
#include "stringHandler.h"
#include "errorStatus.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::variant;

class JsonObject : public JsonBase
{
public:
	JsonObject(const string& content_, const string& name_, shared_ptr<ErrorStatus> error_);
#ifdef TASK_0_2_5__1
	JsonObject(const string& name_);
#endif

	~JsonObject();

	void show(string offset) const;
//#ifdef  TASK_0_2_5__1
//	void push_back(const string& name, const JsonArray& new_item_);
//	void push_back(const );
//#endif

#ifdef TASK_0_2_5__1
	virtual void set(vector<string> path_, const string& name_, JsonBase::eType type_, std::variant<string, double, JsonBase::eSimple> arg_) override;
#endif


	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> get(vector<string> path_, eType * type_) const;

#ifdef  TASK_0_2_5
	virtual string to_string(const string& offset_, bool without_name_, bool end_with_comma_) const override;
	void write(const string& path_, const string& mode_);
#endif

//#ifdef  TASK_0_2_5__1
//	template <class T>
//	void set(vector<string> path_, const T& new_item_);
//#endif

private:

	vector<JsonBase*> m_lists;
};
