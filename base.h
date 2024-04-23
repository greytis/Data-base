#include <iostream>
#include <ctime>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iomanip>


using namespace std;

struct student {
    int id;
    string gender;
    string surname;
    string name;
    string second_name;
    int group_number;
    double rate;
    int day;
    int month;
    int year;    
};

class student_data {
    private:
        vector<student> students;
        int id_next;
    
    public:
        student_data(): id_next(1) {};

        vector<int> intersection(vector<int> nums1, vector<int> nums2) {
            vector<int> result;
            unordered_set<int> set(nums1.begin(), nums1.end());

            for (int num : nums2) {
                if (set.find(num) != set.end()) {
                    result.push_back(num);
                    set.erase(num);
                }
            }

            return result;
        }

        void add_st(const string& gender, const string& surname, const string& name, const string& second_name, int group_number, double rate, int day, int month, int year) {
            students.push_back({id_next++, gender, surname, name, second_name, group_number, rate, day, month, year});
        }
        
        void delete_st(int id) {
            int flag = 0;
            for (int i = 0; i < students.size(); i++) {
                if (students[i].id == id) {
                    students.erase(students.begin() + i);
                    flag = 1;
                }
                if (flag == 1) {
                    students[i].id -=1;
                }
            }
        }

        void edit_st(int id, const string& gender, const string& surname, const string& name, const string& second_name, int group_number, double rate, int day, int month, int year) {
            student stu {id, gender, surname, name, second_name, group_number, rate, day, month, year};
            students.insert(students.begin() + id - 1, stu);
            delete_st(id + 1);
        }

                                                                               
        void print_base(const string& filename) const {
            ofstream fout(filename);
            for (auto it = students.begin(); it != students.end(); it++) {
                    // cout << setw(2) << setfill('0') << 00 << ":";


                fout << it->gender << " " << it->surname << " " << it->name << " " << it->second_name 
                << " " << it->group_number << " " << fixed << setprecision(2) << it->rate << " " << setw(2) << setfill('0') << it->day << 
                "." << setw(2) << setfill('0') << it->month << "." << it->year << endl;
            }
            fout.close();
        }

        int is_correct_st(student& st) const {

            if (st.group_number % 100 > 14 || st.group_number % 100 <= 0 || st.group_number / 100 > 6 || st.group_number / 100 <= 0) {
                printf("%d student's group number is uncorrect\n", st.id);
                return 1;
            }
            switch (st.month) {
                case 4:
                    if (st.day > 30) {
                        printf("%d student's birth date is uncorrect\n", st.id);
                        return 2;
                    }
                    break;
                case 6:
                    if (st.day > 30) {
                        printf("%d student's birth date is uncorrect\n", st.id);
                        return 2;
                    }
                    break;
                case 9:
                    if (st.day > 30) {
                        printf("%d student's birth date is uncorrect\n", st.id);
                        return 2;
                    }
                    break;
                case 11:
                    if (st.day > 30) {
                        printf("%d student's birth date is uncorrect\n", st.id);
                        return 2;
                    }
                    break;
                case 2:
                    if ((st.day > 28 && st.year % 4 != 0) || (st.day > 29 && st.year % 4 == 0)) {
                        printf("%d student's birth date is uncorrect\n", st.id);
                        return 2;
                    }
                    break;
            }

            if (st.rate - 2 < 0 || st.rate - 5 > 0) {
                printf("%d student's rate in uncorrect\n", st.id);
                return 3;
            }                
            return 0;
        }
        
        void is_correct_data() {
            for (auto& student : students) {
                if (is_correct_st(student) > 0) {
                    int id = student.id;
                    delete_st(id);
                }
            }
        }

        void filetobase(const string& filename) {
            ifstream file(filename);
            string line;
            while (getline(file, line)) {
                istringstream ss(line);
                string stu;
                getline(ss, stu, ' ');
                string gender = stu;

                getline(ss, stu, ' ');
                string surname = stu;

                getline(ss, stu, ' ');
                string name = stu;

                getline(ss, stu, ' ');
                string sec_name = stu;

                getline(ss, stu, ' ');
                int group_number = stoi(stu);
                
                getline(ss, stu, ' ');
                size_t dotpos = stu.find('.');
                int integerPart = stoi(stu.substr(0, dotpos));
                int fractionalPart = stoi(stu.substr(dotpos + 1));
                double rate = integerPart + fractionalPart / 100.0;

                getline(ss, stu, ' ');
                string day1, month1, year1;
                stringstream date_ss(stu);
                getline(date_ss, day1, '.');
                getline(date_ss, month1, '.');
                getline(date_ss, year1);
                int day {stoi(day1)};
                int month {stoi(month1)};
                int year {stoi(year1)};

                add_st(gender, surname, name, sec_name, group_number, rate, day, month, year);
            }
            file.close();
        }
        
