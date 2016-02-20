#pragma once
#include "FBullCowGame.h"
#include <map>

// UnrealEngine friendly syntax
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() {
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const {	return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
int32 FBullCowGame::GetMinLength() const { return minLength; }
int32 FBullCowGame::GetMaxLength() const { return maxLength; }

int32 FBullCowGame::GetMaxTries() const {
	int32 MaxTries = 3;
	if (GetHiddenWordLength() <= 2) {
		MaxTries = 3;
	} else if (GetHiddenWordLength() > 6) {
		MaxTries =  20;
	} else {
		TMap<int32, int32> WordLengthtoMaxTries{ { 3,4 },{ 4,7 },{ 5,10 },{ 6,16 } };
		MaxTries = WordLengthtoMaxTries[GetHiddenWordLength()];
	}
	return MaxTries;
}

void FBullCowGame::Reset() {
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	minLength = 2;
	maxLength = 8;
	return;
}


#include <iostream>
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	} else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	} else {
		return EGuessStatus::OK;
	}
}

FWordLengthResult FBullCowGame::CheckWordLength(FString WordLength) const {
	FWordLengthResult Result;
	int32 ValidLength;
	try {
		ValidLength = std::stoi(WordLength);
	} catch (const std::invalid_argument) {
		Result.Status = EWordLengthStatus::Invalid_Status;
		return Result;
	}

	if (ValidLength < minLength || ValidLength > maxLength) {
		Result.Status = EWordLengthStatus::Outside_Range;
		return Result;
	} else {
		Result.Status = EWordLengthStatus::OK;
		Result.ValidLength = ValidLength;
		return Result;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const {
	if (Word.length() == 0 || Word.length() == 1) return true;
	TMap<char, bool> LetterMap;

	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterMap.find(Letter) == LetterMap.end()) { // Not in map
			LetterMap[Letter] = true;
		} else { // already seen it
			return false;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
	if (Word.length() == 0) return true;
	for (auto Letter : Word) {
		if (!islower(Letter)) { return false; }
	}
	return true;
}


// receives valid guess, increments turn, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	for (int32 i = 0; i < MyHiddenWord.length(); i++) {
		for (int32 j = 0; j < Guess.length(); j++) {
			if (MyHiddenWord[i] == Guess[j]) {
				if (i == j) {
					BullCowCount.Bulls++;
				} else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == MyHiddenWord.length()) {
		bGameIsWon = true;
	} else {
		bGameIsWon = false;
	}

	return BullCowCount;
}
