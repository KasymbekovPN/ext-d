#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <fstream>
#include <filesystem>

#include "stringHandler.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

class Dom
{
public:

	enum class item { html, body, head,
					  p, h1, h2, h3, h4, h5, h6, br, hr, blockquote, pre, div, span,
					  em, strong, i, b, u, s, big, tag_small, bling, marquee, 
					  sub, sup, font, ul, ol, li, dl, dt, dd, img, a, 
					  table, caption, th, tr, td, title, style
	};

	typedef map<item, string> ItemNames;
	static ItemNames itemNames;

	Dom(item, bool, const string&, const string&, const string&, const string&);
	~Dom();

	void set(item, const string&, const string&, const string&);
	void set(vector<string>, item, const string&, const string&, const string&);
	Dom* getItem(const string&);
	string getName() const;
	void make_doc();
	string getAsString(int tab_offset) const;
	void show(int) const;

private:

	item m_item;

	bool m_root;

	string m_outfile_path;
	string m_arg;
	string m_str;
	string m_dom_name;

	vector<Dom*> items;

};