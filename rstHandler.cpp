#include "rstHandler.hpp"

RstHandler::CMD_NAMES RstHandler::cmd_names = {
	{ RstHandler::cmd::state, ".. ext-d-state" },
	{ RstHandler::cmd::version, ".. ext-d-version" },
	{ RstHandler::cmd::token_type, ".. ext-d-token-type" },
	{ RstHandler::cmd::paragraph, ".. ext-d-paragraph" },
	{ RstHandler::cmd::func_ret, ".. ext-d-func-ret" },
	{ RstHandler::cmd::code_block, ".. ext-d-code-block" },
	{ RstHandler::cmd::func_param, ".. ext-d-func-param" },
	{ RstHandler::cmd::struct_member, ".. ext-d-struct-member" },
	{ RstHandler::cmd::enum_member, ".. ext-d-enum-member" },
	{ RstHandler::cmd::nav, ".. ext-d-nav"}
};

RstHandler::RstHandler(const string& file_name_, const string& out_) : m_file_path(file_name_), m_out_dir(out_)
{

	m_state = false;
	m_version = "<none>";
	m_type = "<none>";

	FileHandler f(file_name_);
	m_file.clear();
	if (f.isExist()) {
		m_file = f.getAsString();
	}	
	
	handler();
}

RstHandler::RstHandler(const string & short_file_name_, const string & out_, const string & content_): 
	m_short_file_name(short_file_name_), m_out_dir(out_), m_file(content_)
{
	handler();
}

void RstHandler::write2html() const
{

	if (m_state) {
		
		string short_name;
		if (!m_short_file_name.empty()) {
			short_name = StringHandler::split(m_short_file_name, '.')[0];
		}
		else {
			short_name = StringHandler::split(m_file_path.filename().string(), '.')[0];
		}

		string title;
		size_t found = short_name.find_last_of('-');
		if (string::npos != found) {
			title = short_name.substr(0, found);
		}
	
		size_t paragraph_idx = 0;
		size_t func_ret_idx = 0;
		size_t code_block_idx = 0;
		size_t func_param_idx = 0;
		size_t struct_member_idx = 0;
		size_t enum_member_idx = 0;
		size_t nav_idx = 0;
		size_t a_idx = 0;

		string html_file_name = m_out_dir + "\\\\" + short_name + ".html";
	
		Dom dom(Dom::item::html, true, html_file_name, "", "", "html", 0);
		dom.set(Dom::item::head, "", "", "head", 0);
		dom.set({ "head" }, Dom::item::title, "", title, "title", 0);
		dom.set(Dom::item::body, "", "", "body", 0);

		for (auto item : m_chanks) {
			string name;

			if (item[0] == cmd_names[cmd::paragraph]) {
				name = "paragraph_" + std::to_string(paragraph_idx++);
				dom.set({ "body" }, Dom::item::div, "", "", name, 0);

				if (!item[1].empty()) {
					dom.set({ "body", name }, Dom::item::h3, "", item[1], "h_" + name, 0);
				}

				if (!item[2].empty()) {
					dom.set({ "body", name }, Dom::item::p, "", item[2], "p_" + name, 0);
				}
			}
			else if (item[0] == cmd_names[cmd::func_ret]) {
				name = "func_ret_" + std::to_string(func_ret_idx++);
				dom.set({ "body" }, Dom::item::div, "", "", name, 0);
				
				if (!item[2].empty()) {
					dom.set({ "body", name }, Dom::item::h3, "", "Возвращает:", "h_" + name, 0);
					dom.set({ "body", name }, Dom::item::p, "", item[2], "p_" + name, 0);
				}

			}
			else if (item[0] == cmd_names[cmd::code_block]) {
				name = "code_block_" + std::to_string(code_block_idx++);
				dom.set({ "body" }, Dom::item::div, "", "", name, 0);

				if (!item[2].empty()) {
					dom.set({ "body", name }, Dom::item::pre, "", "", "pre_" + name, 0);
					dom.set({ "body", name, "pre_" + name }, Dom::item::code, "", "\n" + item[2], "code_pre_" + name, 0);
				}
			}
			else if (item[0] == cmd_names[cmd::func_param]) {
				name = "func_param_" + std::to_string(func_param_idx++);
				dom.set({ "body" }, Dom::item::div, "", "", name, 0);

				if (!item.empty() && !item.empty()) {
					dom.set({ "body", name }, Dom::item::h3, "", "Параметр:", "h_" + name, 0);
					dom.set({ "body", name }, Dom::item::p, "", item[1] + " - " + item[2], "p_" + name, 0);
				}
			}
			else if (item[0] == cmd_names[cmd::struct_member]) {
				name = "struct_member_" + std::to_string(struct_member_idx++);
				dom.set({ "body" }, Dom::item::div, "", "", name, 0);

				if (!item[0].empty() && !item[2].empty()) {
					dom.set({ "body", name }, Dom::item::h4, "", "Член структуры", "h_" + name, 0);
					dom.set({ "body", name }, Dom::item::p, "", item[1] + " - " + item[2], "p_" + name, 0);
				}
			}
			else if (item[0] == cmd_names[cmd::enum_member]) {
				name = "enum_member_" + std::to_string(enum_member_idx++);
				dom.set({ "body" }, Dom::item::div, "", "", name, 0);

				if (!item[0].empty() && !item[2].empty()) {
					dom.set({ "body", name }, Dom::item::h4, "", "Элемент перечисления", "h_" + name, 0);
					dom.set({ "body", name }, Dom::item::p, "", item[1] + " - " + item[2], "p_" + name, 0);
				}
			}
			else if (item[0] == cmd_names[cmd::nav] && !item[1].empty()) {
				name = "nav_" + std::to_string(nav_idx++);
				dom.set({"body"}, Dom::item::nav, "", "", name, 0);

				auto spl = StringHandler::split(item[1], '|');
				for (auto s : spl) {
					string a_name = StringHandler::filter(s, StringHandler::FBE::all, {' ', '\t'}) + ".html";
					string a_item_name = name + "_a_" + std::to_string(a_idx++);
					dom.set({ "body", name }, Dom::item::a, " href=" + a_name, a_name, a_item_name, 0);
				}

			}
		}
		dom.make_doc();
	}

}

