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

#ifdef  TASK_0_2_5__4

	JsonNumber(const wstring& content_, const wstring& name_, shared_ptr<ErrorStatus> p_errro_);
	JsonNumber(const wstring& name_, double content_);

	~JsonNumber();

	void show(wstring offset) const;
	variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> get(vector<wstring> path_, eType * type_) const;
	virtual wstring to_string(const wstring& offset_, bool without_name_, bool wnd_with_comma_) const override;

#else
	JsonNumber(const string& content_, const string& name_, shared_ptr<ErrorStatus> p_errro_);
#ifdef TASK_0_2_5__1
	JsonNumber(const string& name_, double content_);
#endif

	~JsonNumber();

	void show(string offset) const;

	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> get(vector<string> path_, eType * type_) const;

#ifdef  TASK_0_2_5
	virtual string to_string(const string& offset_, bool without_name_, bool wnd_with_comma_) const override;
#endif
#endif

private:

	double m_content;
};