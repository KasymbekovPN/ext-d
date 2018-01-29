#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "jsonBase.hpp"
#include "jsonNumber.hpp"
#include "jsonObject.hpp"
#include "jsonSimple.hpp"
#include "jsonString.hpp"

using std::vector;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::string;
using std::variant;

class JsonArray : public JsonBase
{
public:
	JsonArray(const string& content_, const string& name_, shared_ptr<ErrorStatus> p_error_);
#ifdef  TASK_0_2_5__1
	JsonArray(const string& name);
#endif
	~JsonArray();

	void show(string offset) const;

#ifdef TASK_0_2_5__1
	virtual void set(vector<string> path_, const string& name_, JsonBase::eType type_, std::variant<string, double, JsonBase::eSimple> arg_) override;
#endif

	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> get(vector<string> path_, eType * type_) const;

#ifdef  TASK_0_2_5
	virtual string to_string(const string& offset_) const override;
#endif

private:

	vector<JsonBase*> m_lists;

};