#include "tokenHandler.hpp"

TokenHandler::CMD_NAMES TokenHandler::cmd_names = {
	{TokenHandler::cmd::state, ".. ext-d-state"},
	{TokenHandler::cmd::version, ".. ext-d-version"},
	{TokenHandler::cmd::token_type, ".. ext-d-token-type"},
	{TokenHandler::cmd::paragraph, ".. ext-d-paragraph"},
	{TokenHandler::cmd::func_ret, ".. ext-d-func-ret"},
	{ TokenHandler::cmd::code_block, ".. ext-d-code-block" },
	{TokenHandler::cmd::func_param, ".. ext-d-func-param"},
	{TokenHandler::cmd::struct_member, ".. ext-d-struct-member"},
	{TokenHandler::cmd::enum_member, ".. ext-d-enum-member"}
};

TokenHandler::TokenHandler(std::experimental::filesystem::path file_name_)
{

	m_shortName = file_name_.filename();

	m_state = false;
	m_type = "";
	m_version = "<none>";

	FileHandler file(file_name_.string());

	string file_string = file.getAsString();
	size_t found = 0;
	vector<size_t> found_vector;
	found = file_string.find("..", found);
	while (string::npos != found) {
		found_vector.push_back(found);
		found = file_string.find("..", found + 2);
	}

	for (size_t i = 0; i < found_vector.size(); ++i) {
		string tmp = found_vector.size() - 1 == i
			? file_string.substr(found_vector[i]) 
			: file_string.substr(found_vector[i], found_vector[i + 1] - found_vector[i]);
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
			cmd_names[cmd::struct_member] == cmd || cmd_names[cmd::enum_member] == cmd) {
			m_chanks.push_back({ cmd, main_arg, text });
		}
	}
}

void TokenHandler::write(const string & out_dir)
{
	if (m_state) {

		string title;
		size_t found = m_shortName.string().find_last_of('-');
		if (string::npos != found) {
			title = m_shortName.string().substr(0, found);
		}

		string html_file_name = out_dir + "\\\\" + StringHandler::split(m_shortName.filename().string(), '.')[0] + ".html";

		Dom dom(Dom::item::html, true, html_file_name, "", "", "html", 0);
		dom.set(Dom::item::head, "", "", "head", 0);
		dom.set({"head"}, Dom::item::title, "", title, "title", 0);
		dom.set(Dom::item::body, "", "", "body", 0);

		size_t paragraph_idx = 0;
		size_t func_ret_idx = 0;
		size_t code_block_idx = 0;
		size_t func_param_idx = 0;
		size_t struct_member_idx = 0;
		size_t enum_member_idx = 0;

		for (auto item : m_chanks) {

			string name;

			if (item[0] == cmd_names[cmd::paragraph]) {
				name = "paragraph_" + std::to_string(paragraph_idx++);
				dom.set({"body"}, Dom::item::div, " class = paragraph", "", name, 0);

				if (!item[1].empty()) {
					dom.set({"body", name}, Dom::item::h3, " class = paragraph_h", item[1], "h_" + name, 0);
				}

				if (!item[2].empty()) {
					dom.set({ "body", name }, Dom::item::p, " class = paragpath_p", item[2], "p_" + name, 0);
				}				
			}
			else if (item[0] == cmd_names[cmd::func_ret]) {
				name = "func_ret_" + std::to_string(paragraph_idx++);
				dom.set({ "body" }, Dom::item::div, " class = func_ret", "", name, 0);

				if (!item[2].empty()) {
					dom.set({"body", name}, Dom::item::h3, "class = func_ret_h", "Возвращает:", "h_" + name, 0);
					dom.set({"body", name}, Dom::item::p, " class = func_ret_p", item[2], "p_" + name, 0);
				}

			}
			else if (item[0] == cmd_names[cmd::code_block]) {
				name = "code_block_" + std::to_string(paragraph_idx++);
				dom.set({ "body" }, Dom::item::div, " class = code_block", "", name, 0);

				if (!item[2].empty()) {
					dom.set({"body", name}, Dom::item::pre, "", "", "pre_" + name, 0);
					dom.set({"body", name, "pre_" + name}, Dom::item::code, "", "\n" + item[2], "code_pre_" + name, 0);
				}
			}
			else if (item[0] == cmd_names[cmd::func_param]) {
				name = "func_param_" + std::to_string(paragraph_idx++);
				dom.set({ "body" }, Dom::item::div, " class = func_param", "", name, 0);

				if (!item.empty() && !item.empty()) {
					dom.set({ "body", name }, Dom::item::h3, " class = func_param_h", "Параметр:", "h_" + name, 0);
					dom.set({ "body", name }, Dom::item::p, " class = func_param_p", item[1] + " - " + item[2], "p_" + name, 0);
				}
			}
			else if (item[0] == cmd_names[cmd::struct_member]) {
				name = "struct_member_" + std::to_string(struct_member_idx++);
				dom.set({"body"}, Dom::item::div, " class = struct_member", "", name, 0);

				if (!item[0].empty() && !item[2].empty()) {
					dom.set({"body", name}, Dom::item::h4, " class = struct_member_h", "Член структуры", "h_" + name, 0);
					dom.set({"body", name}, Dom::item::p, " class = struct_member_p", item[1] + " - " + item[2], "p_" + name, 0);
				}
			}
			else if (item[0] == cmd_names[cmd::enum_member]) {
				name = "enum_member_" + std::to_string(enum_member_idx++);
				dom.set({ "body" }, Dom::item::div, " class = enum_member", "", name, 0);

				if (!item[0].empty() && !item[2].empty()) {
					dom.set({ "body", name }, Dom::item::h4, " class = enum_member_h", "Элемент перечисления", "h_" + name, 0);
					dom.set({ "body", name }, Dom::item::p, " class = enum_member_p", item[1] + " - " + item[2], "p_" + name, 0);
				}
			}

		}
		dom.make_doc();
	}
}
