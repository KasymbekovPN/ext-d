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

	JsonArray(const wstring& content_, const wstring& name_, shared_ptr<ErrorStatus> p_error_);
	JsonArray(const wstring& name);
	~JsonArray();

	virtual void show(wstring offset) const override;

	virtual void set(vector<wstring> path_, const wstring& name_, JsonBase::eType type_, std::variant<wstring, double, JsonBase::eSimple> arg_) override;
	virtual variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> get(vector<wstring> path_, eType * type_) const override;
	virtual wstring to_string(const wstring& offset_, bool without_name_, bool end_with_comma_) const override;

private:

	vector<JsonBase*> m_lists;

};