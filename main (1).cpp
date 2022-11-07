/* Benyamain Yacoob
03-17-2022
Intro to Programming II
Dr. Mina Maleki
"Project #2" Exercise */

#include <iostream>
#include <cstring>
#include <limits>
#include <cctype>

using namespace std;

// Global variables
const int MAX_LINE_LENGTH = 10;
const int MAX_WORD_LENGTH = 20;
const int MAX_CHAR_LENGTH_LINE = 80;

// readText: Reads text lines from the user input that is stored into 2D "text" array
// INPUT: Asks of user to type ('n') lines
// Function called to store input text into a 2D array
// OUTPUT: Returns total number of lines
int readText(char text[MAX_LINE_LENGTH][MAX_CHAR_LENGTH_LINE])
{
    int n = 0;
    
    while (true) 
	{
		cout << "Please enter desired number of text lines (10 or less): ";
        cin >> n;
        
        if (!cin || n > MAX_LINE_LENGTH || n <= 0)
        {
   		    cin.clear();
		    cin.ignore(numeric_limits <streamsize> ::max(), '\n');  // Ignore limitless char until EOF
            cout << "Invalid input.\n\n";
            
            continue;
        }
        else
            break;
	}
	
    cout << "\nType " << n << " sentence(s):" << endl;
    cin.ignore();
    
    for (int i = 0; i < n; i++)
    {
        cin.getline(text[i], 130); // Storing input into array
        
        if (strlen(text[i]) > MAX_CHAR_LENGTH_LINE)
        {
            cout << "Your input on a line is too high. Please try again!\n";
            
            i--;    // Goes back to where user should be left off
        }
    }
    
    cout << "\nThese is what you put in: " << endl << endl;

    for (int i = 0; i < n; i++)    // Displaying what user wrote
    {
        cout << text[i] << endl;
    }
    
    cout << "---------------------";
    
    return n;
}

// extractWords: Reads from text lines to extract words and store into 2D "words" array
// INPUT: N/A
// Function called to store input text into a 2D array
// OUTPUT: Returns total number of words
int extractWords(char text[MAX_LINE_LENGTH][MAX_CHAR_LENGTH_LINE], char words[][MAX_WORD_LENGTH], int n)
{
  // Declaration of variables
  char textCopy[MAX_LINE_LENGTH][MAX_CHAR_LENGTH_LINE], delimList[] = " ,.;!\t";
  int wordCount = 0, j = 0;
  char *tokenPtr;
 
  for (int i = 0; i < MAX_LINE_LENGTH; i++)
  {
      for (int  j = 0; j < MAX_CHAR_LENGTH_LINE; j++)
      {
          textCopy[i][j] = text[i][j];  // Copying text array to be used for strtok
      }
  }

  // Find number of words in the user input
  for (int i = 0; i < n; i++)
  {
      tokenPtr = strtok(textCopy[i], delimList);	// Assign the number of tokens to tokenPtr
      
      while (tokenPtr != NULL)
      {
	    wordCount++;
	    
	    tokenPtr = strtok(NULL, delimList);
	  }
  }
   
  for (int i = 0; i < n; i++)
  {
        tokenPtr = strtok(text[i], delimList);
        
        while (tokenPtr != NULL)
        {
    	    strcpy(words[j], tokenPtr);
    	    
    	    tokenPtr = strtok(NULL, delimList);
    	    j++;
	    }
  }

  return wordCount;
}

// validateInput: Asks program user to confirm the menu option they chose
// INPUT: A character ( inputConfirmation ) that is 'Y' or 'N'
// Function called when menu option chosen needs to be confirmed from the user
// OUTPUT: N/A
char validateInput(int userChoice, char inputConfirmation)
{
    inputConfirmation = toupper(inputConfirmation); // Uppercases the letter

    while (true)
    {
        if (inputConfirmation == 'Y')
            break;
        else if (inputConfirmation == 'N')
            break;
        else if (inputConfirmation != 'Y' && inputConfirmation != 'N')
        {
            cout << "ERROR: Invalid input.\n";
            cout << "Please type (Y/N): ";
            cin >> inputConfirmation;

            inputConfirmation = toupper(inputConfirmation);
        }
    }
    
    return inputConfirmation;
}

// userMenuOptions: Function that allows user to interact with menu interface to select some option
// INPUT: N/A
// Function called in the main
// OUTPUT: Shows the menu for user to choose from
int userMenuOptions()
 {
    int userChoice;
    char inputConfirmation;    // Echoing the input when appropriate
    
    do
    {
        // Displays the menu options
        cout << "\n\nText Analysis\n";
        cout << "---------------------\n";
        cout << "1-Search By Character\n2-Search By Word\n3-Search By Length" << endl;
        cout << "4-Search Uppercase Letters\n5-Search Digits\n0-Quit" << endl;
        cout << "Please enter a selection: ";
        cin >> userChoice;
        cout << "Did you mean to press " << userChoice << " (Y/N)?: ";
        cin >> inputConfirmation;
        
        inputConfirmation = validateInput(userChoice, inputConfirmation);   // Calling function
        
    } while (inputConfirmation != 'Y');

    return userChoice;
}

