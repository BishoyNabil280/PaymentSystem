/*
 * payment.c
 *
 *      Author: Bishoy Nabil
 */
#include<stdio.h>
#include<string.h>

#include "../PaymentSystem/compiler.h"
#include "../PaymentSystem/payment_system.h"

ST_accountBalance_t accBalance[10];

int main(void)
{
	EN_transStat_t status;
	uint8_t ua8_cont='y';
	ST_cardData_t cardData;
	ST_terminalData_t terminalData;
	serverData_Init();
	while(ua8_cont=='y')
	{
		cardData_Entry(&cardData);
		status=terminalData_Entry(&terminalData,&cardData);
		if(status==APPROVED)
		{
			printf("Verifying Data from the server....\n");
			fflush(stdout);
			status=Server_check(&terminalData, &cardData);
			if(status==APPROVED)
			{
				printf("The transaction is APPROVED!\n");
				printf("Do you want to continue (y/n)?:\n");
				fflush(stdout);
				scanf("%c",&ua8_cont);
				fflush(stdin);
			}else
			{
				printf("The transaction is DECLINED!\n");
				printf("Do you want to continue (y/n)?:\n");
				fflush(stdout);
				scanf("%c",&ua8_cont);
				fflush(stdin);
			}
		}else
		{
			printf("The transaction is DECLINED!\n");
			printf("Do you want to continue (y/n)?:\n");
			fflush(stdout);
			scanf("%c",&ua8_cont);
			fflush(stdin);
		}
	}
	return 0;
}
