#include "application.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include <stdio.h>

void appStart(void)
{

    ST_cardData_t *cardData = &(ST_cardData_t){};
    ST_terminalData_t *termData = &(ST_terminalData_t){};
    ST_transaction_t *transData = &(ST_transaction_t){};
    ST_accountsDB_t *accountReference =  &(ST_accountsDB_t){};


    init_accountsDatabase();

    setMaxAmount(termData, 10000.0);
    //Card Module
    if (getCardHolderName(cardData) == WRONG_NAME) return;
    if (getCardExpiryDate(cardData) == WRONG_EXP_DATE) return;
    if (getCardPAN(cardData) == WRONG_PAN) return;

    printf("---------Hello %s!---------\n", cardData->cardHolderName);

    //Terminal Module
    getTransactionDate(termData);
    if (isCardExpired(cardData, termData) == EXPIRED_CARD)
        return;
    else
    {
        getTransactionAmount(termData);
        if (isBelowMaxAmount(termData) == EXCEED_MAX_AMOUNT)
          return;
        else
        {
            transData -> cardHolderData = *cardData;
            transData -> terminalData = *termData;
            //Server Module
            recieveTransactionData(transData);
            return;
        }

    }
}

int main(int argc, char const *argv[])
{
    appStart();
    return 0;
}
