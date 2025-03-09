#include "settxt.h"

settxt::settxt(const std::string& txtname) {
    getTxtmap(txtname);
}

void settxt::getTxtmap(const std::string& txtname)
{
    txtmap.clear();
    std::ifstream txt(txtname);
    std::string curLine;

    if (!txt.is_open()) {
        std::cerr << "Cannot open the file: " << txtname << std::endl;
        return;
    }

    while (std::getline(txt, curLine)) {
        size_t pos = curLine.find(':');
        if (pos != std::string::npos) {
            std::string index = curLine.substr(0, pos);
            std::string target = curLine.substr(pos + 1);

            // 移除前後空白
            index.erase(0, index.find_first_not_of(" \t\r\n"));
            index.erase(index.find_last_not_of(" \t\r\n") + 1);
            target.erase(0, target.find_first_not_of(" \t\r\n"));
            target.erase(target.find_last_not_of(" \t\r\n") + 1);

            txtmap[std::move(index)] = std::move(target);
        }
    }

    txt.close();
}

std::string settxt::getValue(const std::string& key, const std::string& defValue) const
{
    auto it = txtmap.find(key);
    return (it != txtmap.end()) ? it->second : defValue;
}