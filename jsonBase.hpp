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

	JsonBase(eType type_, const string& name_, shared_ptr<ErrorStatus> error_);
#ifdef TASK_0_2_5__1
	JsonBase();
#endif // TASK_0_2_5__1


	virtual ~JsonBase();

	virtual variant<eSimple, double, string, eGetterMsg> get(vector<string> path_, eType* type_) const;
	virtual void show(string offset) const;

#ifdef TASK_0_2_5__1
	virtual void set(vector<string> path_, const string& name_, JsonBase::eType type_, std::variant<string, double, JsonBase::eSimple> arg_);
#endif

#ifdef  TASK_0_2_5
	virtual string to_string(const string& offset_, bool without_name, bool end_with_comma_) const;
#endif

	string Name() const;

protected:

	eType m_type;
	string m_name;
	shared_ptr<ErrorStatus> p_error;

private:

};