        /* поля для выборки:
        фамилия только ==
        group number > < >= <= == 
        rate > < 
        year > < >= <= == 
        */

        vector<int> select_surname(const string& order, const string& value) const {
            //ofstream fout3("out3.txt");
            vector<int> result;
            int i = 0;
            for(student stud : students) {
                if (stud.surname == value) {
                    result.push_back(i);
                }
                i++;
            }
            
            return result;

            // for (int j = 0; j < result.size(); j++) {
            //     fout3 << students[result[j]].gender << " " << students[result[j]].surname << " " << students[result[j]].name << " " << students[result[j]].second_name 
            //     << " " << students[result[j]].group_number << " " << students[result[j]].rate << " " << setw(2) << setfill('0') << students[result[j]].day << 
            //     "." << setw(2) << setfill('0') << students[result[j]].month << "." << students[result[j]].year << endl;
            // }
            // fout3 << endl;
            // fout3.close();
        }

        vector<int> select_group_number(const string& order, const string& value1) {
            //ofstream fout3("out6.txt");
            vector<int> result;
            int i = 0;
            int value = stoi(value1);
            if (order == "<") {
                for (student stud : students) {
                    if (stud.group_number < value) {
                        result.push_back(i);
                    }
                    i++;
                }
            }
            if (order == "<=") {
                for (student stud : students) {
                    if (stud.group_number <= value) {
                        result.push_back(i);
                    }
                    i++;
                }
            }
            if (order == ">") {
                for (student stud : students) {
                    if (stud.group_number > value) {
                        result.push_back(i);
                    }
                    i++;
                }
            }
            if (order == ">=") {
                for (student stud : students) {
                    if (stud.group_number >= value) {
                        result.push_back(i);
                    }
                    i++;
                }
            }
            if (order == "==") {
                for (student stud : students) {
                    if (stud.group_number == value) {
                        result.push_back(i);
                    }
                    i++;
                }
            }
            return result;

            // for (int j = 0; j < result.size(); j++) {
            //     fout3 << students[result[j]].gender << " " << students[result[j]].surname << " " << students[result[j]].name << " " << students[result[j]].second_name 
            //     << " " << students[result[j]].group_number << " " << students[result[j]].rate << " " << setw(2) << setfill('0') << students[result[j]].day << 
            //     "." << setw(2) << setfill('0') << students[result[j]].month << "." << students[result[j]].year << endl;
            // }
            // fout3 << endl;

            // fout3.close();
        }

        vector<int> select_rate(const string& order, const string& value1) {
            //ofstream fout3("out6.txt");
            vector<int> result;
            int i = 0;
            size_t dotpos = value1.find('.');
            int integerPart = stoi(value1.substr(0, dotpos));
            int fractionalPart = stoi(value1.substr(dotpos + 1));
            double value = integerPart + fractionalPart / 100.0;

            if (order == "<") {
                for (student stud : students) {
                    if (stud.rate < value) {
                        result.push_back(i);
                    }
                    i++;
                }
            }

            if (order == ">") {
                for (student stud : students) {
                    if (stud.rate > value) {
                        result.push_back(i);
                    }
                    i++;
                }
            }

            return result;
            
            // for (int j = 0; j < result.size(); j++) {
            //     fout3 << students[result[j]].gender << " " << students[result[j]].surname << " " << students[result[j]].name << " " << students[result[j]].second_name 
            //     << " " << students[result[j]].group_number << " " << students[result[j]].rate << " " << setw(2) << setfill('0') << students[result[j]].day << 
            //     "." << setw(2) << setfill('0') << students[result[j]].month << "." << students[result[j]].year << endl;
            // }
            // fout3 << endl;

            // fout3.close();
        }

