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

#ifdef  TASK_0_2_5__4
	JsonArray(const wstring& content_, const wstring& name_, shared_ptr<ErrorStatus> p_error_);
	JsonArray(const wstring& name);
#else
	JsonArray(const string& content_, const string& name_, shared_ptr<ErrorStatus> p_error_);
#ifdef  TASK_0_2_5__1
	JsonArray(const string& name);
#endif
#endif
	~JsonArray();

#ifdef  TASK_0_2_5__4
	virtual void show(wstring offset) const override;
#else
	void show(string offset) const;
#endif

#ifdef TASK_0_2_5__1
#ifdef  TASK_0_2_5__4
	virtual void set(vector<wstring> path_, const wstring& name_, JsonBase::eType type_, std::variant<wstring, double, JsonBase::eSimple> arg_) override;
#else
	virtual void set(vector<string> path_, const string& name_, JsonBase::eType type_, std::variant<string, double, JsonBase::eSimple> arg_) override;
#endif
#endif

#ifdef  TASK_0_2_5__4
	virtual variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> get(vector<wstring> path_, eType * type_) const override;
#else
	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> get(vector<string> path_, eType * type_) const;
#endif

#ifdef  TASK_0_2_5
#ifdef  TASK_0_2_5__4
	virtual wstring to_string(const wstring& offset_, bool without_name_, bool end_with_comma_) const override;
#else
	virtual string to_string(const string& offset_, bool without_name_, bool end_with_comma_) const override;
#endif	
#endif

private:

	vector<JsonBase*> m_lists;

};