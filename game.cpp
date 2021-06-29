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

void configuration();
void Cards(); //To choose the Total Number of Cards
void SwapProcess(); //To choose to Enable/Disable the Swap Process Option

void GenerateCards();
void chooseCard(Card&); //For Choosing the Card
void Swap(Card, Card); //For simply Swapping the Cards
void evaluate();
void PlayAgain(); //The PlayAgain Option

int cards = 3; //The Total Default Number of Cards
Card card[26]; //The Cards
Card bet, guess; //The User Bet-Card & the chosen Guess-Card
int c; //For Loop-control Cards

char configure = 'N'; //The Default Configuration Options 
char swapProcess = 'N'; //The Default Guessing Option
int swap_times = 9; //The Default Times the Cards would be Swapped
int guesses; //The Times the User had Guesses
int max_cIgnore = 255; //MaxCharacters to be Ignored in the Buffer
char playAgain = 'Y'; //The Default PlayAgain Option

random_device Seed; //RandomValue Generator

int main()
{ 
    cout << endl
		<< "Welcome to the Sinlge-Player Card Guessing Game. \n"
		<< "You are Advised to Consult the Readme File, before Playing the Game. \n"
        << endl << endl;
	
    int a,b;	
    configuration();
	    
    do {
        cout << "Lets Begin! \n\n";
        
        GenerateCards();

        cout << "In Which Card to Put the Bet: ";
        chooseCard(bet);
        
        cout << "let me Swap the Cards! \n";
        uniform_int_distribution<int> rand_card(0, cards-1); //For Randomly Generating the Card
        for(c=0; c<swap_times; c++) {
            a = rand_card(Seed), b = rand_card(Seed);
            Swap(card[a], card[b]);
            
            if(swapProcess == 'Y')
                cout << "  Swapped the Card " << a+1 << " with Card " << b+1 << ". \n";
        }
        if(!(swapProcess == 'Y'))
            sleep(1);
        cout << endl;
        

        cout << "Ok Now Guess where The " << bet.numberName << " of " << bet.suitName << " (Your Bet-Card) is: ";
        while(true) {
            chooseCard(guess);
            evaluate();
        }

        PlayAgain();
    }
    while(playAgain == 'Y');

    cout << endl << endl;
    return 0;
}

void configuration()
{
    do {	
		if(configure == 'Y') {
			Cards();
            SwapProcess();
		}
		
		cout << "The Total of " << cards << " Cards would be Picked randomly from the Deck. \n";

        if(swapProcess == 'Y')
		    cout << "You would be Shown the Swapping Process of the Cards. \n";
        else
            cout << "You will Guess Your Card Blindly, without Seeing the Swapping Process. \n";
		
        cout << "The Cards would be Swapped " << swap_times << " Times. \n";
        cout << "And You have " << (cards/3) << " Chance to Guess Correctly. \n";
        cout << "   Do you want to Configure it (Y/N): ";
		
		cin >> configure;
		configure = toupper(configure);
		cin.ignore(max_cIgnore, '\n');
		
		cout << endl << endl;
	}
	while(configure == 'Y');
}

void Cards()
{
    cout << "Enter the Custom Total Number of Cards to be Picked: ";
    cin >> cards;
    cin.ignore(max_cIgnore,'\n');
    
    if (cin.fail()) {
        cin.clear(); cin.ignore(max_cIgnore,'\n');
        cout << "   Oops! Its not the legal Number of Cards. \n\n";
        cout << "Again, ";
        Cards();
    }
    else if (!(cards>=2)) {
        cout << "   Oops! You Choose to Pick very Few Cards to Play. \n\n";
        cout << "Again, ";
        Cards();
    }
    else if (!(cards<26)) {
        cout << "   Oops! You Choose to Pick a large Amount of Cards to Play. \n\n";
        cout << "Again, ";
        Cards();
    }
    cout << endl; //It would be Buffered each Time the Function Self-Calls
}

void SwapProcess()
{
    cout << "Do You Want to See the Swapping Process (Y/N): ";
    cin >> swapProcess;
    swapProcess = toupper(swapProcess);
    cin.ignore(max_cIgnore,'\n');
    
    if(swapProcess == 'Y') {
        cout << "Enter How Many Times To Swap: ";
        cin >> swap_times;
        cin.ignore(max_cIgnore,'\n');
    
        if (cin.fail()) {
            cin.clear(); cin.ignore(max_cIgnore,'\n');
            cout << "   Oops! Its not the a Number. \n\n";
            cout << "Again, ";
            SwapProcess();
        }
        else if (!(swap_times>=3)) {
            cout << "   Oops! You Choose to Swap very few Times. \n\n";
            cout << "Again, ";
            SwapProcess();
        }
        else if (!(swap_times<52)) {
            cout << "   Oops! You Choose to to Swap very much More Times. \n\n";
            cout << "Again, ";
            SwapProcess();
        }
    }
    else {
        cout << "This option is Set to Deafult. \n";
        swapProcess = 'N';
        swap_times = cards * 3;
    }
    cout << endl; //It would be Buffered each Time the Function Self-Calls
}

void GenerateCards()
{
    cout << "Here are the Cards: \n";
    uniform_int_distribution<int> rand_number(2, 14); //For Randomly Generating the CardNumber
    uniform_int_distribution<int> rand_suit(1, 4); //For Randomly Generating the CardSuit

    for(c=0; c<cards; c++) {
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
    else if(!(choose>=1 && choose<=cards)) {
        cout << "   Oops! There's no such Card. \n";
        cout << "Choose the Card Again: ";
        chooseCard(n);
    }
    
    for(c=0; c<cards; c++)
        if(choose == c+1)
            n = card[c];
}

void Swap(Card a, Card b)
{
    Card temp = a;
    a = b;
    b = temp;
}

void evaluate()
{
    if(guess.number == bet.number && guess.suit == bet.suit) {
        cout << "\n\nGreat! You Won! \n";
    }
    else if(guesses<(cards/3)) {
        cout << "Nah! Guess Again: ";
        guesses++;
        return;
    }
    else {
        cout << "\n\nAhh! You Ran Out of Guessses. You Lose! \n";
        for(c=0; c<cards; c++)
            if(bet.number == card[c].number && bet.suit == card[c].suit)
                cout << "It was on Card no." << c+1 << ". \n";
    }
    cout << endl;
}

void PlayAgain()
{
	cout << "Do You Want to Play Again (Y/N): ";
	cin >> playAgain;
	playAgain = toupper(playAgain);
	cin.ignore(max_cIgnore, '\n');

	if(playAgain == 'Y') {
		cout << "Do You Want to Configure the Options (Y/N): ";	
		cin >> configure;
		configure = toupper(configure);
		cin.ignore(max_cIgnore, '\n');
		
		cout << endl << endl;
		if(configure == 'Y')
			configuration();
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
