#include "jsonObject.hpp"

JsonObject::JsonObject(const string & content_, const string& name_, shared_ptr<ErrorStatus> error_) 
	: JsonBase(JsonBase::eType::object, name_, error_)
{

	string filtred_content = StringHandler::filter(content_, StringHandler::FBE::begin_and_end, {' ', '\t', '\n'});
	if ('{' != filtred_content[0] || '}' != filtred_content[filtred_content.size() - 1]) {
		p_error->set(ErrorStatus::error::json_objectInvalid, true);
		return;
	}

	size_t brack_counter = 0;
	size_t sqr_counter = 0;
	vector<string> v;
	string tmp;
	for (size_t i = 1; i < filtred_content.size() - 1; ++i) {
		
		switch (filtred_content[i])
		{
		case '{': brack_counter++; break;
		case '}': brack_counter--; break;
		case '[': sqr_counter++; break;
		case ']': sqr_counter--; break;
		default:
			break;
		}

		if ((0 == brack_counter && 0 == sqr_counter && ',' == filtred_content[i]) ||
			i == filtred_content.size() - 2)
		{

			if (i == filtred_content.size() - 2) { tmp += filtred_content[i]; }

			size_t found_dots = tmp.find_first_of(':');
			if (string::npos == found_dots) {
				p_error->set(ErrorStatus::error::json_invalidSyntax, true);
			}
			else {

				string name = StringHandler::filter(tmp.substr(0, found_dots), StringHandler::FBE::begin_and_end, { ' ', '\t', '\n' });
				if ('"' == name[0] && '"' == name[name.size() - 1]){
					name = name.substr(1, name.size() - 2);

					string value = StringHandler::filter(tmp.substr(found_dots + 1), StringHandler::FBE::begin_and_end, {' ', '\n', '\t'});
					bool first_is_double_quot_mark = '"' == value[0];
					bool last_is_double_quot_mark = '"' == value[value.size() - 1];
					bool first_is_sqr_brack = '[' == value[0];
					bool last_is_sqr_brack = ']' == value[value.size() - 1];
					bool first_is_brace = '{' == value[0];
					bool last_is_brace = '}' == value[value.size() - 1];

					if (first_is_double_quot_mark && last_is_double_quot_mark) {
						m_lists.push_back(new JsonString(
							value.substr(1, value.size() - 2),
							name,
							p_error
						));
					}
					else if (first_is_brace && last_is_brace) {
						m_lists.push_back(new JsonObject(value, name, p_error));
					}
					else if (first_is_sqr_brack && last_is_sqr_brack) {
						m_lists.push_back(new JsonArray(value, name, p_error));
					}
					else if (!first_is_brace && !first_is_double_quot_mark && !first_is_sqr_brack &&
						!last_is_brace && !last_is_double_quot_mark && !last_is_sqr_brack) 
					{
						if ("null" == value) {
							m_lists.push_back(new JsonSimple(JsonBase::eSimple::simple_null, name, p_error));
						}
						else if ("false" == value) {
							m_lists.push_back(new JsonSimple(JsonBase::eSimple::simple_false, name, p_error));
						}
						else if ("true" == value) {
							m_lists.push_back(new JsonSimple(JsonBase::eSimple::simple_true, name, p_error));
						}
						else {
							m_lists.push_back(new JsonNumber(value, name, p_error));
						}
					}
					else {
						p_error->set(ErrorStatus::error::json_invalidSyntax, true);
					}
				}
				else {
					p_error->set(ErrorStatus::error::json_invalidSyntax, true);
				}
			}

			tmp.clear();
		}
		else {
			tmp += filtred_content[i];
		}
	}
}

JsonObject::JsonObject(const string & name_)
{
	m_type = JsonBase::eType::object;
	m_name = name_;
	m_lists.clear();
}

JsonObject::~JsonObject()
{
	for (auto p : m_lists) {
		delete p;
	}
}

void JsonObject::show(string offset) const
{
	JsonBase::show(offset);
	cout << offset << "{\n";
	for (auto i : m_lists) {
		i->show(offset + '\t');
	}
	cout << offset << "}\n";
}

