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
	~JsonObject();

	//variant<eSimple, int, string> get() const;

	void show(string offset) const;

	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> get(vector<string> path_, eType * type_) const;

private:

	vector<JsonBase*> m_lists;
};