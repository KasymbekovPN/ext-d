#pragma once 

#include <iostream>
#include <string>
#include <memory>

#include "stringHandler.h"
#include "errorStatus.h"
#include "jsonBase.hpp"

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::variant;

class JsonNumber : public JsonBase
{
public:
	JsonNumber(const string& content_, const string& name_, shared_ptr<ErrorStatus> p_errro_);
	~JsonNumber();

	void show(string offset) const;

	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> get(vector<string> path_, eType * type_) const;

#ifdef  TASK_0_2_5
	virtual string to_string(const string& offset_) const override;
#endif

private:

	double m_content;
};