#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<sstream>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file" << endl;
        return;
    }
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        getline(ss, name, ':');
        names.push_back(name);
        
        int s1, s2, s3;
        ss >> s1 >> s2 >> s3;
        int totalScore = s1 + s2 + s3;
        scores.push_back(totalScore);
        grades.push_back(score2grade(totalScore));
    }
    file.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command: " << "\n";
    getline(cin, command);
    size_t spacePos = command.find(' ');
    if (spacePos != string::npos) {
        key = command.substr(spacePos + 1);
        command = command.substr(0, spacePos);
    } else {
        key = "";
    }
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    for (size_t i = 0; i < names.size(); i++) {
        if (toUpperStr(names[i]) == key) {
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            return;
        }
    }
    cout << "---------------------------------\n";
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for (size_t i = 0; i < grades.size(); i++) {
        if (grades[i] == key[0]) {
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}