/*
    Author:
    Topic:
*/
#include<iostream>

using namespace std;

void Generate_MultiplicationTable(int n, int i);
void Generate_Sum_of_N_Numbers(int Number, int InitialeValue, int sum);
void Find_Factorial(int Number, int InitialValue, int sum);

int main()
{
    //Program to print multiplication Table
    int n, i;
    cout<< "Enter n: ";
    cin >> n;
    Generate_MultiplicationTable(n, i);

    //Generate Sum of N numbers
    int N, ii, sum = 0;
    cout<< "Enter N: ";
    cin >> N;
    Generate_Sum_of_N_Numbers(N, ii, sum);

    //Factorial of n
    int NN, iii, Fsum = 1;
    cout << "Enter NN: ";
    cin >> NN;
    Find_Factorial(NN, iii, Fsum);

    //Factors of a number
    int NNN, iv, Facsum;

    return 0;
}

void Generate_MultiplicationTable(int Number, int initialeValue){
    for(initialeValue = 1; initialeValue <= 10;initialeValue++){
        cout << Number << "X" << initialeValue << "=" << initialeValue*Number << endl;
    }
}

void Generate_Sum_of_N_Numbers(int Number, int InitialeValue, int Result){
    for(InitialeValue = 1; InitialeValue<=Number; InitialeValue++){
        Result = Result + InitialeValue;
    }
    cout << "Sum of N numbers is: " << Result << endl; 
}

void Find_Factorial(int Number, int InitialValue, int sum){
    for(InitialValue = 1; InitialValue<=Number; InitialValue++){
        sum = sum*InitialValue;
    }
    cout << "Factorial of " << Number << " is " << sum << endl;
}
