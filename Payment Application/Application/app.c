#ifndef _APP_C_

#define _APP_C_
#include "../Application/app.h"

void appStart(void){
	ST_cardData_t cardData;
	ST_terminalData_t termData;
	ST_transaction_t transData;
	while (getCardHolderName(&cardData) == WRONG_NAME) {
		printf("\n\t<<<WRONG NAME>>>\n");
		printf("Re-enter:\n");

	}
	while (getCardPAN(&cardData) == WRONG_PAN) {
		printf("\n\t<<<WRONG PAN>>>\n");
		printf("Re-enter:\n");
	}
	while(getCardExpiryDate(&cardData) == WRONG_EXP_DATE) {
		printf("\n\t<<<WRONG EXPIRE DATE>>>\n");
		printf("Re-enter:\n");

	}
	while(getTransactionDate(&termData) == WRONG_DATE) {
		printf("\n\t<<<WRONG DATE>>>\n");
		printf("Re-enter:\n");
	}
	if (isCardExpired(cardData, termData) == EXPIRED_CARD) {
		printf("\n\n\t<<<DECLINED EXPIRED CARD>>>\n");
	}
	if (isCardExpired(cardData, termData) == OK_)
	{
		//If card is not expired check if amount exceeds limit
		if (getTransactionAmount(&termData) == INVALID_AMOUNT)
		{
			printf("\n\t<<<DECLINED AMOUNT EXCEEDING LIMIT>>>\n");
		}
		else //transaction amount does not exceed limit
		{
			//Check if account is valid
			/*if (isValidAccount(&cardData) == ACCOUNT_NOT_FOUND )
			{
				printf("\n\t<<<DECLINED INAVLID ACCOUNT>>>\n");
			}*/
			 //account is valid
			{
				//Check if the amount is available
				if(isAmountAvailable(&termData)==LOW_BALANCE)
				{
					printf("\n\t<<<DECLINED INSUFFECIENT FUNDS>>>\n");

				}
				else
				{
					saveTransaction(&transData);

				}
			}
		}
	}
}
#endif
