/*
    Author: Aryan
    Topic: Loops in CPp
*/
#include<iostream>

using namespace std;

void Generate_MultiplicationTable(int n);
void Generate_Sum_of_N_Numbers(int Number, int sum);
void Find_Factorial(int Number, int sum);
void Find_Factors(int Number, int sum);
void Find_Perfect_number(int number, int sum);
void Find_Prime_number(int number, int sum);
void display_digits(int num, int r);


int main()
{
    int n = 0, sum = 0, F_sum = 1, Fac_sum = 1, Perfect_sum, Prime_sum;
    //Program to print multiplication Table
    Generate_MultiplicationTable(n);
    cout << endl;

    //Generate Sum of N numbers
    Generate_Sum_of_N_Numbers(n,sum);
    cout << endl;

    //Factorial of n
    Find_Factorial(n,F_sum);
    cout << endl;

    //Factors of a number
    Find_Factors(n,Fac_sum);
    cout << endl;

    //Perfect numbers
    Find_Perfect_number(n,Perfect_sum);
    cout << endl;

    //Check whether the number is a prime number or not
    Find_Prime_number(n,Prime_sum);
    cout << endl;

    //display digits
    int number, remainder;
    number = 1724;
    display_digits(number, remainder);

    return 0;
}

void Generate_MultiplicationTable(int Number){
    //Program to print multiplication Table
    cout << "Program to print the Multiplication Number" << endl;
    cout<< "Enter n: ";
    cin >> Number;
    for(int initialValue = 1; initialValue <= 10;initialValue++){
        cout << Number << "X" << initialValue << "=" << initialValue*Number << endl;
    }
}

void Generate_Sum_of_N_Numbers(int Number, int Result){
    //Generate Sum of N numbers
    cout << "Program to generate sum of n numbers" << endl;
    cout<< "Enter N: ";
    cin >> Number;
    for(int InitialValue = 1; InitialValue<=Number; InitialValue++){
        Result = Result + InitialValue;
    }
    cout << "Sum of N numbers is: " << Result << endl; 
}

void Find_Factorial(int Number, int sum){
    //Factorial of n
    cout << "Program to generate the factorial of n" << endl;
    cout << "Enter N: ";
    cin >> Number;
    for(int InitialValue = 1; InitialValue<=Number; InitialValue++){
        sum = sum*InitialValue;
    }
    cout << "Factorial of " << Number << " is " << sum << endl;
}

void Find_Factors(int Number, int sum){
    //Factors of a number
    cout << "Program to generate the factors of a Number" << endl;
    cout << "Enter Number: ";
    cin >> Number;
    for(int InitialValue = 1; InitialValue<=Number; InitialValue++){
        if(Number % InitialValue == 0){
            cout << "Factors of " << Number << " are " << InitialValue << endl;
        }
    }
}

void Find_Perfect_number(int number, int sum){
    cout << "Program to get the Perfect Number" << endl;
    cout << "Enter n:";
    cin >> number;
    sum = 0;
    for(int initial_value = 1; initial_value <= number; initial_value++){
        if(number % initial_value == 0){
            sum = sum + initial_value;
        }
    }
    if((number*2) == sum){
        cout << number << " is a Perfect number" << endl;
    }
    else{
        cout << number << " is not a Perfect number" << endl;
    }
}

void Find_Prime_number(int number, int sum){
    cout << "Program to find whether the number is a prime number or not" << endl;
    cout << "Enter Number:";
    cin >> number;
    sum = 0;
    for(int initial_value = 1; initial_value < number; initial_value++){
        if(number % initial_value == 0){
            sum ++;
        }
    }
    if(sum == 1){
        cout << number << " is a prime number" << endl;
    }
    else{
        cout << number << " is not a prime number" << endl;
    }
}

void display_digits(int num, int r){
    for(int i = 0; i < num; i++){
        if(num>0){
            r = num%10;
            num = num/10;
            cout << r;
        }
    }
    cout << endl;
}

void check_armstrong_number(){
}
