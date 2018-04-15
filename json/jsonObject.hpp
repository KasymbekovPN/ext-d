#pragma once

#include <iostream>
#include <string>
#include <variant>
#include <iterator>
#include <codecvt>
#include <fstream>
#include <locale>

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

	JsonObject(const wstring& content_, const wstring& name_, shared_ptr<ErrorStatus> error_);
	JsonObject(const wstring& name_);

	~JsonObject();

	void show(wstring offset) const;
	virtual void set(vector<wstring> path_, const wstring& name_, JsonBase::eType type_, std::variant<wstring, double, JsonBase::eSimple> arg_) override;
	virtual void reset(vector<wstring> path_, variant<wstring, double, JsonBase::eSimple> content_) override;
	virtual variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> get(vector<wstring> path_, eType * type_) const;
	virtual wstring to_string(const wstring& offset_, bool without_name_, bool end_with_comma_) const override;
	void write(const string& path_, const string& mode_);
	void write(const string& path_, const string& mode_, bool rewrite_);

private:

	vector<JsonBase*> m_lists;
};
