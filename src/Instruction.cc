#include "Instruction.hh"

#include <stdint.h>
#include <stdio.h>
#include <cstring>


OpCode stringToOpCode(char const * token)
{
	if (strcmp(token,"jmp") == 0) return op_jmp;
	else if (strcmp(token,"jeq") == 0) return op_jeq;
	else if (strcmp(token,"jne") == 0) return op_jne;
	else if (strcmp(token,"jlt") == 0) return op_jlt;
	else if (strcmp(token,"jlg") == 0) return op_jle;
 	else if (strcmp(token,"jgt") == 0) return op_jgt;
	else if (strcmp(token,"jge") == 0) return op_jge;
	else if (strcmp(token,"call") == 0) return op_call;
	else if (strcmp(token,"set") == 0) return op_set;
	else if (strcmp(token,"add") == 0) return op_add;
	else if (strcmp(token,"sub") == 0) return op_sub;
	else if (strcmp(token,"move") == 0) return op_move;
	else if (strcmp(token,"dump") == 0) return op_dump;
	else if (strcmp(token,"end") == 0) return op_end;
	else if (strcmp(token,"label") == 0) return label;
	else return invalid;
}


Instruction::Instruction(OpCode pCode):
code(pCode)
{
	args = NULL;
}


Instruction::Instruction(OpCode pCode,uint8_t * pArgs):
code(pCode),
args(pArgs)
{}


Instruction::Instruction(FILE * inFile)
{
	code = op_jmp;
	fread(&code,OP_CODE_SIZE,1,inFile);

	switch(code)
	{
	case op_jmp:
		args = new uint8_t[LABEL_SIZE];
		fread(args,LABEL_SIZE,1,inFile);
		break;

	case op_jeq:
	case op_jne:
	case op_jlt:
	case op_jle:
	case op_jgt:
	case op_jge:
		args = new uint8_t[LABEL_SIZE + VAR_SIZE];
		fread(args,LABEL_SIZE + VAR_SIZE,1,inFile);
		break;

	case op_set:
		args = new uint8_t[CONST_SIZE + VAR_SIZE];
		fread(args,CONST_SIZE + VAR_SIZE,1,inFile);
		break;

	case op_move:
		args = new uint8_t[VAR_SIZE * 2];
		fread(args,VAR_SIZE * 2,1,inFile);
		break;

	case op_add:
	case op_sub:
		args = new uint8_t[3];
		fread(args,VAR_SIZE * 3,1,inFile);
		break;

	case op_call:
		int argLength;
		fread(&argLength,2,1,inFile);
		args = new uint8_t[argLength];
		args[0] = argLength & 0xFF;
		args[1] = (argLength >> 8) & 0xFF;
		fread(args + 2,1,argLength - 2,inFile);
		break;
	}
}


Instruction::~Instruction()
{
	if (args != NULL)
	{
		delete[] args;
		args = NULL;
	}
}


void Instruction::toFile(FILE * outFile)
{
	printf("%d\n",code);

	fwrite(&code,OP_CODE_SIZE,1,outFile);

	switch(code)
	{
	case op_jmp:
		fwrite(args,1,LABEL_SIZE,outFile);
		break;

	case op_jeq:
	case op_jne:
	case op_jlt:
	case op_jle:
	case op_jgt:
	case op_jge:
		fwrite(args,1,LABEL_SIZE + VAR_SIZE,outFile);
		break;

	case op_set:
		fwrite(args,1,CONST_SIZE + VAR_SIZE,outFile);
		break;

	case op_move:
		fwrite(args,1,VAR_SIZE * 2,outFile);
		break;

	case op_add:
	case op_sub:
		fwrite(args,1,VAR_SIZE * 3,outFile);
		break;

	case op_call:
		int argLength = args[0] | (args[1] << 8);
		fwrite(args,1,argLength,outFile);
		break;
	}
}
