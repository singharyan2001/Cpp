/*
    Author:
    Topic:
*/
#include<iostream>
using namespace std;

void Grades(int m1,int m2,int m3);

int main()
{
    Grades(10,11,12);
    return 0;
}

void Grades(int m1,int m2,int m3)
{
    float Total,Avg;
    Avg = (m1+m2+m3)/3;
    
    //write nested if statements to print grades
    if( Avg >= 60){
        cout << 'A';
    }
    else{
        if(Avg >= 35 && Avg < 60){
            cout << 'B';
        }
        else{
            cout << 'C';
        }
    }
}
