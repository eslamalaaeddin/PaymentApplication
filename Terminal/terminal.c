#include "terminal.h"
#include<stdio.h>
#include <time.h>
#include<string.h>
#include <stdint.h>

//DONE
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    unsigned int day, month, year;

    // arithmetic type for time to store time since 1970
    time_t now;
    // time() returns the current time of the system as a time_t value
    time(&now);
    // localtime converts a `time_t` value to calendar time and
    // returns a pointer to a `tm` structure with its members
    // filled with the corresponding values
    struct tm *local = localtime(&now);

    day = local -> tm_mday;            // get day of month (1 to 31)
    month = local -> tm_mon + 1;      // get month of year (0 to 11)
    year = local -> tm_year + 1900;   // get year since 1900 122

    char dayString[4];
    char monthString[4];
    char yearString[5];

    // Convert integers to string
    //Reformats an int the assigns it to a string // 5 05
    if (day < 10)
        sprintf(dayString, "0%d/", day);
    else
        sprintf(dayString, "%d/", day);

    if (month < 10)
        sprintf(monthString, "0%d/", month);
    else
        sprintf(monthString, "%d/", month);

    sprintf(yearString, "%d", year);

    //Copy the concatenated day month year into the transactionDate field
    strcpy(termData -> transactionDate, strcat(strcat(dayString, monthString), yearString)); // 20/09/2022

    // printf("%s\n", termData -> transactionDate);
    // printf("%d\n", strlen(termData -> transactionDate));
}

//DONE
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
  //TRANSACTION DATE: Converting from string to integer for comparison 20/09/2022
  char ch1 = termData -> transactionDate[3];
  char ch2 = termData -> transactionDate[4];
  char ch3 = termData -> transactionDate[8];
  char ch4 = termData -> transactionDate[9];

  short m1 = ((int)(ch1)) - 48; //0
  short m2 = ((int)(ch2)) - 48; //9
  short y1 = ((int)(ch3)) - 48; //2
  short y2 = ((int)(ch4)) - 48; //2

  short mm_transaction = m1 * 10 + m2; // 09
  short yy_transcation = y1 * 10 + y2; // 22

  //CARD EXP. DATE: : Converting from string to integer for comparison 12/25
  ch1 = cardData -> cardExpirationDate[0];
  ch2 = cardData -> cardExpirationDate[1];
  ch3 = cardData -> cardExpirationDate[3];
  ch4 = cardData -> cardExpirationDate[4];

  m1 = ((short)(ch1)) - 48; //1
  m2 = ((short)(ch2)) - 48; //2
  y1 = ((short)(ch3)) - 48; //2
  y2 = ((short)(ch4)) - 48; //4

  short mm_card = m1 * 10 + m2;
  short yy_card = y1 * 10 + y2;

  /////////BEGINNING
  // printf("Card: %d/", mm_card);
  // printf("%d\n", yy_card);
  // printf("Transaction: %d/", mm_transaction);
  // printf("%d\n", yy_transcation);

  if (yy_card > yy_transcation)
  {
    return TERMINAL_OK;
  }
  else if (yy_card == yy_transcation)
  {
    if (mm_card >= mm_transaction)
    {
      return TERMINAL_OK;
    }
    else
    {
      printf("ERROR: Expired card.\n");
      return EXPIRED_CARD;
    }
  }
  else
  {
    printf("ERROR: Expired card.\n");
    return EXPIRED_CARD;
  }
}

//DONE
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
        printf("Please enter card transaction amount: ");
        float amount = 0.0;
        scanf("%f", &amount);
        if ((int)(amount*100) <= 0)
        {
          printf("ERROR: Invalid ammount.\n");
          return INVALID_AMOUNT;
        }

        termData -> transAmount = amount;
        // printf("%f\n", termData->transAmount);
        return TERMINAL_OK;
    }

//DONE
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float amount)
{
    if ((int)(amount * 100) <= 0)
    {
      printf("ERROR: Invalid max amount.\n");
      return INVALID_MAX_AMOUNT;
    }
    // printf("%s\n", "Valid");
    termData -> maxTransAmount = amount;
    // printf("%f\n", termData->maxTransAmount);
    return TERMINAL_OK;
}

//DONE
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if ((uint32_t)(termData -> transAmount) > (uint32_t)(termData -> maxTransAmount))
    {
      printf("ERROR: Exceeds max amount.\n");
      return EXCEED_MAX_AMOUNT;
    }
    // printf("%s\n", "Pass");
    return TERMINAL_OK;

}



// int main(int argc, char const *argv[])
// {
//     /*
//     float transAmount;
//     float maxTransAmount;
//     uint8_t transactionDate[11];
//     */
    // ST_terminalData_t termData = {100.0, 1000.0, ""};

    // ST_cardData_t cardHolderData = {"IslamAlaaEddin", "8989374615436851", "12/25"};
    // getTransactionDate(&termData);
    // isCardExpired(&cardHolderData, &termData);

    // getTransactionAmount(&termData);
    // setMaxAmount(&termData, 2000.0);
    // isBelowMaxAmount(&termData);
//     // termData -> transAmount = 2000.0;
//     // isBelowMaxAmount(termData);



//     // setMaxAmount(termData);
//     // printf("%f\n", termData->maxTransAmount);
//     return 0;
// }
