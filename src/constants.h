
#ifndef ASSEMBLER_CONSTANTS_H
#define ASSEMBLER_CONSTANTS_H

#define MAX_LINE_SIZE 80
#define  MAX_LABEL_SIZE 80
#define MEMOERY_START_ADDRESS 100
#define  MAX_FILE_NAME_SIZE 80
#define NUMBER_ZERO_ASCII_CODE 48
#define NUMBER_SEVEN_ASCII_CODE 55
#define MACHINE_CODE_LINE_LENGTH 14


/** a simple boolean definition */
typedef enum { FALSE, TRUE } boolean;

/**
* OperandType, defines what is the type of the given operand.
* The different types of operands we have in our system:
* REGISTER_OPERAND - an operand which points to a valid register name,
* LABEL_OPERAND - an operand which points to a previously declared label
* DIRECT_VALUE_OPERAND - an operand which points directly to a its value, either a string in case .string operation, or number in .data or #-1 cases.
* INDEX_OPERAND- an operands which points to a special index operand.
* NO_OPERAND - indicates that no operand was given
*/
typedef enum {
    DIRECT_VALUE_OPERAND, /*addressing method 0*/
    LABEL_OPERAND, /*addressing method 1*/
    INDEX_OPERAND, /*addressing method 2*/
    REGISTER_OPERAND, /*addressing method 3*/
    NO_OPERAND
} OperandType;

#endif