        vector<int> select_year(const string& order, const string& value1) {
            //ofstream fout3("out6.txt");
            vector<int> result;
            int i = 0;
            int value = stoi(value1);

            if (order == "<") {
                for (student stud : students) {
                    if (stud.year < value) {
                        result.push_back(i);
                    }
                    i++;
                }
            }
            if (order == "<=") {
                for (student stud : students) {
                    if (stud.year <= value) {
                        result.push_back(i);
                    }
                    i++;
                }
            }
            if (order == ">") {
                for (student stud : students) {
                    if (stud.year > value) {
                        result.push_back(i);
                    }
                    i++;
                }
            }
            if (order == ">=") {
                for (student stud : students) {
                    if (stud.year >= value) {
                        result.push_back(i);
                    }
                    i++;
                }
            }
            if (order == "==") {
                for (student stud : students) {
                    if (stud.year == value) {
                        result.push_back(i);
                    }
                    i++;
                }
            }

            return result;

            // for (int j = 0; j < result.size(); j++) {
            //     fout3 << students[result[j]].gender << " " << students[result[j]].surname << " " << students[result[j]].name << " " << students[result[j]].second_name 
            //     << " " << students[result[j]].group_number << " " << students[result[j]].rate << " " << setw(2) << setfill('0') << students[result[j]].day << 
            //     "." << setw(2) << setfill('0') << students[result[j]].month << "." << students[result[j]].year << endl;
            // }
            // fout3 << endl;

            // fout3.close();
        }

        vector<string> split(const string& input, char delim) {
            vector<string> tokens;
            istringstream stream(input);
            string token;

            while (getline(stream, token, delim)) {
                tokens.push_back(token);
            }
            return tokens;
        }

    //    select group  => 201 rating < 3 end
    //    select name == Petrov group>200 end

        vector<int> global_select(const string& query) {
            vector<string> tokens = split(query, ' ');
            vector<int> mid, res;
            for (int k = 0; k <= students.size(); k++) {
                res.push_back(k);
            }
            for (int i = 1; i < tokens.size(); i+=3) {
                if (tokens[i] == "surname") {
                    mid = select_surname(tokens [i+1], tokens[i+2]);
                }
                if (tokens[i] == "group") {
                    mid = select_group_number(tokens[i+1], tokens[i+2]);
                    
                }
                if (tokens[i] == "rate") {
                    mid = select_rate(tokens[i+1], tokens[i+2]);
                }
                if (tokens[i] == "year") {
                    mid = select_year(tokens[i+1], tokens[i+2]);
                }
                res = intersection(mid, res);
                
            }
            
            return res;
        }
        
        int global_query(const string& query) {
            vector<string> tokens = split(query, ' ');
            vector<int> result;

            ofstream ff("a.txt");

            for (int k = 0; k < tokens.size(); k++) {
                ff << tokens[k] << endl;
            }

            if (tokens[0] == "select") {

                result = global_select(query);

                ofstream fout3("out6.txt");
                for (int j = 0; j < result.size(); j++) {
                    fout3 << students[result[j]].gender << " " << students[result[j]].surname << " " << students[result[j]].name << " " << students[result[j]].second_name 
                    << " " << students[result[j]].group_number << " " << students[result[j]].rate << " " << setw(2) << setfill('0') << students[result[j]].day << 
                    "." << setw(2) << setfill('0') << students[result[j]].month << "." << students[result[j]].year << endl;
                }
                fout3 << endl;
                fout3.close();
                return 0;
            }
    
            if (tokens[0] == "add") {
                const string& value1 = tokens[6];
                size_t dotpos = value1.find('.');
                double a = stoi(value1.substr(0, dotpos)) + stoi(value1.substr(dotpos + 1)) / 100.0;
                add_st(tokens[1], tokens[2], tokens[3], tokens[4], stoi(tokens[5]), a, stoi(tokens[7]), stoi(tokens[8]), stoi(tokens[9]));
                return 0;
            }
            
            if (tokens[0] == "delete") {
                result = global_select(query);
                for (int i = 0; i < result.size(); i++) {
                    delete_st(students[result[i]].id);
                }
                return 0;
            }

            printf("Incorrent query\n");
            return 1;
        }

};

       
/*
void print_base() {
            for (auto it = students.begin(); it != students.end(); it++) {

                cout << it->surname<< " " << it->name << " " << it->second_name << " " << it->group_number << " " << it->rate << endl;
            }
        }
***/
        // void print_base(ofstream& fout) {
        //     for (auto it = students.begin(); it != students.end(); it++) {

        //         fout << it->surname<< " " << it->name << " " << it->second_name << " " << it->group_number << " " << it->rate << endl;
        //     }
        // }