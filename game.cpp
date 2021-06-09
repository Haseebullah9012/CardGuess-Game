#include<iostream>
#include<random> //For Randomly Generating Value
#include<string> //For String Variables
#include<unistd.h> //For Sleep Pause
using namespace std;

struct Card {
    int number; 
    string numberName;
    int suit;
    string suitName;
};

void Swap(Card *a, Card *b); //For simply Swapping the Cards
void PlayAgain(); //The PlayAgain Option
char playAgain = 'Y'; //The Default PlayAgain Option

int main()
{
    Card card[3]; //The Cards
    int c; //For Loop-control Cards

    Card bet, guess; //The User Bet-Card & the chosen Guess-Card
    int choose; //For User-Input to choose Bet-Card & Guess-Card
    
    random_device Seed; //RandomValue Generator
    uniform_int_distribution<int> rand_card(0, 2); //For Randomly Choosing the Card
    uniform_int_distribution<int> rand_number(2, 14); //For Randomly Choosing the CardNumber
    uniform_int_distribution<int> rand_suit(1, 4); //For Randomly Choosing the CardSuit

    cout << endl;
    
    do {
        cout << "Lets Begin! \n\n";

        //Randomly Choose and Display Three Cards
        cout << "Here are the Cards: \n";
        for(c=0; c<3; c++) {
            card[c].number = rand_number(Seed); 
            card[c].suit = rand_suit(Seed);
            
            switch(card[c].number)
            {
                case 2:
                    card[c].numberName = "Two"; break;
                case 3:
                    card[c].numberName = "Three"; break;
                case 4:
                    card[c].numberName = "Four"; break;
                case 5:
                    card[c].numberName = "Five"; break;
                case 6:
                    card[c].numberName = "Six"; break;
                case 7:
                    card[c].numberName = "Seven"; break;
                case 8:
                    card[c].numberName = "Eight"; break;
                case 9:
                    card[c].numberName = "Nine"; break;
                case 10:
                    card[c].numberName = "Ten"; break;
                
                case 11:
                    card[c].numberName = "Jack"; break;
                case 12:
                    card[c].numberName = "Queen"; break;
                case 13:
                    card[c].numberName = "King"; break;
                case 14:
                    card[c].numberName = "Ace"; break;
                
                default:
                    card[c].numberName = "No-Number";
            }
            
            switch(card[c].suit)
            {
                case 1:
                    card[c].suitName = "Diamonds"; break;
                case 2:
                    card[c].suitName = "Hearts"; break;
                case 3:
                    card[c].suitName = "Spades"; break;
                case 4:
                    card[c].suitName = "Clubs"; break;
                default:
                    card[c].suitName = "No-Suit";
            }

            cout << "  Card " << c+1 << ": The " << card[c].numberName << " of " << card[c].suitName << ". " << endl;
        }
        cout << endl;
        
        //Choose the Bet-Card
        cout << "In Which Card to Put the Bet: ";
        cin >> choose;
        for(c=0; c<3; c++)
            if(choose == c+1)
                bet = card[c];
        cout << endl << endl;
        
        
        //Swap the Cards Randomly
        //cout << "Wait Until the Cards are being Swapped! " << endl;
        cout << "let me Swap the Cards! \n";
        for(c=0; c<3*2; c++)
            Swap(&card[rand_card(Seed)], &card[rand_card(Seed)]);
        sleep(1);
        

        //Guess the Choosen Bet-Card
        cout << "Ok Now Guess where The " << bet.numberName << " of " << bet.suitName << " (Your Bet-Card) is: ";
        cin >> choose;
        for(c=0; c<3; c++)
            if(choose == c+1)
                guess = card[c];
        cout << endl;


        //Compare the Guess-Card & Bet-Card
        if(guess.number == bet.number && guess.suit == bet.suit)
            cout << "Great! You Won! \n\n";
        else {
            cout << "Ahh! You Lose! \n";
            for(c=0; c<3; c++)
                if(bet.number == card[c].number && bet.suit == card[c].suit)
                    cout << "It was on Card no." << c+1 << ". \n\n";
        }

        PlayAgain();
    }
    while(playAgain == 'Y');


    cout << endl << endl;
    return 0;
}

void Swap(Card *a, Card *b)
{
    Card temp = *a;
    *a = *b;
    *b = temp;
}

void PlayAgain()
{
	cout << "Do You Want to Play Again (Y/N): ";
	cin >> playAgain;
	playAgain = toupper(playAgain);
	
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
