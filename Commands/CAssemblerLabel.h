#pragma once
#include "Commands/CAssemblerCommand.h"

class Label;

class CAssemblerLabel: public CAssemblerCommand
{
public:
	CAssemblerLabel(const std::wstring& name, int RamPos, int Section, bool constant);
	virtual bool Validate();
	virtual void Encode() { };
	virtual void writeTempData(TempData& tempData);
	virtual void writeSymData(SymbolData& symData);
private:
	Label* label;
	bool constant;
};

class CDirectiveFunction: public CAssemblerCommand
{
public:
	CDirectiveFunction(const std::wstring& name, int Section);
	virtual bool Validate();
	virtual void Encode() { };
	virtual void writeTempData(TempData& tempData);
	virtual void writeSymData(SymbolData& symData);
private:
	CAssemblerLabel* label;
};