void RstHandler::handler()
{
	if (!m_file.empty()) {

		size_t found = 0;
		vector<size_t> found_vector;
		found = m_file.find("..", found);
		while (string::npos != found) {
			found_vector.push_back(found);
			found = m_file.find("..", found + 2);
		}

		for (size_t i = 0; i < found_vector.size(); ++i) {
			string tmp = found_vector.size() - 1 == i
				? m_file.substr(found_vector[i])
				: m_file.substr(found_vector[i], found_vector[i + 1] - found_vector[i]);
			found = tmp.find_first_of('\n');
			string cmd_line = tmp.substr(0, found);
			string cmd, main_arg, text;

			size_t split_found = cmd_line.find("::");
			if (".." == cmd_line.substr(0, 2) && string::npos != split_found) {
				vector<char> filter_list = { ' ', '\n', '\t', '\\' };
				cmd = StringHandler::filter(
					cmd_line.substr(0, split_found), StringHandler::FBE::begin_and_end, filter_list
				);
				main_arg = StringHandler::filter(
					cmd_line.substr(split_found + 2), StringHandler::FBE::begin_and_end, filter_list
				);
				text = StringHandler::filter(
					tmp.substr(found + 1), StringHandler::FBE::begin_and_end, filter_list
				);
			}

			if (cmd_names[cmd::state] == cmd) {
				m_state = "true" == main_arg;
			}
			else if (cmd_names[cmd::version] == cmd) {
				m_version = main_arg;
			}
			else if (cmd_names[cmd::token_type] == cmd) {
				m_type = main_arg;
			}
			else if (cmd_names[cmd::paragraph] == cmd || cmd_names[cmd::func_ret] == cmd ||
				cmd_names[cmd::code_block] == cmd || cmd_names[cmd::func_param] == cmd ||
				cmd_names[cmd::struct_member] == cmd || cmd_names[cmd::enum_member] == cmd ||
				cmd_names[cmd::nav] == cmd) {
				m_chanks.push_back({ cmd, main_arg, text });
			}
		}
	}
}
