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

class JsonSimple : public JsonBase
{
public:
	JsonSimple(JsonBase::eSimple content_, const string& name_, shared_ptr<ErrorStatus> p_error_);
	~JsonSimple();

	void show(string offset) const;

	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> get(vector<string> path, JsonBase::eType* type_) const;

private:

	JsonBase::eSimple m_content;

};