#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <variant>
#include <memory>

#include "config.h"
#include "fileHandler.h"
#include "stringHandler.h"
#include "errorStatus.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::variant;
using std::shared_ptr;
using std::wstring;

class JsonBase
{
public:

	enum class eType {
		base, array, number, object, simple, string 
	};

	enum class eSimple {
		simple_false, simple_true, simple_null
	};

	enum class eGetterMsg {
		not_exist, is_object, is_array, is_base
	};

#ifdef TASK_0_2_5__4
	JsonBase(eType type_, const wstring& name_, shared_ptr<ErrorStatus> error_);
#else
	JsonBase(eType type_, const string& name_, shared_ptr<ErrorStatus> error_);
#endif	

#ifdef TASK_0_2_5__1
	JsonBase();
#endif // TASK_0_2_5__1


	virtual ~JsonBase();	

#ifdef  TASK_0_2_5__4
	virtual variant<eSimple, double, wstring, eGetterMsg> get(vector<wstring> path_, eType* type_) const;
	virtual void show(wstring offset) const;
#else
	virtual variant<eSimple, double, string, eGetterMsg> get(vector<string> path_, eType* type_) const;
	virtual void show(string offset) const;
#endif	

#ifdef TASK_0_2_5__1
#ifdef  TASK_0_2_5__4
	virtual void set(vector<wstring> path_, const wstring& name_, JsonBase::eType type_, std::variant<wstring, double, JsonBase::eSimple> arg_);
#else
	virtual void set(vector<string> path_, const string& name_, JsonBase::eType type_, std::variant<string, double, JsonBase::eSimple> arg_);
#endif
#endif

#ifdef  TASK_0_2_5
#ifdef  TASK_0_2_5__4
	virtual wstring to_string(const wstring& offset_, bool without_name, bool end_with_comma_) const;
#else
	virtual string to_string(const string& offset_, bool without_name, bool end_with_comma_) const;
#endif	
#endif

#ifdef  TASK_0_2_5__4
	wstring Name() const;
#else
	string Name() const;
#endif

protected:

	eType m_type;
#ifdef  TASK_0_2_5__4
	wstring m_name;
#else
	string m_name;
#endif	
	shared_ptr<ErrorStatus> p_error;

private:

};