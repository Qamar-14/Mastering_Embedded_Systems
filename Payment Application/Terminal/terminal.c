#ifndef _TERMINALC_
#define _TERMINALC_

#include "terminal.h"
#include <time.h>
#include <stdio.h>
#include <ctype.h>



EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	time_t tim;
	char t[50];
	struct tm *detl;
	time( &tim );
	detl = localtime( &tim );
	strftime(t, 20, "%x - %I:%M %p", detl);

	printf("Date & time is : %s",t);
	fflush(stdout);
	printf("\nPlease enter date of transaction in the following format DD/MM/YYYY, e.g 25/06/2022.: \n");
	fflush(stdout);
	int i, date=0;

	gets((char*)termData->transactionDate);
	for(i=0; termData->transactionDate[i]!='\0';i++)
	{
		date++;
	}

	if(( date < 10 )||(date == 0 ))
		return WRONG_DATE ;
	else if ((termData->transactionDate[2] != '/')&&(termData->transactionDate[2] != '/'))
		return WRONG_DATE ;
	/*else {
		for(i=0; termData->transactionDate[i]!='\0';i++)
		{
			if((i!=2)&&(i!=4))
			{
				if (!isdigit(termData->transactionDate[i]))
					return  WRONG_DATE ;
			}
		}
	}*/
	return OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
	if((termData.transactionDate[9] < cardData.cardExpirationDate[4])&&(termData.transactionDate[8] <= cardData.cardExpirationDate[3])){
		return OK_;
	}
	if(termData.transactionDate[8] < cardData.cardExpirationDate[3])
	{
		return OK_;
	}
	if((termData.transactionDate[9] == cardData.cardExpirationDate[4])&&(termData.transactionDate[8] == cardData.cardExpirationDate[3])){
		if(termData.transactionDate[3] > cardData.cardExpirationDate[0]){
			return OK_;
		}
		else if((termData.transactionDate[4] < cardData.cardExpirationDate[1])&&(termData.transactionDate[3] <= cardData.cardExpirationDate[0]))
		{
			return OK_;
		}
	}
	return EXPIRED_CARD;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
	printf("Please enter the transaction amount:\n");
	fflush(stdout);

	scanf("%f",  &termData->transAmount);
	if(termData->transAmount <= 0 )
		return INVALID_AMOUNT;
	return OK_;

}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, ST_cardData_t *cardData)
{
	printf("Enter maximum amount for a transaction: ");
	fflush(stdout);

	float max;
	scanf("%f", &max);
	if (max <= 0)
		return INVALID_MAX_AMOUNT;
	termData->maxTransAmount = max;
	return OK_;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	if(termData->maxTransAmount < termData->transAmount  )
		return EXCEED_MAX_AMOUNT;
	else
		return OK_;

}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	char cardPan[20];
	int size = 20;

	int i;

	for (int i = 0; i < size; i++) {
		cardPan[i] = cardData->primaryAccountNumber[i];
	}
	int check_digit;
	int start_index;
	int num;

	for (i = size - 1; i >= 0; --i)
	{
		if (cardPan[i] != '\0')
		{
			check_digit = cardPan[i] - '0';
			start_index = i - 1;
			break;
		}
	}
	for (int i = start_index; i >= 0; i -= 2)
	{
		if (cardPan[i] == '\0')
			continue;
		num = cardPan[i] - '0';
		num *= 2;
		if (num < 10)
			cardPan[i] = '0' + num;
		else
			cardPan[i] = '0' + num - 9;
	}
	int sum = 0;
	for (int i = 0; i <= start_index; i++) {
		if (cardPan[i] == '\0')
			continue;
		sum += cardPan[i] - '0';
	}
	if (sum % 10 == check_digit)
		return OK;
	else return INVALID_CARD;
}

#endif
