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

template <class T>
class variantItem
{
public:
    T value;
    bool except_flag;
};

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

	JsonBase(eType type_, const wstring& name_, shared_ptr<ErrorStatus> error_);
	JsonBase();

	virtual ~JsonBase();	

	virtual void reset(vector<wstring> path_, variant<wstring, double, JsonBase::eSimple> content_);
	virtual variant<eSimple, double, wstring, eGetterMsg> get(vector<wstring> path_, eType* type_) const;
	virtual void show(wstring offset) const;
	virtual void set(vector<wstring> path_, const wstring& name_, JsonBase::eType type_, std::variant<wstring, double, JsonBase::eSimple> arg_);
	virtual wstring to_string(const wstring& offset_, bool without_name, bool end_with_comma_) const;

    template <class T>
    variantItem<T> variantExp(const vector<wstring>& path_) const;

    template <class T>
    variantItem<T> variantExp(const vector<wstring>& path_, ErrorStatus::error error_);

	wstring Name() const;

protected:
	eType m_type;
	wstring m_name;
	shared_ptr<ErrorStatus> p_error;

private:

};

template<class T>
variantItem<T> JsonBase::variantExp(const vector<wstring>& path_) const
{
    eType type_;
    variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> o_variant = get(path_, &type_);

    variantItem<T> result;
    try
    {
        result.value = std::get<T>(o_variant);
        result.except_flag = false;
    }
    catch(std::bad_variant_access&)
    {
        result.except_flag = true;
    }

    return result;
}

template <class T>
variantItem<T> JsonBase::variantExp(const vector<wstring>& path_, ErrorStatus::error error_)
{
    eType type_;
    variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> o_variant = get(path_, &type_);

    variantItem<T> result;
    try
    {
        result.value = std::get<T>(o_variant);
        result.except_flag = false;
    }
    catch(std::bad_variant_access&)
    {
        result.except_flag = true;
        p_error->set(error_, true);
    }

    return result;
}
