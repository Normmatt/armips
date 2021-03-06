#pragma once
#include <vector>
#include "Util/Util.h"

class Logger
{
public:
	enum ErrorType { Warning, Error, FatalError, Notice };

	static void clear();
	static void printLine(const std::wstring& text);
	static void printLine(const char* text, ...);
	static void printError(ErrorType type, const std::wstring& text);
	static void printError(ErrorType type, const wchar_t* format, ...);
	static void queueError(ErrorType type, const std::wstring& text);
	static void queueError(ErrorType type, const wchar_t* format, ...);
	static void printQueue();
	static void clearQueue() { queue.clear(); };
	static StringList getErrors() { return errors; };
	static bool hasError() { return error; };
	static bool hasFatalError() { return fatalError; };
private:
	static std::wstring formatError(ErrorType type, const std::wstring& text);
	static void setFlags(ErrorType type);

	struct QueueEntry
	{
		ErrorType type;
		std::wstring text;
	};

	static std::vector<QueueEntry> queue;
	static std::vector<std::wstring> errors;
	static bool error;
	static bool fatalError;
};

class ConditionData
{
public:
	void addIf(bool conditionMet);
	void addElse();
	void addElseIf(bool conditionMet);
	void addEndIf();
	bool conditionTrue();
	size_t activeConditions() { return conditions.size(); };
private:
	struct Entry
	{
		bool currentConditionMet;
		bool matchingCaseExecuted;
		bool isInElseCase;
	};

	std::vector<Entry> conditions;
};

class AreaData
{
public:
	void startArea(int start, int size, int fileNum, int lineNumber);
	void endArea();
	bool checkAreas();
private:
	struct Entry
	{
		int start;
		int maxAddress;
		int fileNum;
		int lineNumber;
		bool overflow;
	};

	std::vector<Entry> entries;
};