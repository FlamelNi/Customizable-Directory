

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const string DELIMIT = ",";

class ExcelToTable {
    public:
    string fullHtml = "";
    string title = "";
    string column_left = "";
    string column_right = "";
    vector<vector<string>> rows = vector<vector<string>>{};

    void addRows(string a, string b) {
        rows.push_back(vector<string>{a, b});
    }
    void addRows(vector<string> strs) {
        rows.push_back(strs);
    }

    string getTitle() {
        return "<h1 class=\"display-4\" id=\"station_name\">"+ this->title + "</h1>";
    }

    string firstRow() {
        string s = "";
        s = s + "" + "\n";
        return s;
    }

    string getRows() {
        string s = "";
        s = s + "" + "\n";
        return s;
    }
    
    void findInTemplet() {

    }

    void modifyHtml() {
        

        // cout << tempHTML;

        // fout.open("index.html");
        // fout.close();

    }
};

string getSubstrByDelimiter(string s, int index) {
    string temp = "";
    for (int i = 0; i <= index; i++) {
        int nextFound = s.find(DELIMIT);
        temp = s.substr(0, nextFound);
        s = s.substr(nextFound+1);
    }
    return temp;
}

ExcelToTable readExcelFormat() {
    ExcelToTable formatData;
    ifstream fin;
    string s;

    //reading directory excel format
    fin.open("directory.csv");

    getline(fin, s);
    // cout << getSubstrByDelimiter(s, 1) << endl;
    formatData.title = getSubstrByDelimiter(s, 1);

    getline(fin, s);
    // cout << getSubstrByDelimiter(s, 1) << endl;
    // cout << getSubstrByDelimiter(s, 3) << endl;

    
    while (!fin.eof()) {
        getline(fin, s);
        //feed this to format data vector
    }

    fin.close();
    return formatData;
}

string readHtmlTemplet() {
    string tempHTML = "";
    ifstream fin;
    string s = "";

    fin.open("indexTemplet.html");
    
    while (!fin.eof()) {
        getline(fin, s);
        tempHTML = tempHTML + s + "\n";
    }
    fin.close();
    return tempHTML;
}


int main() {
    string s = "";
    string title = "";
    string left = "";
    string right = "";

    ifstream fin;
    // ofstream fout;

    ExcelToTable formatData = readExcelFormat();
    
    formatData.fullHtml = readHtmlTemplet();
    std::cout << formatData.fullHtml;

    formatData.modifyHtml();

    
    return 0;
}


