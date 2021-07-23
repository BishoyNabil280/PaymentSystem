/*
 ============================================================================
 Name        : Payment_System.c
 Author      : Bishoy Nabil
 Version     :
 Copyright   : Your copyright notice
 Description : Payment system
 ============================================================================
 */
#include "../PaymentSystem/payment_system.h"

#include<stdio.h>
#include<string.h>

#include "../PaymentSystem/compiler.h"

#define MAX_AMOUNT 5000

EN_transStat_t Server_check(ST_terminalData_t *terminalData, ST_cardData_t *cardData)
{
	uint8_t ua8_counter;
	for(ua8_counter=0;ua8_counter<10;ua8_counter++)
	{
		if(strcmp(cardData->primaryAccountNumber, accBalance[ua8_counter].primaryAccountNumber)==0)
			break;
	}
	if(ua8_counter==10)
	{
		printf("Primary Account Number is not found!\n");
		fflush(stdout);
		return DECLINED;
	}else
	{
		if(terminalData->transAmount <= accBalance[ua8_counter].balance)
		{
			accBalance[ua8_counter].balance-=terminalData->transAmount;
			return APPROVED;
		}else
		{
			printf("Balance Not Found!\n");
			fflush(stdout);
			return DECLINED;
		}
	}
}

EN_transStat_t terminalData_Entry(ST_terminalData_t *terminalData, ST_cardData_t *cardData)
{
	uint8_t ua8_cardMonth, ua8_cardYear, ua8_transMonth, ua8_transYear;
	terminalData->maxTransAmount=MAX_AMOUNT;
	printf("Please Enter Terminal Data:\n");
	printf("Please Enter the transaction Amount:\n");
	fflush(stdout);
	scanf("%f",&(terminalData->transAmount));
	fflush(stdin);
	if(terminalData->transAmount>terminalData->maxTransAmount)
	{
		printf("Transaction amount exceeded the Max limit!\n");
		fflush(stdout);
		return DECLINED;
	}
	printf("Please Enter transaction Date (DD/MM/YYYY):\n");
	fflush(stdout);
	gets(terminalData->transactionDate);
	fflush(stdin);
	ua8_cardMonth=((cardData->cardExpirationDate[0]*10) + cardData->cardExpirationDate[1]);
	ua8_cardYear=((cardData->cardExpirationDate[3]*10) + cardData->cardExpirationDate[4]);
	ua8_transMonth=((terminalData->transactionDate[3]*10) + terminalData->transactionDate[4]);
	ua8_transYear=((terminalData->transactionDate[8]*10) + terminalData->transactionDate[9]);
	if(ua8_transYear>ua8_cardYear)
	{
		printf("Card is expired!\n");
		fflush(stdout);
		return DECLINED;
	}else if(ua8_transYear<ua8_cardYear)
		return APPROVED;
	else if(ua8_transYear==ua8_cardYear)
	{
		if(ua8_transMonth<=ua8_cardMonth)
			return APPROVED;
		else
		{
			printf("Card is expired!\n");
			fflush(stdout);
			return DECLINED;
		}
	}
}

void serverData_Init(void)
{
	strcpy(accBalance[0].primaryAccountNumber,"123456789");
	accBalance[0].balance=100;
	strcpy(accBalance[1].primaryAccountNumber,"234567891");
	accBalance[1].balance=6000;
	strcpy(accBalance[2].primaryAccountNumber,"567891234");
	accBalance[2].balance=3250.25;
	strcpy(accBalance[3].primaryAccountNumber,"456789123");
	accBalance[3].balance=1500.12;
	strcpy(accBalance[4].primaryAccountNumber,"258649173");
	accBalance[4].balance=500;
	strcpy(accBalance[5].primaryAccountNumber,"654823719");
	accBalance[5].balance=2100;
	strcpy(accBalance[6].primaryAccountNumber,"971362485");
	accBalance[6].balance=0;
	strcpy(accBalance[7].primaryAccountNumber,"793148625");
	accBalance[7].balance=1;
	strcpy(accBalance[8].primaryAccountNumber,"123123456");
	accBalance[8].balance=10.12;
	strcpy(accBalance[9].primaryAccountNumber,"456789321");
	accBalance[9].balance=0.55;
}


void cardData_Entry(ST_cardData_t *cardData)
{
	printf("Please Enter Card Data:\n");
	printf("Please Enter the Card Holder Name:\n");
	fflush(stdout);
	gets(cardData->cardHolderName);
	fflush(stdin);
	printf("Please enter the Primary Account Number:\n");
	fflush(stdout);
	gets(cardData->primaryAccountNumber);
	fflush(stdin);
	printf("Please Enter Card Expiry Date (MM/YY):\n");
	fflush(stdout);
	gets(cardData->cardExpirationDate);
	fflush(stdin);
}
