#include<iostream>
#include<random> //For Randomly Generating Value
#include<string> //For String Variables
#include<unistd.h> //For Sleep-Pause
using namespace std;

struct Card
{
    int number; 
    int suit;
    string numberName;
    string suitName;

    void syncNumberName() //To Sync the NumberName with the Integer-Number
    {
        switch(number)
        {
            case 2:
                numberName = "Two"; break;
            case 3:
                numberName = "Three"; break;
            case 4:
                numberName = "Four"; break;
            case 5:
                numberName = "Five"; break;
            case 6:
                numberName = "Six"; break;
            case 7:
                numberName = "Seven"; break;
            case 8:
                numberName = "Eight"; break;
            case 9:
                numberName = "Nine"; break;
            case 10:
                numberName = "Ten"; break;
            
            case 11:
                numberName = "Jack"; break;
            case 12:
                numberName = "Queen"; break;
            case 13:
                numberName = "King"; break;
            case 14:
                numberName = "Ace"; break;
            
            default:
                numberName = "No-Number";
        }
    };
    void syncSuitName() //To Sync the SuitName with the Integer-Suit
    {
        switch(suit)
            {
                case 1:
                    suitName = "Diamonds"; break;
                case 2:
                    suitName = "Hearts"; break;
                case 3:
                    suitName = "Spades"; break;
                case 4:
                    suitName = "Clubs"; break;
                default:
                    suitName = "No-Suit";
            }
    };
};

void GenerateCards();
void chooseCard(Card&); //For Choosing the Card
void Swap(Card, Card); //For simply Swapping the Cards
void evaluate();
void PlayAgain(); //The PlayAgain Option

Card card[3]; //The Cards
Card bet, guess; //The User Bet-Card & the chosen Guess-Card
int c; //For Loop-control Cards

int max_cIgnore = 255; //MaxCharacters to be Ignored in the Buffer
char playAgain = 'Y'; //The Default PlayAgain Option

random_device Seed; //RandomValue Generator
uniform_int_distribution<int> rand_card(0, 2); //For Randomly Generating the Card
uniform_int_distribution<int> rand_number(2, 14); //For Randomly Generating the CardNumber
uniform_int_distribution<int> rand_suit(1, 4); //For Randomly Generating the CardSuit

int main()
{ 
    cout << endl
		<< "Welcome to the Sinlge-Player Card Guessing Game. \n"
		<< "You are Advised to Consult the Readme File, before Playing the Game. \n"
		<< endl;

    do {
        cout << "Lets Begin! \n\n";
        
        GenerateCards();

        cout << "In Which Card to Put the Bet: ";
        chooseCard(bet);
        
        cout << "let me Swap the Cards! \n";
        for(c=0; c<3*2; c++)
            Swap(card[rand_card(Seed)], card[rand_card(Seed)]);
        sleep(1);
        
        cout << "Ok Now Guess where The " << bet.numberName << " of " << bet.suitName << " (Your Bet-Card) is: ";
        chooseCard(guess);

        evaluate();

        PlayAgain();
    }
    while(playAgain == 'Y');

    cout << endl << endl;
    return 0;
}

void GenerateCards()
{
    cout << "Here are the Cards: \n";
    for(c=0; c<3; c++) {
        card[c].number = rand_number(Seed); 
        card[c].suit = rand_suit(Seed);
        
        card[c].syncNumberName();
        card[c].syncSuitName();
        
        cout << "  Card " << c+1 << ": The " << card[c].numberName << " of " << card[c].suitName << ". " << endl;
    }
    cout << endl;
}

void chooseCard(Card &n)
{
    int choose;
    cin >> choose;
    cin.ignore(max_cIgnore,'\n');
			
    if (cin.fail()) {
        cin.clear(); cin.ignore(max_cIgnore,'\n');
        cout << "   Oops! Its not the legal Card Number. \n\n";
        cout << "Choose the Card Again: ";
        chooseCard(n);
    }
    else if(!(choose>=1 && choose<=3)) {
        cout << "   Oops! There's no such Card. \n";
        cout << "Choose the Card Again: ";
        chooseCard(n);
    }
    
    for(c=0; c<3; c++)
        if(choose == c+1)
            n = card[c];
    
    cout << endl; //It would be Buffered each Time the Function Self-Calls
}

void Swap(Card a, Card b)
{
    Card temp = a;
    a = b;
    b = temp;
}

void evaluate()
{
    if(guess.number == bet.number && guess.suit == bet.suit)
        cout << "Great! You Won! \n\n";
    else {
        cout << "Ahh! You Lose! \n";
        for(c=0; c<3; c++)
            if(bet.number == card[c].number && bet.suit == card[c].suit)
                cout << "It was on Card no." << c+1 << ". \n\n";
    }
}

void PlayAgain()
{
	cout << "Do You Want to Play Again (Y/N): ";
	cin >> playAgain;
	playAgain = toupper(playAgain);
	cin.ignore(max_cIgnore, '\n');

	if(playAgain == 'Y') {
		cout << endl << endl;
        return;
	}
	else if(playAgain == 'N') {
		cout << endl << endl;
		cout << "Thanks for Playing. Hope You Enjoyed the Game! \n";
		cout << "It would be very Kind of you, if you give us an Honest Feedback. \n\n";

		cout << "You can Find me in GitHub https://github.com/Haseebullah9012. \n";
	}
	else {
		cout << "   Oops! Its not a legal Response. \n\n";
		cout << "Again, ";
		PlayAgain();
	}
}
