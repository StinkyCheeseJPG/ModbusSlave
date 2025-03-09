#include "settxt.h"

void settxt::getTxtmap(const string& txtname)
{
	txtmap.clear();
	ifstream txt(txtname);
	string curLine;

	if (!txt.is_open()) {
		cerr << "Can not open the file named : " << txtname << endl;
		return;
	}

	while (getline(txt, curLine)){
		int pos = curLine.find(":");
		if (pos != string::npos) {
			string index = curLine.substr(0, pos);
			string target = curLine.substr(pos + 1);
			txtmap.insert({ index, target });
		}
	}

	txt.close();
}

string settxt::getValue(const string& key, string defValue)
{
	auto it = txtmap.find(key);
	if (it != txtmap.end()) {
		return it->second;
	}
	return defValue;
}
