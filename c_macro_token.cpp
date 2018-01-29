#include "c_macro_token.hpp"

cMacroToken::cMacroToken(const string & buffer) : cBaseToken(cBaseToken::TokenType::macro, buffer)
{
	bool rec_name = true;
	bool parenthesis = false;
	bool rec_value = false;

	m_value.clear();

	string line = StringHandler::filter(buffer.substr(7), StringHandler::FBE::begin_and_end, { ' ', '\t' });
	string name;

	for (auto ch : line) {

		if (rec_name) {
			name += ch;
		}

		if (rec_name) {
			if ('(' == ch) {
				parenthesis = true;
			}

			if (parenthesis) {
				if (')' == ch) {
					parenthesis = false;
				}
			}
		}

		if (rec_name && !parenthesis) {
			if (' ' == ch || '\t' == ch) {
				rec_name = false;
				rec_value = true;
			}
		}

		if (rec_value) {
			m_value += ch;
		}

	}

	setName(StringHandler::filter(name, StringHandler::FBE::begin_and_end, { ' ', '\n', '\t', '\\' }));
	m_value = StringHandler::filter(m_value, StringHandler::FBE::all, { '\\', '\n', ' ', '\t' });
}

cMacroToken::~cMacroToken()
{
}

void cMacroToken::show(int offset_) const
{
	cBaseToken::show(offset_);
	cout << cBaseToken::get_offset_string(offset_) << "Token Value: " << endl << m_value << endl;
}

#ifdef  TASK_0_2_5
void cMacroToken::write(const string & dir_, const string & file_name_, const string & mode_)
{
	cBaseToken::write(dir_, file_name_, mode_);
	//cout << "macro" << endl;

	//
	// todo: запись *.ipynb через json_object
	//

	string fill_name = dir_ + "\\\\" + file_name_;
	JsonObject json_object("root");
	json_object.set({}, "test1", JsonBase::eType::string, std::variant<string, double, JsonBase::eSimple>("Hello"));
	json_object.set({}, "test2", JsonBase::eType::array, std::variant<string, double, JsonBase::eSimple>());
	json_object.set({}, "test3", JsonBase::eType::object, std::variant<string, double, JsonBase::eSimple>());
	json_object.set({}, "test4", JsonBase::eType::number, std::variant<string, double, JsonBase::eSimple>(10));
	json_object.set({}, "test5", JsonBase::eType::simple, std::variant <string, double, JsonBase::eSimple>(JsonBase::eSimple::simple_true));
	json_object.set({}, "test6", JsonBase::eType::string, std::variant <string, double, JsonBase::eSimple>("Hello"));

	json_object.set({"test3"}, "test3_1", JsonBase::eType::string, std::variant<string, double, JsonBase::eSimple>("te"));
	json_object.set({ "test3" }, "test3_2", JsonBase::eType::number, std::variant<string, double, JsonBase::eSimple>(-11));
	json_object.set({ "test3" }, "test3_3", JsonBase::eType::object, std::variant<string, double, JsonBase::eSimple>());
	json_object.set({ "test3", "test3_1" }, "test3_1_1", JsonBase::eType::string, std::variant<string, double, JsonBase::eSimple>("te1"));

	json_object.set({"test2"}, "name_1", JsonBase::eType::string, std::variant<string, double, JsonBase::eSimple>("n1"));
	json_object.set({ "test2" }, "name_2", JsonBase::eType::string, std::variant<string, double, JsonBase::eSimple>("n2"));
	json_object.set({ "test2" }, "name_3", JsonBase::eType::string, std::variant<string, double, JsonBase::eSimple>("n3"));
	json_object.set({ "test2" }, "name_4", JsonBase::eType::string, std::variant<string, double, JsonBase::eSimple>("n4"));


	json_object.show("");
	//JsonObject json_object(/*Имя*/);

	//
	// todo: заполняем json_object
	//
	

	//json_object.write(file_name_, "ipynb");



	//if (!std::experimental::filesystem::exists(fill_name)) {
	//	std::ofstream fout(fill_name);
	//	fout << ".. ext-d-state:: false" << endl << endl
	//		<< ".. ext-d-version:: " << PROJECT_VERSION << endl << endl
	//		<< ".. ext-d-token-type:: " << cBaseToken::tokenTypeNames[m_type] << endl << endl
	//		<< ".. ext-d-paragraph:: Общее" << endl << endl << endl
	//		<< ".. ext-d-code-block:: c-lang" << endl << endl
	//		<< getRaw() << endl;
	//	fout.close();
	//}

}
#else
void cMacroToken::write(const string & dir_, const string & file_name_)
{

	cBaseToken::write(dir_, file_name_);

	string fill_name = dir_ + "\\\\" + file_name_;

	if (!std::experimental::filesystem::exists(fill_name)) {
		std::ofstream fout(fill_name);
		fout << ".. ext-d-state:: false" << endl << endl
			<< ".. ext-d-version:: " << PROJECT_VERSION << endl << endl
			<< ".. ext-d-token-type:: " << cBaseToken::tokenTypeNames[m_type] << endl << endl
			<< ".. ext-d-paragraph:: Общее" << endl << endl << endl
			<< ".. ext-d-code-block:: c-lang" << endl << endl
			<< getRaw() << endl;
		fout.close();
	}
}
#endif
