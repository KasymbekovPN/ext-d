#include "c_macro_token.hpp"

cMacroToken::cMacroToken(const string & buffer) : cBaseToken(cBaseToken::TokenType::macro)
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

void cMacroToken::show() const
{
	cBaseToken::show();
	cout << "Token Value: " << endl << m_value << endl;
}
