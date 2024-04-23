#include "base.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    setlocale(LC_ALL, " ");
    string fout("output.txt");
    ifstream fin("test.txt"); 

    student_data students;


    string q;

    getline(fin, q);
    
    students.filetobase(fout);
    students.global_query(q);



    // students.filetobase(fout);
    // students.print_base(fout2);
    // students.select_surname("aboba", surname);
    // students.delete_st(1);
    // students.print_base(fout4);
    // students.edit_st(1, "М", "Калинин", "Георгий", "Тимурович", 106, 3.16, 26, 12, 2003);
    // students.print_base(fout5);

    //students.select_group_number("<=", "206");
    //students.select_rate("<=", "2.56");



    return 0;
}