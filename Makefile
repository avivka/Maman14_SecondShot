all: assembler

assembler: main.o phase2.o phase1.o CreateBMC.o UtilsBMC.o FromBitToSign.o SymbolsTable.o CodeSegement.o Analyzer.o CommandBuilder.o CommandsIndex.o DataSegment.o Opearnds.o TextUtils.o Binary.o FileReader.o FileWriter.o Error.o List.o src/constants.h src/modules/statments_types.h
	gcc -g -Wall -pedantic -ansi main.o phase2.o phase1.o CreateBMC.o UtilsBMC.o FromBitToSign.o SymbolsTable.o CodeSegement.o Analyzer.o CommandBuilder.o CommandsIndex.o DataSegment.o Opearnds.o TextUtils.o Binary.o FileReader.o FileWriter.o Error.o List.o  -o assembler -lm
	rm *.o

main.o: src/main.c src/main.h src/constants.h
	gcc -c -Wall -pedantic  src/main.c -o main.o

phase2.o: src/phase2.c src/phase2.h src/constants.h
	gcc -c -Wall -pedantic  src/phase2.c -o phase2.o

phase1.o: src/phase1.c src/phase1.h src/constants.h
	gcc -c -Wall -pedantic  src/phase1.c -o phase1.o

CreateBMC.o: src/modules/CreateBMC.c src/modules/CreateBMC.h src/utils/UtilsBMC.h
	gcc -c -Wall -pedantic  src/modules/CreateBMC.c -o CreateBMC.o

UtilsBMC.o: src/utils/UtilsBMC.c src/utils/UtilsBMC.h
	gcc -c -Wall -pedantic  src/utils/UtilsBMC.c -o UtilsBMC.o

FromBitToSign.o: src/utils/FromBitToSign.c src/utils/FromBitToSign.h
	gcc -c -Wall -pedantic  src/utils/FromBitToSign.c -o FromBitToSign.o

SymbolsTable.o: src/modules/SymbolsTable.c src/modules/SymbolsTable.h src/constants.h
	gcc -c -Wall -pedantic  src/modules/SymbolsTable.c -o SymbolsTable.o

CodeSegement.o: src/modules/CodeSegement.c src/modules/CodeSegement.h src/constants.h
	gcc -c -Wall -pedantic  src/modules/CodeSegement.c -o CodeSegement.o

Analyzer.o: src/modules/Analyzer.c src/modules/Analyzer.h src/constants.h src/modules/statments_types.h
	gcc -c -Wall -pedantic  src/modules/Analyzer.c -o Analyzer.o

CommandBuilder.o: src/modules/CommandBuilder.c src/modules/CommandBuilder.h src/constants.h
	gcc -c -Wall -pedantic  src/modules/CommandBuilder.c -o CommandBuilder.o

CommandsIndex.o: src/modules/CommandsIndex.c src/modules/CommandsIndex.h src/constants.h
	gcc -c -Wall -pedantic  src/modules/CommandsIndex.c -o CommandsIndex.o

DataSegment.o: src/modules/DataSegment.c src/modules/DataSegment.h src/constants.h
	gcc -c -Wall -pedantic  src/modules/DataSegment.c -o DataSegment.o

Opearnds.o: src/modules/Opearnds.c src/modules/Opearnds.h src/constants.h src/modules/statments_types.h
	gcc -c -Wall -pedantic  src/modules/Opearnds.c -o Opearnds.o

TextUtils.o: src/utils/TextUtils.c src/utils/TextUtils.h src/constants.h
	gcc -c -Wall -pedantic  src/utils/TextUtils.c -o TextUtils.o

Binary.o: src/utils/Binary.c src/utils/Binary.h src/constants.h
	gcc -c -Wall -pedantic  src/utils/Binary.c -o Binary.o

FileReader.o: src/utils/FileReader.c src/utils/FileReader.h src/constants.h
	gcc -c -Wall -pedantic  src/utils/FileReader.c -o FileReader.o

FileWriter.o: src/utils/FileWriter.c src/utils/FileWriter.h src/constants.h
	gcc -c -Wall -pedantic  src/utils/FileWriter.c -o FileWriter.o

Error.o: src/utils/Error.c src/utils/Error.h src/constants.h
	gcc -c -Wall -pedantic  src/utils/Error.c -o Error.o

List.o: src/utils/List.c src/utils/List.h src/constants.h
	gcc -c -Wall -pedantic  src/utils/List.c -o List.o

clean:
	rm assembler*
	rm *.o