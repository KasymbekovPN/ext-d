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
	~JsonArray();

	void show(string offset) const;

	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> get(vector<string> path_, eType * type_) const;

private:

	vector<JsonBase*> m_lists;

};