#ifdef TASK_0_2_5__1
void JsonObject::set(vector<string> path_, const string & name_, JsonBase::eType type_, std::variant<string, double, JsonBase::eSimple> arg_)
{
	if (0 == path_.size()){
		switch (type_) {
		case JsonBase::eType::array:
			m_lists.push_back(new JsonArray(name_));
			break;
		case JsonBase::eType::number: {
			double tmp;
			try {
				tmp = std::get<double>(arg_);
			}
			catch (std::bad_variant_access&) {
				tmp = 0;
			}
			m_lists.push_back(new JsonNumber(name_, tmp));
		}  break;
		case JsonBase::eType::object:
			m_lists.push_back(new JsonObject(name_));
			break;
		case JsonBase::eType::simple: {
			JsonBase::eSimple tmp;
			try {
				tmp = std::get<JsonBase::eSimple>(arg_);
			}
			catch (std::bad_variant_access&) {
				tmp = JsonBase::eSimple::simple_null;
			}
			m_lists.push_back(new JsonSimple(name_, tmp));
		}  break;
		case JsonBase::eType::string: {
			string tmp;
			try {
				tmp = std::get<string>(arg_);
			}
			catch (std::bad_variant_access&) {
				tmp = "";
			}
			m_lists.push_back(new JsonString(name_, tmp));
		}  break;
		default:
			break;
		}
	}
	else {

		for (auto iter : m_lists) {
			if (iter->Name() == path_[0]) {
				vector<string> new_path;
				std::copy(path_.begin() + 1, path_.end(), std::inserter(new_path, new_path.begin()));
				iter->set(new_path, name_, type_, arg_);
			}
		}

	}
}
#endif

variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> JsonObject::get(vector<string> path_, eType * type_) const
{
	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> res;

	if (0 == path_.size()) {
		*type_ = m_type;
		res = JsonBase::eGetterMsg::is_object;
		return res;
	}

	for (auto iter : m_lists) {
		
		if (path_[0] == iter->Name()) {
			vector<string> new_path;
			std::copy(path_.begin() + 1, path_.end(), std::inserter(new_path, new_path.begin()));
			res = iter->get(new_path, type_);
			return res;
		}
	}
	
	*type_ = m_type;
	res = JsonObject::eGetterMsg::not_exist;
	return res;
}

#ifdef  TASK_0_2_5
string JsonObject::to_string(const string & offset_, bool without_name_, bool end_with_comma_) const
{
	string res = offset_;
	if (false == without_name_) {
		res += "\"" + m_name + "\" : ";
	}
	res += "{\n";
	for (size_t i = 0; i < m_lists.size(); ++i) {
		res += m_lists[i]->to_string(offset_ + '\t', false, i < m_lists.size() - 1);
		//res += m_lists[i]->to_string(offset_ + '\t', false);
		//res += i < m_lists.size() ? ",\n" : "\n";
	}
	//res += "},\n";
	res += offset_ + (end_with_comma_ ? "},\n" : "}\n");

	return res;
}

void JsonObject::write(const string & path_, const string & mode_)
{
	if ("ipynb" == mode_) {
		JsonObject tmp_json_object = *this;
		tmp_json_object.set({}, "metadata", JsonBase::eType::object, variant<string, double, JsonBase::eSimple>());
		tmp_json_object.set({"metadata"}, "kernelspec", JsonBase::eType::object, variant<string, double, JsonBase::eSimple>());
		tmp_json_object.set({ "metadata", "kernelspec" }, "display_name", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("Python 3"));
		tmp_json_object.set({ "metadata", "kernelspec" }, "language", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("python"));
		tmp_json_object.set({ "metadata", "kernelspec" }, "name", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("python3"));
		tmp_json_object.set({ "metadata" }, "language_info", JsonBase::eType::object, variant<string, double, JsonBase::eSimple>());
		tmp_json_object.set({ "metadata", "language_info"}, "codemirror_mode", JsonBase::eType::object, variant<string, double, JsonBase::eSimple>());
		tmp_json_object.set({ "metadata", "language_info","codemirror_mode" }, "name", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("ipython"));
		tmp_json_object.set({ "metadata", "language_info","codemirror_mode" }, "version", JsonBase::eType::number, variant<string, double, JsonBase::eSimple>(3));
		tmp_json_object.set({ "metadata", "language_info" }, "file_extension", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>(".py"));
		tmp_json_object.set({ "metadata", "language_info" }, "mimetype", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("text/x-python"));
		tmp_json_object.set({ "metadata", "language_info" }, "name", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("python"));
		tmp_json_object.set({ "metadata", "language_info" }, "nbconvert_exporter", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("python"));
		tmp_json_object.set({ "metadata", "language_info" }, "pygments_lexer", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("ipython3"));
		tmp_json_object.set({ "metadata", "language_info" }, "version", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("3.6.3"));
		tmp_json_object.set({}, "nbformat", JsonBase::eType::number, variant<string, double, JsonBase::eSimple>(4));
		tmp_json_object.set({}, "nbformat_mirror", JsonBase::eType::number, variant<string, double, JsonBase::eSimple>(2));

		cout << tmp_json_object.to_string("", true, false) << endl;
	}
}
#endif
