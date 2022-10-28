#include "card.h"
#include <stdio.h>
#include <string.h>

//DONE
int isCardHolderNameAlphabetic(uint8_t cardHolderName[])
{
  char* ch;
  for (ch = cardHolderName; *ch != '\0'; ch++)
  {
    if (!((*ch >= 'A' && *ch <= 'Z') || (*ch >= 'a' && *ch <= 'z'))) return 0; //FALSE
  }
  return 1; //TRUE
}

//DONE
int isCardPANAlphanumeric(uint8_t cardPAN[])
{
  char* ch;
  for (ch = cardPAN; *ch != '\0'; ch++)
  {
    if (!(*ch >= '0' && *ch <= '9')) return 0; //FALSE
  }
  return 1; //TRUE
}

//DONE
int isCardExpDateAlphanumeric(uint8_t cardExpirationDate[])
{
  char* ch;
  short i = 0;
  for (ch = cardExpirationDate; *ch != '\0'; ch++, i++)
  {
    if (i != 2)
    {
      if (!(*ch >= '0' && *ch <= '9')) return 0; //FALSE
    }

  }
  return 1; //TRUE
}

//DONE
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    printf("Please enter card holder name: ");
    gets(cardData->cardHolderName);
    unsigned short nameLength = strlen(cardData->cardHolderName);
    if (cardData->cardHolderName == NULL || nameLength < 20 || nameLength > 24 || isCardHolderNameAlphabetic(cardData->cardHolderName) == 0)
    {
      printf("ERROR: Wrong card name\n");
      return WRONG_NAME;
    }
    return CARD_OK;
}

//DONE
int isValidExpiryDate(uint8_t cardExpirationDate[])
{
  // 12/25
  if (cardExpirationDate[2] != '/') return 0;

  int res = isCardExpDateAlphanumeric(cardExpirationDate);
  if (res == 0) return 0;

  //Getting Exp Date as integer mm and integer yy. 12/25
  char ch1 = cardExpirationDate[0];
  char ch2 = cardExpirationDate[1];

  short m1 = ((short)(ch1)) - 48; //1
  short m2 = ((short)(ch2)) - 48; //2

  short mm_card = m1 * 10 + m2;

  if (mm_card > 12) return 0;//Not valid

  return 1;//Valid
}

//DONE
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    printf("Please enter card expiry date in the format MM/YY: ");
    gets(cardData->cardExpirationDate);
    unsigned short cardExpDateLength = strlen(cardData->cardExpirationDate);
    if (cardData->cardExpirationDate == NULL || cardExpDateLength != 5 || isValidExpiryDate(cardData->cardExpirationDate) == 0)
    {
      printf("ERROR: Wrong card expiry date\n");
      return WRONG_EXP_DATE;
    }

    return CARD_OK;
}

//DONE
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    printf("Please enter card primary account number: ");
    gets(cardData->primaryAccountNumber);
    unsigned short numberLength = strlen(cardData->primaryAccountNumber);
    if (cardData->primaryAccountNumber == NULL || numberLength < 16 || numberLength > 19 || isCardPANAlphanumeric(cardData -> primaryAccountNumber) == 0 )
      {
      printf("ERROR: Wrong card primary account number\n");
      return WRONG_PAN;
    }
    return CARD_OK;
}

// int main()
// {
//     ST_cardData_t *cardData = &(ST_cardData_t){};
//
//     getCardPAN(cardData);
//
//
//     return 0;
// }
