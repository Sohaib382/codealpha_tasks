#include <iostream>
#include <string>
using namespace std;

double gradeToPoint(string grade){
    if(grade=="A+") return 4.0;
    else if(grade=="A") return 3.75;
    else if(grade=="A-") return 3.5;
    else if(grade=="B+") return 3.25;
    else if(grade=="B") return 3.0;
    else if(grade=="B-") return 2.75;
    else if(grade=="C+") return 2.5;
    else if(grade=="C") return 2.25;
    else if(grade=="C-") return 2.0;
    else if(grade=="D+") return 1.5;
    else if(grade=="D") return 1.0;
    else if(grade=="F") return 0.0;
    else return -1.0;
}

int main(){
    int n;
    double semesterCredits=0,semesterGradePoints=0;
    cout<<"Enter number of courses in this semester: ";
    cin>>n;
    for(int i=1;i<=n;i++){
        string grade;
        double credit;
        cout<<"\nCourse "<<i<<endl;
        cout<<"Enter grade (A+, A, A-, B+, B, B-, C+, C, C-, D+, D, F): ";
        cin>>grade;
        cout<<"Enter credit hours: ";
        cin>>credit;
        double gp=gradeToPoint(grade);
        if(gp==-1){
            cout<<"Invalid grade entered!"<<endl;
            return 0;
        }
        semesterCredits+=credit;
        semesterGradePoints+=gp*credit;
    }
    double sgpa=semesterGradePoints/semesterCredits;
    cout<<"\nSemester Credits: "<<semesterCredits<<endl;
    cout<<"Semester Grade Points: "<<semesterGradePoints<<endl;
    cout<<"SGPA: "<<sgpa<<endl;
    double previousCGPA,previousCredits;
    cout<<"\nEnter previous total credits (0 if first semester): ";
    cin>>previousCredits;
    if(previousCredits>0){
        cout<<"Enter previous CGPA: ";
        cin>>previousCGPA;
        double totalCredits=previousCredits+semesterCredits;
        double totalGradePoints=(previousCGPA*previousCredits)+semesterGradePoints;
        double cgpa=totalGradePoints/totalCredits;
        cout<<"\nTotal Credits (All Semesters): "<<totalCredits<<endl;
        cout<<"Final CGPA: "<<cgpa<<endl;
    }else{
        cout<<"\nThis is your first semester."<<endl;
        cout<<"CGPA = SGPA = "<<sgpa<<endl;
    }
    return 0;
}
