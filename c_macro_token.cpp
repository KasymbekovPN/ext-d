#include "c_macro_token.hpp"

cMacroToken::cMacroToken(const string & buffer) : cBaseToken(cBaseToken::TokenType::macro, buffer)
{
	bool rec_name = true;
	bool parenthesis = false;
	bool rec_value = false;

	m_value.clear();

#ifdef  TASK_0_2_5__4
	string line = StringHandler::filter<string, char>(buffer.substr(7), StringHandler::FBE::begin_and_end, { ' ', '\t' });
#else
	string line = StringHandler::filter(buffer.substr(7), StringHandler::FBE::begin_and_end, { ' ', '\t' });
#endif
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

#ifdef  TASK_0_2_5__4
	setName(StringHandler::filter<string, char>(name, StringHandler::FBE::begin_and_end, { ' ', '\n', '\t', '\\' }));
	m_value = StringHandler::filter<string, char>(m_value, StringHandler::FBE::all, { '\\', '\n', ' ', '\t' });
#else
	setName(StringHandler::filter(name, StringHandler::FBE::begin_and_end, { ' ', '\n', '\t', '\\' }));
	m_value = StringHandler::filter(m_value, StringHandler::FBE::all, { '\\', '\n', ' ', '\t' });
#endif
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
#ifdef  TASK_0_2_5__4

	JsonObject json_object(L"root");
	json_object.set({}, L"cells", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());

	json_object.set({ L"cells" }, L"cell_0", JsonObject::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_0" }, L"cell_type", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"markdown"));
	json_object.set({ L"cells", L"cell_0" }, L"metadata", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_0" }, L"source", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_0", L"source" }, L"source_0", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"### Общее\\n"));
	json_object.set({ L"cells", L"cell_0", L"source" }, L"source_1", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"\\n"));
	json_object.set({ L"cells", L"cell_0", L"source" }, L"source_2", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"Здесь описание"));

	json_object.set({ L"cells" }, L"cell_1", JsonObject::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_1" }, L"cell_type", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"markdown"));
	json_object.set({ L"cells", L"cell_1" }, L"metadata", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_1" }, L"source", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_1", L"source" }, L"source_0", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"```c\\n"));
	json_object.set({ L"cells", L"cell_1", L"source" }, L"source_1", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"#define TEST 1000\\n"));
	json_object.set({ L"cells", L"cell_1", L"source" }, L"source_2", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"\\n"));
	json_object.set({ L"cells", L"cell_1", L"source" }, L"source_3", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"int main(){\\n"));
	json_object.set({ L"cells", L"cell_1", L"source" }, L"source_4", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"\\n"));
	json_object.set({ L"cells", L"cell_1", L"source" }, L"source_5", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"    // ....\\n"));
	json_object.set({ L"cells", L"cell_1", L"source" }, L"source_6", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"\\n"));
	json_object.set({ L"cells", L"cell_1", L"source" }, L"source_7", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"    return 0;\\n"));
	json_object.set({ L"cells", L"cell_1", L"source" }, L"source_8", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"}\\n"));
	json_object.set({ L"cells", L"cell_1", L"source" }, L"source_9", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"```"));
#else
	JsonObject json_object("root");
	json_object.set({}, "cells", JsonBase::eType::array, variant<string, double, JsonBase::eSimple>());

	json_object.set({"cells"}, "cell_0", JsonObject::eType::object, variant<string, double, JsonBase::eSimple>());
	json_object.set({ "cells", "cell_0" }, "cell_type", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("markdown"));
	json_object.set({"cells", "cell_0"}, "metadata", JsonBase::eType::object, variant<string, double, JsonBase::eSimple>());
	json_object.set({ "cells", "cell_0" }, "source", JsonBase::eType::array, variant<string, double, JsonBase::eSimple>());
	json_object.set({ "cells", "cell_0", "source" }, "source_0", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("### Общее\\n"));
	json_object.set({ "cells", "cell_0", "source" }, "source_1", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("\\n"));
	json_object.set({ "cells", "cell_0", "source" }, "source_2", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("Здесь описание"));

	json_object.set({ "cells" }, "cell_1", JsonObject::eType::object, variant<string, double, JsonBase::eSimple>());
	json_object.set({ "cells", "cell_1" }, "cell_type", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("markdown"));
	json_object.set({ "cells", "cell_1" }, "metadata", JsonBase::eType::object, variant<string, double, JsonBase::eSimple>());
	json_object.set({ "cells", "cell_1" }, "source", JsonBase::eType::array, variant<string, double, JsonBase::eSimple>());
	json_object.set({ "cells", "cell_1", "source" }, "source_0", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("```c\\n"));
	json_object.set({ "cells", "cell_1", "source" }, "source_1", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("#define TEST 1000\\n"));
	json_object.set({ "cells", "cell_1", "source" }, "source_2", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("\\n"));
	json_object.set({ "cells", "cell_1", "source" }, "source_3", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("int main(){\\n"));
	json_object.set({ "cells", "cell_1", "source" }, "source_4", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("\\n"));
	json_object.set({ "cells", "cell_1", "source" }, "source_5", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("    // ....\\n"));
	json_object.set({ "cells", "cell_1", "source" }, "source_6", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("\\n"));
	json_object.set({ "cells", "cell_1", "source" }, "source_7", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("    return 0;\\n"));
	json_object.set({ "cells", "cell_1", "source" }, "source_8", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("}\\n"));
	json_object.set({ "cells", "cell_1", "source" }, "source_9", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("```"));
#endif

	cout << 1 << endl;

	json_object.write("C:/projects/external-description/_build_vs/Release/test.ipynb", "ipynb");

	cout << 2 << endl;
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
