#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;


class settxt
{
public:
    explicit settxt(const std::string& txtname);
    void getTxtmap(const std::string& txtname);
    std::string getValue(const std::string& key, const std::string& defValue = "") const;

private:
    std::map<std::string, std::string> txtmap;
};

