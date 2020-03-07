
// Normal Mgic Squares (Odd, even)

#include "iostream"
#include "windows.h"
#include "time.h"
#include "random"
#include "chrono"

using namespace std;

// declare our square with max order of 100
const int NMAX = 100;
int MSquare[NMAX][NMAX] = {0};
int MSqNr[NMAX*NMAX];

// we enumerated our Magic Square types
enum MSqType
{
    Odd = 1,
    doublyEven, 
    singlyEven
};


// here we defined our directions moving tricks using 'enum' and 'arrays'
const int dirNr = 6;
enum direction      { UP,    RIGHT,     DOWN,   LEFT,    DOWN_LEFT,   DOWN_RIGHT};
int dir_r[dirNr] =  {-1,     0,         1,      0,       1,           1         };
int dir_c[dirNr] =  { 0,     1,         0,      -1,     -1,           1         };


// prototyping our functions
void magicSquare();

// Print the magic square
void printMSquare(int);

// to check the order to know which type of Magic Square we will generate
int OddEven(int);

// Magic Square validation functions
int sumWithDir(int, int, int, int);
bool validateMagicSquare(int);

// Rotate your Magic Square
void rotateMSq(int);

// for the 3 types of squares where each one has a unique algorithm to solve it
void oddMagicSqaure(int, char);
void doublyEvenMSquare(int, char);
void singlyEvenMSquare(int, char);


int main()
{
    magicSquare();

    return 0;
}




