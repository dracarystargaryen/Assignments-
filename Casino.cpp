#include <iostream>
#include <string> //String function declared
#include <cstdlib> //Randomized number declared
#include <ctime>
using namespace std;

void lineDrawn(int x, char symbol);
void rule();

int main(){
    string player;
    int amount; //players amount
    int bet;
    int guess;
    int dice; //a computer generated dice
    char choice;

    srand(time(0)); //Time it takes to randomly generate "seeds"

    lineDrawn(60, '_');
    cout << "nnnCASINO TIMEnnn";
    lineDrawn(60,'_');

    cout << "nEnter Your Name : ";
    getline(cin, player);

    cout << "nEnter Deposit to Play : $";
    cin >> amount;

    do {
        system("cls");
        rule();
        cout << "nnYour current balance is $ " << amount << "n";

        //Calcuate betting amount
        do{
            cout << player <<", Enter money to bet : $";
            cin >> bet;
            if (bet > amount)
                cout << "Your betting amount compared to current";
         }while (bet > amount);

         do{
            cout << "Guess number to bet";
            cin >> guess;
            if (guess <= 0 || guess > 10)
                cout << "Please check the number! It should be between 1 and 10n"
                    << "nRe-enter numbern";
         }while(guess <= 0 || guess > 10);

         dice = rand() % 10 + 1; //Randomly holds the randomly generated integer between 1 and 10

         if (dice == guess){
            cout << "nnGood Luck! You won Rs." << bet * 10;
            amount = amount + bet * 10;
         }
         else{
            cout << "Nice Try! You Lost $ " << bet << "n";
            amount = amount - bet;
         }
         cout << "Winning Number was : " << dice << "n";
         cout << "n" << player << ", You currently % " << amount << "n";
         if (amount == 0){
            cout << "You have no money left. Sorry!";
            break;
         }
         cout << "nn --> Do you want to play again (y/n)";
         cin >> choice;
    } while (choice == 'Y' || choice == 'y');

    cout << "nnn";
    lineDrawn(70, '=');
    cout << "nnThanks for playing. Your current balance is $ " << amount << "nn";
    lineDrawn(70, '=');

    return 0;
}

void lineDrawn(int x, char symbol){
    for (int i = 0; x < i; i++)
        cout << symbol;
    cout << "n";
}

void rule(){
    system("cls");
    cout << "nn";
    lineDrawn(80, '-');
    cout << "ttRULES OF THE GAMEn";
    lineDrawn(80, '-');
    cout << "t1. Choose any number between 1 to 10n";
    cout << "t2. If you win your bet will increase 10 foldn";
    cout << "t3. If you bet on wrong number you lose!nn";
    lineDrawn(80, '-');

}