// searchByLength: Tells user how many words have the input specified string length
// INPUT: User enters ('3') on menu interface
// Function called in the main to search "words" of that user-specified length
// OUTPUT: Returns the number of occurrences of words with that length appearing in the text
int searchByLength(char words[][MAX_WORD_LENGTH], int wordCount)
{
    int wordLen = 0, inputWordLen;

    cout << "Enter string search length: ";
    cin >> inputWordLen;
    
    for (int i = 0; i < wordCount; i++)
    {
        if (strlen(words[i]) == inputWordLen)   // Using strlen in order to find requested length
            wordLen++;
    }
    
    cout << "Number of words with " << inputWordLen << " characters = " << wordLen;
    
    return wordLen;
}

// searchByCharacter: Tells user how many words have the input specified character
// INPUT: User enters ('1') on menu interface
// Function called in the main to search "text" with that character
// OUTPUT: Returns the number of occurrences of that specified character
int searchByCharacter(char text[][MAX_CHAR_LENGTH_LINE], int n)
{
    char inputChChoice;
    int ch = 0;
    
    while (true) 
	{
		cout << "Enter a character to search: ";
        cin >> inputChChoice;
        
        if (!isalpha(inputChChoice))    // Only accepts character input
        {
            cout << "Invalid input! Please try again.\n\n";
            
            continue;
        }
        else
            break;
	}
	
 	for (int i = 0; i < n; i++)
    {
        for (int  j = 0; j < MAX_CHAR_LENGTH_LINE; j++)
        {
            if (tolower(inputChChoice) == tolower(text[i][j]))    // Finding input letter in array
                ch++;
        }
    }
    
    cout << "Number of occurrences with character " << inputChChoice << " = " << ch;
    
    return ch;
}

// searchByWord: Tells user number of occurrences found for their input specified keyword
// INPUT: User enters ('2') on menu interface
// Function called in the main to search "words" with that keyword
// OUTPUT: Returns the number of occurrences of that specified keyword
int searchByWord(char words[][MAX_WORD_LENGTH], int wordCount)
{
    char keywordInput[MAX_WORD_LENGTH];
    int keyword = 0;
    
    cout << "Enter a keyword to search (20 or less characters): ";
    cin >> keywordInput;
    
    // Making the words array lowercase for it to match lowercase keyword input from user
    for (int i = 0; i < wordCount; i++)
    {
        for (int j = 0; j < strlen(words[i]); j++)
            words[i][j] = tolower(words[i][j]);
    }
    
    cout << "Number of occurrences of " << keywordInput << " = ";
    
    // Make the input lowercase
    for (int i = 0; i < strlen(keywordInput); i++)
        keywordInput[i] = tolower(keywordInput[i]);
    
    for (int i = 0; i < wordCount; i++)
    {
        if (!strcmp(words[i], keywordInput))    // Correct way to test for equality
            keyword++;
    }
    
    cout << keyword;
    
    return keyword;
}

// searchUppercaseLetters: Number of occurrences found for uppercase letters
// INPUT: User enters ('4') on menu interface
// Function called in the main to search "text" for uppercase letters
// OUTPUT: Returns the number of occurrences of uppercase letters
int searchUppercaseLetters(char text[][MAX_CHAR_LENGTH_LINE], int n)
{
    int uppercaseIncrement = 0;
    
    for (int i = 0; i < n; i++)
    {
        for (int  j = 0; j < MAX_CHAR_LENGTH_LINE; j++)
        {
            if (isupper(text[i][j]))    // Finding uppercase letters in array
                uppercaseIncrement++;
        }
    }
	
    cout << "Number of uppercase letters = " << uppercaseIncrement;
    
    return uppercaseIncrement;
}

// searchDigits: Number of occurrences found for digits
// INPUT: User enters ('5') on menu interface
// Function called in the main to search "text" for digits
// OUTPUT: Returns the number of occurrences of digits
int searchDigits(char text[][MAX_CHAR_LENGTH_LINE], int n)
{
    int digitsIncrement = 0;
    
    for (int i = 0; i < n; i++)
    {
        for (int  j = 0; j < MAX_CHAR_LENGTH_LINE; j++)
        {
            if (isdigit(text[i][j]))
                digitsIncrement++;
        }
    }
	
    cout << "Number of digits found = " << digitsIncrement;
    
    return digitsIncrement;
}

int main()
{
    // Declaration of variables
    char text[MAX_LINE_LENGTH][MAX_CHAR_LENGTH_LINE], words[400][MAX_WORD_LENGTH];
    int mainN = 0, mainWordCount = 0;
    
    mainN = readText(text);  // Calling the function
    
    mainWordCount = extractWords(text, words, mainN);   // Calling function to tokenize the words
    
    // Exits the menu interface by pressing 0
    bool codeRuns = true;    // Terminates program if false

    do
    {
        // Function is called after text input to show menu interface
        int userChoice = userMenuOptions();
        
        switch (userChoice)
        {
            case 1: searchByCharacter(text, mainN);
            break;
            case 2: searchByWord(words, mainWordCount);
            break;

            case 3: searchByLength(words, mainWordCount);
            break;

            case 4: searchUppercaseLetters(text, mainN);
            break;

            case 5: searchDigits(text, mainN);
            break;

            case 0: codeRuns = false;
            cout << "---------------------"; 
            cout << "\nThanks for playing!\n";
            break;

            default:    cout << "Invalid input!\n";
            break;
         }
     } while (codeRuns);
    
    return 0;
}
