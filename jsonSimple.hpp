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

#ifdef TASK_0_2_5__4
	JsonSimple(JsonBase::eSimple content_, const wstring& name_, shared_ptr<ErrorStatus> p_error_);
	JsonSimple(const wstring& name_, JsonBase::eSimple content_);
	~JsonSimple();

	virtual void show(wstring offset) const override;
	virtual variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> get(vector<wstring> path, JsonBase::eType* type_) const override;
	virtual wstring to_string(const wstring& offset_, bool without_name_, bool end_with_comma_) const override;
#else
	JsonSimple(JsonBase::eSimple content_, const string& name_, shared_ptr<ErrorStatus> p_error_);
#ifdef  TASK_0_2_5__1
	JsonSimple(const string& name_, JsonBase::eSimple content_);
#endif
	~JsonSimple();

	void show(string offset) const;

	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> get(vector<string> path, JsonBase::eType* type_) const;
#ifdef  TASK_0_2_5
	virtual string to_string(const string& offset_, bool without_name_, bool end_with_comma_) const override;
#endif
#endif

private:

	JsonBase::eSimple m_content;

};