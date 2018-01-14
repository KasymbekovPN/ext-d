#include "dom.hpp"

Dom::ItemNames Dom::itemNames{
	{Dom::item::html, "html" },
	{Dom::item::head, "head" },
	{Dom::item::body, "body"},
	{Dom::item::p, "p"},
	{Dom::item::h1, "h1"},
	{Dom::item::h2, "h2"},
	{Dom::item::h3, "h3"},
	{Dom::item::h4, "h4"},
	{Dom::item::h5, "h5"},
	{Dom::item::h6, "h6"}, 
	{Dom::item::br, "br"},
	{Dom::item::hr, "hr"},
	{Dom::item::blockquote, "blockquote"},
	{Dom::item::pre, "pre"},
	{Dom::item::div, "div"},
	{Dom::item::span, "span"}, 
	{Dom::item::em, "em"},
	{Dom::item::strong, "strong"},
	{Dom::item::i, "i"},
	{Dom::item::b, "b"},
	{Dom::item::u, "u"},
	{Dom::item::s, "s"},
	{Dom::item::big, "big"},
	{Dom::item::tag_small, "small"},
	{Dom::item::bling, "bling"},
	{Dom::item::marquee, "marquee"},
	{Dom::item::sub, "sub"},
	{Dom::item::sup, "sup"}, 
	{Dom::item::font, "font"},
	{Dom::item::ul, "ul"},
	{Dom::item::ol, "ol"},
	{Dom::item::li, "li"},
	{Dom::item::dl, "dl"},
	{Dom::item::dt, "dt"},
	{Dom::item::dd, "dd"},
	{Dom::item::img, "img"},
	{Dom::item::a, "a"},
	{Dom::item::table, "table"},
	{Dom::item::caption, "caption"},
	{Dom::item::th, "th"},
	{Dom::item::tr, "tr"},
	{Dom::item::td, "td"},
	{Dom::item::title, "title"},
	{Dom::item::style, "style"},
	{Dom::item::code, "code"}
};

Dom::Dom(item item_, bool root_, const string & outfile_path_, const string& arg_, const string& str_, const string& dom_name_, size_t reserve_) :
	m_item(item_), m_root(root_), m_outfile_path(outfile_path_), m_arg(arg_), m_str(str_), m_dom_name(dom_name_)
{
	if (reserve_) {
		items.reserve(reserve_);
	}
	else {
		items.clear();
	}	
}

Dom::~Dom()
{
	for (auto i : items) {
		delete i;
	}
}

void Dom::set(item item_, const string & arg_, const string & str_, const string& dom_name_, size_t reserve_)
{
	items.push_back(new Dom(item_, false, "", arg_, str_, dom_name_, reserve_));
}

void Dom::set(vector<string> path_, item item_, const string & arg_, const string & str_, const string & dom_name_, size_t reserve_)
{
	if (path_.size() == 0) {
		string ws;
		items.push_back(new Dom(item_, false, ws, arg_, str_, dom_name_, reserve_));
	}
	else {

		for (auto item : items) {
			if (path_[0] == item->getName()) {

				vector<string> buffer;
				std::copy(path_.begin() + 1, path_.end(), std::inserter(buffer, buffer.begin()));
				getItem(path_[0])->set(buffer, item_, arg_, str_, dom_name_, reserve_);

				break;
			}
		}
	}
}


Dom* Dom::getItem(const string & name_)
{
	for (auto i : items) {
		if (name_ == i->getName()) {
			return i;
		}
	}

	return nullptr;
}

string Dom::getName() const {
	return m_dom_name;
}

void Dom::make_doc()
{
	std::cout << "make html doc : " << m_outfile_path << endl;

	size_t found = m_outfile_path.find_last_of('\\');
	if (string::npos != found) {

		string dir_path = m_outfile_path.substr(0, found - 1);
		vector<string> dirs_names = StringHandler::split(dir_path, L'\\');

		string path = dirs_names[0];

		for (auto iter = dirs_names.begin() + 1; iter != dirs_names.end(); iter++) {
			path += "//" + *iter;
			if (!std::experimental::filesystem::exists(path)) {
				std::experimental::filesystem::create_directory(path);
			}
		}
	}

	std::ofstream fout(m_outfile_path);
	fout << getAsString(0);
	fout.close();
}

string Dom::getAsString(int tab_offset) const
{

	string offset;
	for (int i = 0; i < tab_offset; ++i) {
		offset += '\t';
	}

	string result = offset + "<" + itemNames[m_item] + " " + m_arg + " >";
	result += "\t" + m_str + "\n";

	for (auto item : items) {
		result += item->getAsString(tab_offset + 1);
	}

	if (Dom::item::br != m_item) {
		result += offset + "</" + itemNames[m_item] + ">\n";
	}	

	return result;
}

void Dom::show(int num_offset) const
{

	string offset;
	for (int i = 0; i < num_offset; ++i) {
		offset += '\t';
	}

	std::cout << offset << "<" << itemNames[m_item] << " " << m_arg << " >" << endl;

	if (!m_str.empty()) {
		std::cout << '\t' << offset << m_str << endl;
	}
	
	for (auto iter : items) {
		iter->show(num_offset + 1);
	}

	if (Dom::item::br != m_item) {
		std::cout << itemNames[m_item] << endl;
		std::cout << offset << "</" << itemNames[m_item] << ">" << endl;
	}	
}