void magicSquare()
{
    int N = 0;              // -> the order of Magic Square
    bool check;             // -> to validate our input
    char mOption;           // -> magic option to get from user the printing option
    char VOption;           // -> validation option to validate your Magic Square
    int mConstant = 0;      // -> to calculate the Magic constant and restore it here
    int OddOrEven = 0;      // -> to classify our order in which Magic Square type it belongs
    

    // to generate again Magic squares
    do
    {
        check = true;

        // This part is for getting form user the Order of the Magic Square
        do
        {
            check = true;

            cout<<"\t\t\t+++ Magic Square Generation +++\n\n\n"
                <<"\n\t- Enter the order you want: ";
            cin>>N;

            // input validation
            if(cin.fail() || N > 100 || N < 3)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                check = false;
                if(cin.fail())
                    cout<<"\n\n\t\t\t!!! You entered Unvalid value,Plz enter your order again.!!!\n\n";
                else
                    cout<<"\n\n\t\t\t!!! Plz enter a value between 3 and 100 !!!\n\n";
            }

        }while(!check);

        // This part is for let the user choose if he want the Magic Square printed step by step or only once at the end
        do
        {
            check = true;

            cout<<"\n\t- Do you want the Magic square printed step by step ?\n"
                <<"\n\t+----------------------------+"
                <<"\n\t- 'y' for yes. \t 'n' for no."
                <<"\n\t+----------------------------+"
                <<"\n\n\t- Your choice is: ";
            cin >>mOption;

            // input validation
            if(cin.fail() || (mOption != 'n' && mOption != 'N' && mOption != 'y' && mOption != 'Y') )
            {
                cin.clear();
                cin.ignore(10000, '\n');
                check = false;
                cout<<"\n\n\t\t\t!!! You entered Unvalid value,Plz enter your order again.!!!\n\n";
            }
        } while (!check);
        

        // if we do it again initialize our 
        //memset(MSquare, 0, sizeof(MSquare[0][0]) * N * N); // there is a problem when I use my array an pass it to other functions
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
                MSquare[i][j] = 0;
        }
        fill(MSqNr, MSqNr + (N*N), true);

        cout<<"\n\n\n";
    
        // to check the category of Magic Square Order
        OddOrEven = OddEven(N);
        if(OddOrEven == Odd)
            oddMagicSqaure(N, mOption);
        else
        {
            if(OddOrEven == doublyEven)
                doublyEvenMSquare(N, mOption);
            else
                singlyEvenMSquare(N, mOption);    
        }

        cout<<"\n\n\n";

        // to rotate the Magic Square if you want
        do
        {
            check = true;

            cout<<"\n\t- Do you want to rotate the Magic Square ?\n"
                <<"\n\t+-----------------------------------------+"
                <<"\n\t- 'y' for yes rotate.\t 'n' no for rotate not."
                <<"\n\t+-----------------------------------------+"
                <<"\n\n\t- Your Option is: ";
            cin>>VOption;

            // input validation
            if(cin.fail() || (VOption != 'y' && VOption != 'Y' && VOption != 'n' && VOption != 'N'))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                check = false;
                cout<<"\n\n\t!!! You entered unvalid value, Plz enter a correct value again !!!\n\n";
            }
            else
            {
                if(VOption == 'y' || VOption == 'Y')
                {
                    do
                    {
                        rotateMSq(N);

                        cout<<"\n";
                        cout<<"\n\t- Rotate again ?\n"
                        <<"\n\t+-----------------------------------------+"
                        <<"\n\t- 'y' for yes rotate.\t 'n' no for rotate not."
                        <<"\n\t+-----------------------------------------+"
                        <<"\n\n\t- Your Option is: ";
                        cin>>VOption;
                        // input validation
                        if(cin.fail() || (VOption != 'y' && VOption != 'Y' && VOption != 'n' && VOption != 'N'))
                        {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            check = false;
                            cout<<"\n\n\t!!! You entered unvalid value, Plz enter a correct value again !!!\n\n";
                        }else
                        {
                            if(VOption == 'y' || VOption == 'Y')
                                check = false;
                            else
                                check = true;
                            
                        }
                    }while(!check);
                } 
            }
        }while(!check);

        cout<<"\n\n\n";

        // to validate the Magic Square if wanted
        do
        {
            check = true;

            cout<<"\n\t- For checking the Magic Square:\n"
                <<"\n\t+-----------------------------------------+"
                <<"\n\t- 'y' for yes check.\t 'n' no check not."
                <<"\n\t+-----------------------------------------+"
                <<"\n\n\t- Your Option is: ";
            cin>>VOption;

            // input validation
            if(cin.fail() || (VOption != 'y' && VOption != 'Y' && VOption != 'n' && VOption != 'N'))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                check = false;
                cout<<"\n\n\t!!! You entered unvalid value, Plz enter a correct value again !!!\n\n";
            }
        }while(!check);

        // to validate your Magic square
        if(VOption == 'y' || VOption == 'Y')
        {
            if(validateMagicSquare(N))
            {
                cout<<"\n\t- The magic Square of Order "<<N<<"X"<<N<<" is valid\n"
                    <<"\n\t- The Magic constant of Order "<<N<<"X"<<N<<" is: ";
                mConstant = N * (N * N + 1) / 2;
                cout<<mConstant;
            }
            else
                cout<<"\n\t- The magic Square of Order "<<N<<"X"<<N<<" is not valid\n";
        }

        cout<<"\n\n\n";

        cout<<"\n\t- Do you want to generate a nother Magic Square:\n"
                <<"\n\t+-----------------------------------------+"
                <<"\n\t- 'y' yes generate a new one.\t 'n' no do not generate."
                <<"\n\t+-----------------------------------------+"
                <<"\n\n\t- Your Option is: ";
        cin>>VOption;

        // input validation
        if(cin.fail() || (VOption != 'y' && VOption != 'Y' && VOption != 'n' && VOption != 'N'))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            check = false;
            cout<<"\n\n\t!!! You entered unvalid value, Plz enter a correct value again !!!\n\n";
        }
        
        cout<<"\n\n\n";
    
    }while(!check || VOption == 'y' || VOption == 'Y');
}

// Print the magic square
void printMSquare(int N)
{
    cout<<"\n\t";
    for(int i = 0; i < N; i++)    
    {
        if(N*N < 100)
            cout<<"_____";
        else
        {
            if(N*N < 1000)
                cout<<"______";
            else
                cout<<"_______";
        }   
    }    
        

    for(int i = 0; i < N; i++)
    {
        cout<<"\n\t| ";
        for(int j = 0; j < N; j++)
        {
            if(N*N < 100)
            {    
                if(MSquare[i][j] < 10)
                    cout<< MSquare[i][j]<<" ";
                else
                    cout<< MSquare[i][j];
                cout<<" | ";
            }
            else
            {
                if(N*N < 1000)
                {
                    if(MSquare[i][j] < 100)
                    {
                        if(MSquare[i][j] < 10)
                            cout<< MSquare[i][j]<<"  ";
                        else
                            cout<< MSquare[i][j]<<" ";
                        
                    }  
                    else
                        cout<< MSquare[i][j];
                    cout<<" | ";
                }else
                {
                    if(MSquare[i][j] < 1000)
                    {
                        if(MSquare[i][j] < 10)
                            cout<< MSquare[i][j]<<"   ";
                        else
                        {
                            if(MSquare[i][j] < 100)
                                cout<< MSquare[i][j]<<"  ";
                            else
                                cout<< MSquare[i][j]<<" ";    
                        }
                    }
                    else
                        cout<< MSquare[i][j];
                    cout<<" | ";
                }
            }
        }
        
        cout<<"\n\t";

        for(int j = 0; j < N; j++)
        {
            if(N*N < 100)
                cout<<"_____";
            else
            {
                if(N*N < 1000)
                    cout<<"______";
                else
                    cout<<"_______";
            }
        }    
    }

    cout<<"\n\n";

}

