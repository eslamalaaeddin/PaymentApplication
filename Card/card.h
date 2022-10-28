#ifndef CARD
#define CARD

typedef unsigned char uint8_t;

//Enum for different card errors
typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}
EN_cardError_t;

//Structure for modeling a card
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}
ST_cardData_t;


EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);
int isCardHolderNameAlphabetic(uint8_t cardHolderName[]);
int isCardPANAlphanumeric(uint8_t cardPAN[]);
int isCardExpDateAlphanumeric(uint8_t cardExpirationDate[]);
int isValidExpiryDate(uint8_t cardExpirationDate[]);


#endif
