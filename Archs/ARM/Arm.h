#pragma once
#include "Util/CommonClasses.h"
#include "Pool.h"

#define ARM_SHIFT_LSL		0x00
#define ARM_SHIFT_LSR		0x01
#define ARM_SHIFT_ASR		0x02
#define ARM_SHIFT_ROR		0x03
#define ARM_SHIFT_RRX		0x04

typedef struct {
	char* name;
	short num;
	short len;
} tArmRegister;

typedef struct {
	char Name[4];
	int Number;
} tArmRegisterInfo;

extern const tArmRegister ArmRegister[];

class CArmArchitecture: public CArchitecture
{
public:
	CArmArchitecture();
	~CArmArchitecture();
	virtual void AssembleOpcode(const std::wstring& name, const std::wstring& args);
	virtual bool AssembleDirective(const std::wstring& name, const std::wstring& args);
	virtual void NextSection();
	virtual void Pass2();
	virtual void Revalidate();
	virtual int GetWordSize() { return 4; };
	void SetThumbMode(bool b) { thumb = b; };
	bool GetThumbMode() { return thumb; };
	void SetArm9(bool b) { arm9 = b; };
	int NewPool() { return PoolCount++; };
	ArmPool& GetPool(int num) { return Pools[num]; };
	int AddToCurrentPool(int value);
	void NextPool() { CurrentPool++; };
private:
	bool thumb;
	bool arm9;
	ArmPool* Pools;
	int PoolCount;
	int CurrentPool;
};

extern CArmArchitecture Arm;;

bool ArmGetRegister(char* source, int& RetLen, tArmRegisterInfo& Result);
int ArmGetRegister(char* source, int& RetLen);
bool ArmCheckImmediate(char* Source, char* Dest, int& RetLen, CStringList& List);
bool ArmGetRlist(char* source, int& RetLen, int ValidRegisters, int& Result);
int ArmGetShiftedImmediate(unsigned int num, int& ShiftAmount);
bool ArmGetCopNumber(char* source, int& RetLen, tArmRegisterInfo& Result);
bool ArmGetCopRegister(char* source, int& RetLen, tArmRegisterInfo& Result);