// to check the order to know which type of Magic Square we will generate
int OddEven(int N)
{
    int evenOddChecker = 0;
    
    if(N % 2 != 0)  // odd is not divisable by 2 so its reminder is always not == 0
        evenOddChecker = Odd;
    else
    {
        if(N % 4 != 0)
            evenOddChecker = singlyEven; // is not divisable by 4 
        else
            evenOddChecker = doublyEven; // is divisable by 4
        
    }
    return evenOddChecker;
}


// Validation functions to check the Magic constant
int sumWithDir(int row, int col, int direction, int N)
{
    int sum = 0;
    for(int i = 0; i < N; i++)
    {
        sum += MSquare[row][col];   // sum the values of the Magic square array in one direction

        row += dir_r[direction];    // switch to next cell in a specific direction
        col += dir_c[direction];
    }
    return sum;
}

bool validateMagicSquare(int N)
{
    int sumDir = 0;
    
    sumDir = sumWithDir(0, 0, RIGHT, N);

    for(int i = 0; i < N; i++)
    {
        if(sumDir != sumWithDir(i,   0, RIGHT, N))  return false;
        if(sumDir != sumWithDir(0,   i, DOWN,  N))  return false;
    }

    if(sumDir != sumWithDir(0, 0,   DOWN_RIGHT, N))   return false;
    if(sumDir != sumWithDir(0, N-1, DOWN_LEFT,  N))   return false;

    return true;
}

// rotations 
void rotateMSq(int N)
{
    int floorDiv = N/2;
    int tmpCell = 0;
    int Order = N-1;

    // to change between cycles
    for(int i = 0; i < floorDiv; i++)
    {
        // to move to the next element to swap it in each cycle
        for(int j = i; j < N-1-i; j++)
        {
             
            tmpCell = MSquare[i][j];  // put the most-top left corner into temp variable
            MSquare[i][j] = MSquare[Order-j][i]; // swap the most-bottom left to most-top left
            MSquare[Order-j][i] = MSquare[Order-i][Order-j];  // swap the most-bottom right to most-bottom left
            MSquare[Order-i][Order-j] = MSquare[j][Order-i];    // swap the most-top right to most-bottom right
            MSquare[j][Order-i] = tmpCell; // swap the empCell value of the most-top left to most-top right
        } 
    }
    printMSquare(N);
}

// Magic Square functions
void oddMagicSqaure(int N, char option)
{
    int row = 0, col = 0;
    int tmpR = 0, tmpC = 0;
    int rdChoice = 0;
    int tmp = 0;
    
    // random generator
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(0, 1);
    rdChoice = distr(eng);

    // assigning 1 to the center of the 1st row
    col = (N / 2);
    MSquare[row][col] = 1;

    // to print the 1st move if we print each step one by one
    if(option == 'y' || option == 'Y')
        printMSquare(N);
    
    // Odd Magic Square Algorithm (Siamese method - Up_Right)
    for(int i = 1; i < N*N; i++)
    {
        tmpR = row; tmpC = col;
        // 1st Step UP
        if(row == 0)
            row = N-1;
        else
            row += dir_r[UP];
        
        // 2nd Step Right
        if(col == (N-1))
            col = 0;
        else
            col += dir_c[RIGHT];
        
        // check to assign the cell valu2
        if(MSquare[row][col] == 0)
            MSquare[row][col] = i+1;
        else
        {
            // Go back to my original position
            row = tmpR;
            col = tmpC;

            // go down
            if(row == N-1)
                row = 0;
            else
                row += dir_r[DOWN];
               
            
            MSquare[row][col] = i+1;
        }

        if(option == 'y' || option == 'Y')
        {
            printMSquare(N);
            Sleep(2000);
        }
    }

    // form Magic square after construction in a different way
    if(rdChoice > 0)
    {
        row = 0; col = 0;

        // interchange one colomn from left with one colomn from the right
        for(; row < N; row++)
        {
            // swapping the elements of the 2 colomns one by one
            tmp = MSquare[row][N-1]; // put the right colomn element in temporarily variable 
            MSquare[row][N-1] = MSquare[row][col]; // put the left cell value into the right cell
            MSquare[row][col] = tmp;    // put the temp vlaue of th right cell into the left cell

            if(option == 'y' || option == 'y')
            {
                printMSquare(N);
                Sleep(2000);
            }
        }

        row--; // to step back one step and stay in our Magic Square
        
        // interchange one row from top with one row from bottom 
        for(; col < N; col++)
        {
            // swapping the elements of the 2 rows one by one
            tmp = MSquare[row][col]; // put the bottom row element into temporarily variable
            MSquare[row][col] = MSquare[0][col]; // put the top row element into the bottom row element
            MSquare[0][col] = tmp; // put the temp value of the bottom row element into the top row element

            if(option == 'y' || option == 'Y')
            {
                printMSquare(N);
                Sleep(2000);
            }
        }   
    }
    
    // to prevent repeat the last square
    if(option == 'n' || option == 'N')
        printMSquare(N);
        
}


