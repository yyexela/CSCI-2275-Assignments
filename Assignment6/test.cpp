#include<iostream>
#include<string>

using namespace std;

int main(){
    string str1 = "alabama";
    string str2 = "allegory";
    cout<<"str1: "<<str1<<endl;
    cout<<"str2: "<<str2<<endl;
    if(str1 > str2) cout<<"str1 > str2"<<endl;
    if(str1 < str2) cout<<"str1 < str2"<<endl;
    if(str1 == str2) cout<<"str1 > str2"<<endl;

    cout<<str1[0]<<endl;
}