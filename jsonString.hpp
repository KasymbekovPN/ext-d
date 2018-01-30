#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "jsonBase.hpp"
#include "errorStatus.h"

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;

class JsonString : public JsonBase
{
public:
	JsonString(const string& content_, const string& name_, shared_ptr<ErrorStatus> p_error_);
#ifdef  TASK_0_2_5__1
	JsonString(const string& name_, const string& content_);
#endif
	~JsonString();

	void show(string offset) const;

	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> get(vector<string> path_, JsonBase::eType* type_) const;

#ifdef TASK_0_2_5
	virtual string to_string(const string& offset_, bool without_name_, bool end_with_comma_) const override;
#endif // TASK_0_2_5


private:

	string m_content;
};