#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Makes syntax UnrealEngine Friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
int32 GetValidLength();
bool AskToPlayAgain();
void PrintGameSummary();


FBullCowGame BCGame;

int main() {

	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
	return 0;
}

void PlayGame() {
	BCGame.Reset();
	// Choose word length
	int32 WordLength = GetValidLength();
	std::cout << "Word length: " << WordLength << std::endl;
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <=MaxTries) {
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "You win!";
	} else {
		std::cout << "You lose, better luck next time.";
	}
	std::cout << std::endl;
}

void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter of the isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

int32 GetValidLength() {
	FWordLengthResult Result;
	FText WordLength = "";
	int32 Min = BCGame.GetMinLength();
	int32 Max = BCGame.GetMaxLength();

	do {
		std::cout << "Choose a word length?";
		std::cout << " [" << Min << "-" << Max << "] ";

		std::getline(std::cin, WordLength);
		Result = BCGame.CheckWordLength(WordLength);
		switch (Result.Status) {
		case EWordLengthStatus::Invalid_Status:
			std::cout << "Please enter a number.\n\n";
			break;
		case EWordLengthStatus::Outside_Range:
			std::cout << "Please enter a number between ";
			std::cout << Min << " and " << Max << "\n\n";
			break;
		default:
			break;
		}
	} while (Result.Status != EWordLengthStatus::OK);
	
	return Result.ValidLength;
}

FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an Isogram.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);

	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again? [y/n] ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}
