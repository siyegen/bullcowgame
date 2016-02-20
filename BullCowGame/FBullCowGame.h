#pragma once
#include <string>

using FString = std::string;
using int32 = int;

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum class EWordLengthStatus {
	Invalid_Status,
	OK,
	Outside_Range
};

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

struct FWordLengthResult {
	int32 ValidLength = 0;
	EWordLengthStatus Status = EWordLengthStatus::Invalid_Status;
};

class FBullCowGame {
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	int32 GetMinLength() const;
	int32 GetMaxLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	FWordLengthResult CheckWordLength(FString) const;

	void Reset();

	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	int32 minLength;
	int32 maxLength;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};