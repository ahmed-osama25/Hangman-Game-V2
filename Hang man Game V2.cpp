#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<cctype>

using namespace std;

string words[1500];
int wordcount = 0;

// Hangman Art

void displayHangmangame(int attempts)
{
    int stage = 7 - attempts; // 0 - 7 stages

    cout << "\n";
    cout << "   ___\n";
    cout << "  |   |\n";
    
    if(stage >= 1)
    {
        cout << "  |   O\n"; 
    }

    else
    {
        cout << "  |\n";
    }
    
    if(stage == 2) 
    {
        cout << "  |   |\n"; 

    }

    else if(stage >= 3) 
    {
        cout << "  |  /|\\\n"; 
    }

    else if(stage >= 2)
    {
        cout << "  |   |\n"; 
    }
    else
    {
        cout << "  |\n";
    }
    
    if(stage >= 4) 
    {
        cout << "  |  / \\\n"; 
    }

    else
    {
        cout << "  |\n";
    }
    
    cout << "  |\n";
    cout << "__|__\n";
    cout << "\n";
}

// load words

void loadwords()
{
    ifstream file("words.txt");

    if(!file)
    {
        cout << "Error opening words.txt" << endl;
        return;
    }

    while(wordcount < 1500 && file >> words[wordcount])
    {
        wordcount++;
    }

    file.close();
}

// Choose Random Word

string choosWord()
{
    int randomIndex = rand() % wordcount;
    return words[randomIndex];
}

// Create hidden word

string createHiddenword(string word)
{
    string hiddenword;

    for(int i = 0; i < word.length(); i++)
    {
        hiddenword.append("_");
    }

    return hiddenword;
}

// Check if letter Exists

bool checkword(string word, char guess)
{
    for(int i = 0; i < word.length(); i++)
    {
        if(word[i] == guess)
        {
            return true;
        }
    }

    return false;
}

// Update hidden word

void updatehiddenword(string word, string &hiddenword, char guess)
{
    for(int i = 0; i < word.length(); i++)
    {
        if(word[i] == guess)
        {
            hiddenword[i] = guess;
        }
    }
}

// Update Attempts

void updateAttempts(int &attempts, bool found)
{
    if(!found)
    {
        attempts--;
    }
}

// Check Win

bool checkwin(string word, string hiddenword)
{
    return word == hiddenword;
}

// Display Menu

void displayMenu()
{
    cout << "\n=============================================================\n";
    cout << "\n                 Welcome TO Hangman Game                     \n";
    cout << "\n                     Made By: Ahmad Osama                    \n";
    cout << "\n=============================================================\n";
}

// Play Game

void playGame()
{
    system("cls");

    if(wordcount == 0 )
    {
        cout << "No words avilable! " << endl;

        return;
    }

    cout << "\n==================================================\n";
    cout << "                 Hangman Game Started               \n";
    cout << "\n==================================================\n";

    string selectword = choosWord();

    // Convert To lowerCase 

    for(int i = 0 ; i < selectword.length(); i ++)
    {
        selectword[i] = tolower(selectword[i]);
    }

    string hiddenword = createHiddenword(selectword);

    string usedletters = "";

    int attempts = 7;

    while(attempts > 0)
    {
        displayHangmangame(attempts);

        // Display Current word
        
        cout << "Current Word: ";

        for(int i = 0; i < hiddenword.length(); i++)
        {
            cout << hiddenword[i] << " ";
        }

        cout << "\n\n";

        // Display used letters
        
        cout << "Used Letters: ";
        if(usedletters.empty())
        {
            cout << "None";
        }

        else
        {
            cout << usedletters;
        }
        
        cout << "\n\n";

        // Display Attempts

        cout << "Attempts Left: " << attempts << "\n";

        cout << "=====================================\n\n";

        // Get User input

        char guess;
        cout << "Enter a letter: ";
        cin >> guess;
        cout << "\n";

        // Validate input

        if(!isalpha(guess))
        {
            cout << "Please enter a letter\n";
            continue;
        }

        guess = tolower(guess);

        // Check if already used

        bool alreadyUsed = false;

        for(int i = 0; i < usedletters.length(); i++)
        {
            if(usedletters[i] == guess)
            {
                alreadyUsed = true;
                break;
            }
        }

        if(alreadyUsed)
        {
        cout << "You Already guessed '" << guess << "'!\n";
        cout << "Please Enter to continue....";
        cin.ignore();
        cin.get();
        system("cls");
        continue;
        }

        // Check if letter is in word

        bool found = checkword(selectword , guess);

        if(found)
        {
        cout << "Good Guess!\n\n";
        }

        else
        {
        cout << "Wrong guess!\n\n";
        }   

        // Update hidden word

        updatehiddenword(selectword, hiddenword, guess);
    
        // Add to used letters

        usedletters += guess;
        usedletters += ", ";

        // Update Attempts

        updateAttempts(attempts, found);

        // Check Win 

        if(checkwin(selectword, hiddenword))
        {
        system("cls");
        displayHangmangame(attempts);

        cout << "Current Word: ";
        
        for(int i = 0 ; i < hiddenword.length(); i++)
        {
            cout << hiddenword[i] << " ";
        }

        cout << "\n\n";

        cout << "\n=================================================================\n";
        cout << "                            Congratulations                        \n";
        cout << "                        Word: " << selectword <<                   "\n";
        cout << "                   Attempts Left: " << attempts <<                 "\n";
        cout << "\n=================================================================\n";

        break;

        system("cls");

        }

        // Game Over - lost

        if(attempts == 0 )
        {
            system("cls");
            displayHangmangame(attempts);

            cout << "\n===========================================\n";
            cout << "                  GAME OVER!                 \n";
            cout << "           The word was: " << selectword << "\n";
            cout << "        Better Luck next time!               \n";
            cout << "\n===========================================\n";

        }
    }
    
    
}

// Main Function

int main()
{
    srand(time(0));

    loadwords();

    displayMenu();

    char playAgain;

    do 
    {
        playGame();

        cout << "======================================================\n";
        cout << "Do you want to play again ? (Y/N):";
        cin >> playAgain;

    }while(playAgain == 'y' || playAgain == 'Y');

    cout << "\n =============================================================\n";
    cout << "               Thanks For Playing!   Goodbye!                   \n";
    cout << "\n =============================================================\n";

    system("pause");

    return 0;
}