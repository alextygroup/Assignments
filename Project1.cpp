// Authors:     Alexander Rodriguez, Ty Curie Buckner
// Due Date:    2/3/16
// Programming Assignment 1
// Spring 2016 - CS 3358 - 391
//
// Instructor:  Husain Gholoom
//
// Purpose:     The purpose of this program is to allow the user to generate a variably
//              sized square grid of random integers from 1-size of grid and to check
//              if the generated number square is a magic square such that each row,
//              column, and diagonal of the square adds to the same integer.


#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

void popArray(int square[], int Area);
//populates one dimensional array.
void magicCheck(int square[], int Length, int Area);
//creates two dimensional array, outputs it in square form, and checks for magicNumber
bool restartMenu();
//Menu to restart program.
void getSize(int &Length);
//Opening menu telling the user what the program does.
void clearBuffer();
//clears iostream buffer

int main(){
    srand(time(NULL)); //creates a random seed depending on the system TIME

    int Length; //Length of one side of the square.
    int Area; //Length*Length value for contents of square.

    cout << "\nWelcome to my magic sequence program. ";
    cout << "The function of this program is to" << endl;
    cout << endl;
    cout << "  1. Allow the user to enter the size of the magic square";
    cout << "such as N. N >= 2." << endl;
    cout << "  2. Create an array of size N x N." << endl;
    cout << "  3. Populate the array with distinct random numbers." << endl;
    cout << "  4. Display the sum for each row, column, and diagonals";
    cout << "then determine whether" << endl;
    cout << "     the numbers in N x N array are magic";
    cout << "square numbers." << endl << endl;

    do{
        getSize(Length);
        if(Length<2){ //check if Length is above 2
            cout<<"\nError **magic square size Must be >=2"<<endl;
            restartMenu();
            getSize(Length);
        }

        Area = Length*Length;
        int square[Area];//one dimensional array for square.
        popArray(square, Area);

        cout<<"\nThe magic sequence that is created for the size "
        <<Length<<"  :"<<endl<<endl;

        magicCheck(square, Length, Area);
        } while(restartMenu());

    return 0;
}

void popArray(int square[], int Area){
    int newInteger; //newInteger will hold the random number and will be compared to the array
                  //to check for uniqueness.
    bool isUnique;  //true = unique, false = repeated integer

    for(int i=0; i<Area; i++){  //populates array with distinct integers 1-Area
        do{
            isUnique = true;
            newInteger = (rand()% (Area +1));
            for(int j=0; j<Area; j++){
                if (newInteger == square[j])
                    isUnique = false;
            }
        }while(!isUnique);

        square[i] = newInteger;
    }
}

void magicCheck(int square[], int Length, int Area){
    bool isMagicNum = true; //bool value used to check if square is magic
    int twosquare[Length][Length]; //two dimensional array for the square.
    int magicNum = (Length*(Area+1))/2; //equation for magic number
    int* row = new int[Length]; //allocate memory for array of size Length
    int* column = new int[Length]; //allocate memory for array of size Length
    int diagonal [2]={0, 0}; //array for the two diagonals of the square

    for(int i=0; i<Length;i++){
        for(int k=0;k<Length;k++){
            twosquare[i][k] = square[(i*Length)+k];
            //one dimensional array is converted to two dimensional array
            cout<<setw(2)<<right<<twosquare[i][k]<<"  ";
            //formats output
        }
        cout<<endl<<endl;
    }

    cout<<"The magic number is "<<magicNum<<endl;

    for (int x = 0; x < Length; x++){ //initialize array
        row[x] = 0;
        column[x] = 0;
    }

    for(int i=0; i<Length; i++){
        diagonal[0]+= twosquare[i][i];
        diagonal[1]+= twosquare[i][Length-(i+1)];
        for (int k=0; k<Length; k++){
            row[i] += twosquare[i][k];
            column[i] += twosquare[k][i];
        }

        if(row[i]!=magicNum || column[i]!=magicNum)
            isMagicNum = false;
    }

    for(int x = 0; x<Length; x++){
        cout << "\nSum of numbers in Row " << x+1 << " = " << row[x];
    }
    for(int x = 0; x<Length; x++){
        cout << "\nSum of numbers in Column " << x+1 << " = " << column[x];
    }

    cout<<"\nSum of numbers in first diagonal  = "<<diagonal[0];
    cout<<"\nSum of numbers in second diagonal = "<<diagonal[1]<<endl;

    if(isMagicNum)
        cout<<"\nThe above is a magic square"<<endl;
    else
        cout<<"\nThe above is not a magic square"<<endl;

    delete []column; //clears allocated memory
    delete []row;
}

bool restartMenu(){
    char restart; //char the user will input to close or restart the program.
    cout<<"\nWould you like to find another magic square?";
    cout<<"\nEnter 'y' or 'Y' to continue or 'n' or 'N' quit: ";
    cin>>restart;
    cout<<endl<<endl;
    if(restart!='y' && restart!='Y' && restart!='N' && restart!='n'){
        cout<<"Error *** Invalid choice - Must enter y|Y | n|N"<<endl;
        cin>>restart;
    }
    if(restart=='Y'||restart=='y')
        return true;
    else
        return false;
}

void getSize(int &Length){
    cout<<"Enter the size of the magic square : ";

    //forces input of integer type > 1
    while (true){
        cin >> Length;
        if ((cin) && (Length > 1)){
            break;
        }
        cout << "Please enter an integer larger than one: " << flush;
        clearBuffer();
    }
}

void clearBuffer(){
    //clears iostream buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}