void doublyEvenMSquare(int N, char option)
{
    int sideSq = N/4;     // for the 4 side squares
    int centerSq = N/2;
    int count = 0;
    
    int row = 0, col = 0;
    int rdChoice = 0;
    int tmp = 0;
    
    // random generator
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(0, 1);
    rdChoice = distr(eng);


    // filling the 5 square areas
    for( row = 0; row < N; row++)
    {
        
        for(col = 0; col < N; col++)
        {
            // check to fill the upper and lower side squares
            if(row < sideSq || row >= N-sideSq)
            {
                // fill the side square cell
                MSquare[row][col] = ++count;
                MSqNr[count] = false;

                // check to skip the colomns of unspecified squares area to go only to side squares
                if(col == sideSq-1)
                {
                    col += centerSq;
                    count += centerSq;  // '-1' sum count with centerSq to fill the right nr. in the right cell  
                }
            }
                
            
            // check to fill the center square area
            if(row >= sideSq && row < N-sideSq)
            {
                // check the left boundery
                if(col == 0)
                {
                    col += sideSq;
                    count += sideSq; // -1
                }

                // check the right boundery
                if(col == N-sideSq)
                {
                    //col += sideSq;   // or break; because its the last part of the row
                    count += sideSq; // -1
                    break;
                }

                // fill the center square cell
                MSquare[row][col] = ++count;
                MSqNr[count] = false;
            }
            
            // to print step by step
            if(option == 'y' || option == 'Y')
            {
                printMSquare(N);
                Sleep(2000);
            }
        }
        
    }

    // filling the remaining area
    for(row = 0; row < N; row++)
    {
        for(col = 0; col < N; col++) // we removed the col++ increment to prevent duplication
        {
            // to fill the part around the sdie squares
            if(row < sideSq || row >= N-sideSq)
            {
                // to skip side squares left side up and down
                if(col == 0)
                {
                    col   += sideSq; 
                    count -= sideSq;
                }
                
                // to skip side squares right side up and down
                if(col == N-sideSq)
                {
                    count -= sideSq;
                    break;
                }
                MSquare[row][col] = count--;
                
            }
            // to fill the part around the center square area
            if(row >= sideSq && row < N-sideSq)
            {
                if(col < sideSq || col >= N-sideSq)
                    MSquare[row][col] = count--;
                else
                {
                    col   += centerSq-1;
                    count -= centerSq;
                }
            }

            // to print step by step
            if(option == 'y' || option == 'Y')
            {
                printMSquare(N);
                Sleep(2000);
            }
        }
    }

    
    
    // form Magic square after construction in a different way
    if(rdChoice > 0)
    {
        row = 0; col = 0;

        // interchange one colomn from left with one colomn from the right
        for(; row < N; row++)
        {
            // swapping the elements of the 2 colomns one by one
            tmp = MSquare[row][N-1]; // put the right colomn element in temporarily variable 
            MSquare[row][N-1] = MSquare[row][col]; // put the left cell value into the right cell
            MSquare[row][col] = tmp;    // put the temp vlaue of th right cell into the left cell

            if(option == 'y' || option == 'y')
            {
                printMSquare(N);
                Sleep(2000);
            }
        }

        row--; // to step back one step and stay in our Magic Square
        
        // interchange one row from top with one row from bottom 
        for(; col < N; col++)
        {
            // swapping the elements of the 2 rows one by one
            tmp = MSquare[row][col]; // put the bottom row element into temporarily variable
            MSquare[row][col] = MSquare[0][col]; // put the top row element into the bottom row element
            MSquare[0][col] = tmp; // put the temp value of the bottom row element into the top row element

            if(option == 'y' || option == 'Y')
            {
                printMSquare(N);
                Sleep(2000);
            }
        }   
    }

    // to print once at the end
    if(option == 'n' || option == 'N')
        printMSquare(N);
}


