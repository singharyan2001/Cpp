/*
    Author:
    Topic:
*/
#include<iostream>

using namespace std;

void Generate_MultiplicationTable(int n, int i);
void Generate_Sum_of_N_Numbers(int Number, int InitialValue, int sum);
void Find_Factorial(int Number, int InitialValue, int sum);
void Find_Factors(int Number, int InitialValue, int sum);

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
    int NN, iii, F_sum = 1;
    cout << "Enter NN: ";
    cin >> NN;
    Find_Factorial(NN, iii, F_sum);

    //Factors of a number
    int NNN, iv, Fac_sum;
    cout << "Enter Number: ";
    cin >> NNN;
    Find_Factors(NNN, iv, Fac_sum);

    return 0;
}

void Generate_MultiplicationTable(int Number, int initialValue){
    for(initialValue = 1; initialValue <= 10;initialValue++){
        cout << Number << "X" << initialValue << "=" << initialValue*Number << endl;
    }
}

void Generate_Sum_of_N_Numbers(int Number, int InitialValue, int Result){
    for(InitialValue = 1; InitialValue<=Number; InitialValue++){
        Result = Result + InitialValue;
    }
    cout << "Sum of N numbers is: " << Result << endl; 
}

void Find_Factorial(int Number, int InitialValue, int sum){
    for(InitialValue = 1; InitialValue<=Number; InitialValue++){
        sum = sum*InitialValue;
    }
    cout << "Factorial of " << Number << " is " << sum << endl;
}

void Find_Factors(int Number, int InitialValue, int sum){
    for(InitialValue = 1; InitialValue<=Number; InitialValue++){
        if(Number % InitialValue == 0){
            cout << "Factors of " << Number << " are " << InitialValue << endl;
        }
    }
}
