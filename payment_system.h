/*
 * payment_system.h
 *
 *      Author: Bishoy Nabil
 */

#ifndef PAYMENT_SYSTEM_H_
#define PAYMENT_SYSTEM_H_

/* Card Data Structure */

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

/* Terminal Data Structure */

typedef struct ST_terminalData_t
{
	float32_t transAmount;
	float32_t maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

/* Transaction Status Enum */

typedef enum EN_transStat_t
{
	DECLINED,
	APPROVED
}EN_transStat_t;

/* Transaction Data Structure */

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t transData;
	EN_transStat_t transStat;
}ST_transaction;

/* Account Balance Structure */

typedef struct ST_accountBalance_t
{
	float32_t balance;
	uint8_t primaryAccountNumber[20];
}ST_accountBalance_t;

extern ST_accountBalance_t accBalance[10];

/* APIs */

void cardData_Entry(ST_cardData_t *cardData);
void serverData_Init(void);
EN_transStat_t terminalData_Entry(ST_terminalData_t *terminalData, ST_cardData_t *cardData);
EN_transStat_t Server_check(ST_terminalData_t *terminalData,ST_cardData_t *cardData);

#endif /* PAYMENT_SYSTEM_H_ */
