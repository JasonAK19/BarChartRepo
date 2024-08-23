//
// Created by Jason on 4/23/2023.
//
using namespace std;
#include "Bar.h"
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
Bar::Bar() {}

Bar::Bar(string filename) {
    m_fileName = filename;
    m_data = new LL<string>;
}

Bar::~Bar() {
    delete[] m_data;
    m_data = nullptr;
}

void Bar::Start() {
    LoadFile();
}


void Bar::LoadFile() {
    ifstream
}

void Bar::RemovePunct(std::string &str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }

    while (!str.empty() and ispunct(str.back())) {
        str.pop_back();
    }

    while (!str.empty() and ispunct(str.front())) {
        str.erase(0, 1);
    }

}
