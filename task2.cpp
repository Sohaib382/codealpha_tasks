#include <iostream>
#include <fstream>
#include <string>
using namespace std;
bool userExists(string username){
    ifstream file("users.txt");
    string u,p;
    while(file>>u>>p){
        if(u==username){
            return true;
        }
    }
    file.close();
    return false;
}
void registerUser(){
    string username,password;
    cout<<"--- User Registration ---"<<endl;
    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter password: ";
    cin>>password;

    if(userExists(username)){
        cout<<"Error: Username already exists!"<<endl;
        return;
    }

    ofstream file("users.txt",ios::app);
    file<<username<<" "<<password<<endl;
    file.close();

    cout<<"Registration successful!"<<endl;
}
void loginUser(){
    string username,password,u,p;
    cout<<"--- User Login ---"<<endl;
    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter password: ";
    cin>>password;

    ifstream file("users.txt");
    bool found=false;

    while(file>>u>>p){
        if(u==username && p==password){
            found=true;
            break;
        }
    }
    file.close();

    if(found)
        cout<<"Login successful! Welcome "<<username<<"."<<endl;
    else
        cout<<"Error: Invalid username or password!"<<endl;
}

int main(){
    int choice;
    do{
        cout<<"===== Login & Registration System ====="<<endl;
        cout<<"1. Register"<<endl;
        cout<<"2. Login"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;

        if(choice==1)
            registerUser();
        else if(choice==2)
            loginUser();
        else if(choice==3)
            cout<<"Exiting program..."<<endl;
        else
            cout<<"Invalid choice! Try again."<<endl;

    }while(choice!=3);

    return 0;
}
