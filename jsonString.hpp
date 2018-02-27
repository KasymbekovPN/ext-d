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

	JsonString(const wstring& content_, const wstring& name_, shared_ptr<ErrorStatus> p_error_);
	JsonString(const wstring& name_, const wstring& content_);
	~JsonString();

	virtual void show(wstring offset) const override;
	virtual void reset(vector<wstring> path_, variant<wstring, double, JsonBase::eSimple> content_) override;
	virtual variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> get(vector<wstring> path_, JsonBase::eType* type_) const override;
	virtual wstring to_string(const wstring& offset_, bool without_name_, bool end_with_comma_) const override;

private:
	wstring m_content;

};