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
	virtual ~JsonBase();

	virtual variant<eSimple, double, string, eGetterMsg> get(vector<string> path_, eType* type_) const;
	virtual void show(string offset) const;

#ifdef  TASK_0_2_5
	virtual string to_string(const string& offset_) const;
#endif

	string Name() const;

protected:

	eType m_type;
	string m_name;
	shared_ptr<ErrorStatus> p_error;

private:

};