void singlyEvenMSquare(int N, char option)
{
    int smallSq = N/2;    // to split our big square into 4 parts vertically and horizontally
    int countA = 0;
    int countB = (smallSq * smallSq);
    int countC = (smallSq * smallSq)*2;
    int countD = (smallSq * smallSq)*3;

    int row = 0, col = 0;
    int tmpR = 0, tmpC = 0; 

    int rdChoice = 0;
    int tmp = 0;
    int MaxRd = (N/2); // indicate the nr of formations we can do in our constructed Magic Square

    // random generator
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(0, MaxRd);
    rdChoice = distr(eng);

    // fill the 4 parts
    while(true)
    {
        // set the up center Square A
        if(row == 0 && col == 0 && countA == 0)
        {
            col = smallSq / 2;
            MSquare[row][col] = ++countA;
        }

        // set the up center Square B
        if(row == smallSq && col == smallSq && countB == (smallSq*smallSq))
        {
            col = smallSq + (smallSq / 2);
            MSquare[row][col] = ++countB; 
        }

        // set the up center Square C
        if(row == 0 && col == smallSq && countC == (smallSq*smallSq)*2)
        {
            col = smallSq + (smallSq / 2);
            MSquare[row][col] = ++countC;
        }

        // set the up center Square D
        if(row == smallSq && col == 0 && countD == (smallSq*smallSq)*3)
        {
            col = smallSq / 2;
            MSquare[row][col] = ++countD;
        }

        // fill the 4 small squares

        // use it to backtrack and move down if up_right cell is full
        tmpR = row; tmpC = col;

        // Up A & C
        if(row == 0)
            row = smallSq-1;
        else
        {
            // Up B and D
            if(row == smallSq)
                row = N-1;
            else
                row += dir_r[UP];
        }
            

        // Right A & D
        if(col == smallSq-1)
            col = 0;
        else
        {
            // Right B & C
            if(col == N-1)
                col = smallSq;
            else
                col += dir_c[RIGHT];
        }
            
        
        if(MSquare[row][col] == 0)
        {
            // fill A square cell
            if(row < smallSq && col < smallSq)
                MSquare[row][col] = ++countA;
            else
            {
                // fill B square cell
                if(row >= smallSq && col >= smallSq)
                    MSquare[row][col] = ++countB;
                else
                {
                    // fill C square cell
                    if(row < smallSq && col >= smallSq)
                        MSquare[row][col] = ++countC;
                    else
                    {
                        // fill D square cell
                        if(row >= smallSq && col < smallSq)
                            MSquare[row][col] = ++countD;
                    }
                }
            }
        }    
        else
        {
            row = tmpR; col = tmpC;
            // Down A & C
            if(row == smallSq-1)
                row = 0;
            else
            {
                // Down B & D
                if(row == N-1)
                    row = smallSq;
                else
                    row += dir_r[DOWN];
            }
                
            // fill A square cell
            if(row < smallSq && col < smallSq)
                MSquare[row][col] = ++countA;
            else
            {
                // fill B square cell
                if(row >= smallSq && col >= smallSq)
                    MSquare[row][col] = ++countB;
                else
                {
                    // fill C square cell
                    if(row < smallSq && col >= smallSq)
                        MSquare[row][col] = ++countC;
                    else
                    {
                        // fill D square cell
                        if(row >= smallSq && col < smallSq)
                            MSquare[row][col] = ++countD;
                    }
                }
            }
        }

        if(option == 'y' || option == 'Y')
        {
            printMSquare(N);
            Sleep(2000);
        }

        // check the last move in each small square to switch to the next small square
        
        // switch from A to B
        if(countA == (smallSq * smallSq) )
        {
            row = smallSq; 
            col = smallSq;
            countA = 0;
        }else
        {
            // switch from B to C
            if(countB == (smallSq * smallSq * 2) )
            {
                row = 0;
                col = smallSq;
                countB = 0;
            }else
            {
                // switch from C to D
                if(countC == (smallSq * smallSq * 3) )
                {
                    row = smallSq;
                    col = 0;
                    countC = 0;
                }
                else
                {
                    if(countD == N*N)
                    {
                        countD = 0;
                        break;
                    }
                }
            }
        }
    }


    // the last part to get our Magic square
    int divFloor = N/4;
    int smallSqC = divFloor-1;
    int smallSqMidRow = smallSq/2;
    int rowDownAC = 0, colDownA = 0, colDownC = 0;
    int tmpVal = 0;

    // make mirror image reflection and swap the cell numbers
    for(int rowAC = 0; rowAC < smallSq; rowAC++)
    {
        
        rowDownAC = smallSq + rowAC; 
        
        for(int colA = 0, colC = N-1; colA < divFloor; colA++)
        {
            // assign the coordinates of the lower part of the Magic square
            colDownA = colA;

            if(rowAC != smallSqMidRow)
            {
                // swap the A small square highlighted colomns with D
                // take the lower part in a temp variable
                tmpVal = MSquare[rowDownAC][colDownA];
                MSquare[rowDownAC][colDownA] = MSquare[rowAC][colA];
                MSquare[rowAC][colA] = tmpVal;
            }
            else
            {
                // swap the A small square dent highlighted row with D
                colA++; colDownA++; 
                
                tmpVal = MSquare[rowDownAC][colDownA];
                MSquare[rowDownAC][colDownA] = MSquare[rowAC][colA];
                MSquare[rowAC][colA] = tmpVal;
                
                colA--; colDownA--;
            }

            // swap the C small square with B
            if(colC >= N-smallSqC)
            {
                colDownC = colC;
                tmpVal = MSquare[rowDownAC][colDownC];
                MSquare[rowDownAC][colDownC] = MSquare[rowAC][colC];
                MSquare[rowAC][colC] = tmpVal;
                
                colC--;
            }
            
            if(option == 'y' || option == 'Y')
            {
                printMSquare(N);
                Sleep(2000);    
            }
        }
    }

    
    // form Magic square after construction in a different way
    if(rdChoice > 0)
    {
        row = 0; col = 0;

        // interchange one colomn from left with one colomn from the right
        for(; row < N; row++)
        {
            // swapping the elements of the 2 colomns one by one
            tmp = MSquare[row][N-1]; // put the right colomn element in temporarily variable 
            MSquare[row][N-1] = MSquare[row][col]; // put the left cell value into the right cell
            MSquare[row][col] = tmp;    // put the temp vlaue of th right cell into the left cell

            if(option == 'y' || option == 'y')
            {
                printMSquare(N);
                Sleep(2000);
            }
        }

        row--; // to step back one step and stay in our Magic Square
        
        // interchange one row from top with one row from bottom 
        for(; col < N; col++)
        {
            // swapping the elements of the 2 rows one by one
            tmp = MSquare[row][col]; // put the bottom row element into temporarily variable
            MSquare[row][col] = MSquare[0][col]; // put the top row element into the bottom row element
            MSquare[0][col] = tmp; // put the temp value of the bottom row element into the top row element

            if(option == 'y' || option == 'Y')
            {
                printMSquare(N);
                Sleep(2000);
            }
        }   
    }

    if(option == 'n' || option == 'N')
        printMSquare(N);
}


// discarded code from our project:
/*

// from the above doubly even Magic Square functioin:
    // {
    //     if(col < sideSq)
    //         MSquare[row][col] = ++count;
        
    //     if(col >= N-sideSq)
    //         MSquare[row][col] = ++count;
    // }
    
    // // check to fill the center square
    // if(row >= sideSq && row < N-sideSq)



// not completed other try from my self turned out that it will take along time 
  
    void rotateMSq(int N)
    {
        int floorDiv = N/2;
        int rotateIter = (N*4)-4;
        int tmpCellNew = 0, tmpCellOld = 0;
        int row = 0, col = 0;
        int Order = N;

        for(int i = 0; i < floorDiv; i++)
        {
            row = i;
            col = i;
            for(int j = i; j < rotateIter; col++, j++)
            {
                // Right
                if(col < (Order-1))
                {
                    if(col != i)
                        MSquare[row][col] = tmpCellOld;
                    tmpCellNew = MSquare[row][col+1];
                    
                    col += dir_c[RIGHT];
                }
            }
            rotateIter -=8;
            Order -= 2;
        }
    }

// from OddMagicSquare() function

    //int MaxRd = (N/2)-1; // indicate the nr of formations we can do in our constructed Magic Square

*/