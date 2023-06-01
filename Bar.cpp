#include "Bar.h"
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

Bar::Bar() {};

// Name: Bar (Overloaded Constructor)
// Preconditions: Input file
// Postconditions: m_data is allocated, m_fileName populated
Bar::Bar(std::string filename) {
    m_fileName = filename;
    m_data = new LL<string>();
}

// Name: ~Bar (Destructor)
// Preconditions: m_data has been dynamically allocated
// Postconditions: m_data is empty
Bar::~Bar() {
    delete m_data;
   m_data = nullptr;
}

// Name: Start
// Preconditions: None (filename is available)
// Postconditions: None
void Bar::Start() {
    LoadFile();
   RemoveCommon();
   RemoveSingles();
   SortData();
   DisplayBars();
   Export();
}
// Name: LoadFile()
// Preconditions: m_fileName is populated with good data
// Postconditions: m_data is populated
void Bar::LoadFile() {

    ifstream file;
    string line;
    string revLine;
    int wordCount = 0;

    file.open(m_fileName);
    if(file.is_open()){
        while(getline(file, line)){

             RemovePunct(line);
             // splits each words in the line
            istringstream ss(line);
            string word;
            //each word is inserted in the linked list one by one and is counted
            while (ss >> word){
                wordCount++;
                m_data->Insert(word);
            }

        }
    }

    file.close();
    cout << wordCount << " loaded" << endl;
}

// Name: RemovePunct (passed a string)
// Preconditions: Strings to be evaluated
// Postconditions: Punctuation is removed from string
void Bar::RemovePunct(std::string &str) {
    // turns each letter in every word lower case
    for (size_t i = 0; i < str.length(); ++i) {
        str[i] = tolower(str[i]);
    }

    // iterates through each word in reverse and erases punctuation
    for (int i = str.size() - 1; i >= 0; i--) {
        if (ispunct(str[i])) {
            str.erase(i, 1);
        }
    }

}

// Name: RemoveCommon
// Preconditions: m_data is populated and EXCLUDE_LIST is populated
// Postconditions: m_data will have no words from EXCLUDE_LIST
void Bar::RemoveCommon() {
    string choice;
    //while loop for input validation
    while(choice != "yes" and choice != "no") {
        cout << "would you like to remove all common words? " << endl;
        cin >> choice;
    }

        if (choice == "yes") {

            //nested for loop that removes each word in the exclude list
            for (int i = 0; i < m_data->GetSize(); i++) {
                for (int j = 0; j < EXCLUDE_LIST.size(); j++) {
                    m_data->RemoveAt(EXCLUDE_LIST.at(j));
                }
            }
          cout << "all common words removed" << endl;
        } else if (choice == "no") {
            cout << "ok" << endl;
        }

}

// Name: RemoveSingles
// Preconditions: m_data is populated
// Postconditions: m_data will have no words with a frequency of 1
void Bar::RemoveSingles() {
    string choice;
    int wordCount = 0;
    while(choice != "yes" and choice != "no") {
        cout << "would you like to remove words with a frequency of 1? " << endl;
        cin >> choice;

    }

    if(choice == "yes") {
        int i = 0;
        while (i < m_data->GetSize()) {
            // checks for the frequency of the words
            int count = (*m_data)[i].second;
            // removes word if the frequency = 1
            if (count == 1) {
                wordCount++;
                m_data->RemoveAt((*m_data)[i].first);
            } else {
                // adds to i, moving to the next index
                i++;
            }
        }
        cout << wordCount << " words removed?" << endl;
    }
    else if(choice == "no")
    {
        cout << "ok" << endl;
    }

}

// Name: SortData
// Preconditions: m_data is populated
// Postconditions: m_dataSorted is populated and sorted based on frequency
void Bar::SortData() {
    int size = m_data->GetSize();
    for (int i = 0; i < size; i++) {
        pair<string, int>& data = (*m_data)[i];
        // adds every pair to sorted data, checks for emptiness because of how overloaded operator was implemented
        if(!data.first.empty()) {
            m_dataSorted.insert(make_pair(data.second, data.first));
        }
    }
}

// Name: DisplayBars
// Preconditions:  m_dataSorted is populated
// Postconditions: Bar charts are displayed
void Bar::DisplayBars() {
    // iterates through sorted data backwatds which means the words displays from highest to lowest
    multimap<int, string>::reverse_iterator rit;
    for(rit = m_dataSorted.rbegin(); rit != m_dataSorted.rend(); rit++){
        int count = rit->first;
        cout << rit->second << ": " ;
        // prints an * depending on frequency
        while (count > 0) {
            cout << "*";
            count--;
        }
        cout << endl;
    }
}

// Name: Export
// Preconditions: m_dataSorted is populated
// Postconditions: New export file is created and populated with a formatted bar chart
void Bar::Export() {
    string newFile;
    cout << "What would you like to call the export file?" << endl;
    cin >> newFile;
    // creates a new file
    ofstream exFile(newFile);

    if(!exFile){
        cout << "Error opening the export file." << endl;
    }

    // puts the var information into the new file
    multimap<int, string>::reverse_iterator rit;
    for(rit = m_dataSorted.rbegin(); rit != m_dataSorted.rend(); rit++){
        int count = rit->first;
        exFile << rit->second << ": " ;
        while (count > 0) {
            exFile << "*";
            count--;
        }
        exFile << endl;
    }

    exFile.close();

    cout << "Output to export file " << newFile << endl;
}
