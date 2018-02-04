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

#ifdef  TASK_0_2_5__4
	JsonString(const wstring& content_, const wstring& name_, shared_ptr<ErrorStatus> p_error_);
	JsonString(const wstring& name_, const wstring& content_);
#else
	JsonString(const string& content_, const string& name_, shared_ptr<ErrorStatus> p_error_);
#ifdef  TASK_0_2_5__1
	JsonString(const string& name_, const string& content_);
#endif
#endif

	~JsonString();

#ifdef  TASK_0_2_5__4
	virtual void show(wstring offset) const override;
#else
	void show(string offset) const;
#endif

#ifdef  TASK_0_2_5__4
	virtual variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> get(vector<wstring> path_, JsonBase::eType* type_) const override;
#else
	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> get(vector<string> path_, JsonBase::eType* type_) const;
#endif

#ifdef  TASK_0_2_5__4
	virtual wstring to_string(const wstring& offset_, bool without_name_, bool end_with_comma_) const override;
#else
#ifdef TASK_0_2_5
	virtual string to_string(const string& offset_, bool without_name_, bool end_with_comma_) const override;
#endif // TASK_0_2_5
#endif


private:

#ifdef  TASK_0_2_5__4
	wstring m_content;
#else
	string m_content;
#endif

};