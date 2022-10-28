#include "server.h"
#include "string.h"
#include <stdio.h>

ST_accountsDB_t accountsDatabase[255];
int currentAccountsDBRowIndex = 0;

ST_transaction_t transactionsDatabase[255] = {0};
int currentSequenceNumber = 0;
int currentTransactionDBRowIndex = 0;

//DONE
void init_accountsDatabase()
{
  ST_accountsDB_t tempAccount;
  int state_dummy_var = 0;
  float balance_dummy_var = 100.0;
  for (int i = 0 ; i < 10 ; i++)
  {
        tempAccount.balance = 1000.0 + balance_dummy_var;
        if (state_dummy_var % 2 == 0)
          tempAccount.state = BLOCKED;
        else
          tempAccount.state = RUNNING;
        state_dummy_var++;
        balance_dummy_var += 100.0;
        accountsDatabase[i] = tempAccount;
  }
    strcpy(accountsDatabase[0].primaryAccountNumber , "123456789123456780");
    strcpy(accountsDatabase[1].primaryAccountNumber , "123456789123456781");
    strcpy(accountsDatabase[2].primaryAccountNumber , "123456789123456782");
    strcpy(accountsDatabase[3].primaryAccountNumber , "123456789123456783");
    strcpy(accountsDatabase[4].primaryAccountNumber , "123456789123456784");
    strcpy(accountsDatabase[5].primaryAccountNumber , "123456789123456785");
    strcpy(accountsDatabase[6].primaryAccountNumber , "123456789123456786");
    strcpy(accountsDatabase[7].primaryAccountNumber , "123456789123456787");
    strcpy(accountsDatabase[8].primaryAccountNumber , "123456789123456788");
    strcpy(accountsDatabase[9].primaryAccountNumber , "123456789123456789");

    for (int i = 0; i < 10; i++)
        {
          printf("%f - ", accountsDatabase[i].balance);
          printf("%d - ", accountsDatabase[i].state);
          printf("%s  \n", accountsDatabase[i].primaryAccountNumber);
        }
}

//DONE
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
  ST_accountsDB_t accountReference;
  if (isValidAccount(&(transData -> cardHolderData), &accountReference) == SERVER_OK)
  {
    if (isBlockedAccount(&accountReference) == SERVER_OK)
    {
      if (isAmountAvailable(&(transData -> terminalData), &accountReference) == SERVER_OK)
      {
        accountReference.balance -= transData -> terminalData.transAmount;

        if (saveTransaction(transData) == SERVER_OK)
        {
          printf("Approved ");
          printf("New Balance: %f\n", accountReference.balance);
          return APPROVED;
        }

        else
        {
          printf("Internal Server Error!\n");
          return INTERNAL_SERVER_ERROR;
        }
      }
      else
      {
        printf("Declined: Insuffecient fund!\n");
        return DECLINED_INSUFFECIENT_FUND;
      }

    }
    else
    {
      printf("Declined: Stolen card!\n");
      return DECLINED_STOLEN_CARD;
    }

  }
  else
  {
    printf("Fruad card!\n");
    return FRAUD_CARD;
  }
}

//DONE
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountReference)
{

  for (int i = 0; i < 255; i++)
  {
    if (strcmp((accountsDatabase[i].primaryAccountNumber), (cardData -> primaryAccountNumber)) == 0)
    {
      *accountReference = accountsDatabase[i];
      return SERVER_OK ;
    }
  }
  printf("Invalid: Accound is not found!\n");
  return ACCOUNT_NOT_FOUND;
}

//DONE
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference)
{
  if (((uint32_t)(termData -> transAmount)) > ((uint32_t)(accountReference -> balance)))
  {
    printf("Low balance!\n");
    return LOW_BALANCE;
  }
  return SERVER_OK;
}

//DONE
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
  if (accountRefrence -> state == BLOCKED)
  {
    printf("Blocked account!\n");
    return BLOCKED_ACCOUNT;
  }
  return SERVER_OK;
}


//DONE
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
  int seqNumber = currentSequenceNumber + 1;
  transData -> transactionSequenceNumber = seqNumber;
  transactionsDatabase[currentTransactionDBRowIndex] = *transData;
  // EN_serverError_t status = SERVER_OK;
  // EN_serverError_t status = TRANSACTION_NOT_FOUND;
  EN_serverError_t status = getTransaction(seqNumber, transData);
  if (status == SERVER_OK)
  {
    currentSequenceNumber++;
    currentTransactionDBRowIndex++;
    return SERVER_OK;
  }
  else
  {
    printf("Saving failed!\n");
    //Recovering
    currentSequenceNumber--;
    currentTransactionDBRowIndex--;
    transactionsDatabase[currentTransactionDBRowIndex] = (ST_transaction_t){};
    return SAVING_FAILED;
  }
}

//DONE
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
  for (int i = 0; i < 255; i++)
  {
    if (transactionSequenceNumber == transactionsDatabase[i].transactionSequenceNumber)
    {
      *transData = transactionsDatabase[i];
      return SERVER_OK ;
    }
  }
  printf("Transaction not found!\n");
  return TRANSACTION_NOT_FOUND;
}

// int main(int argc, char const *argv[])
// {
//     init_accountsDatabase();
//     for (int i = 0; i < 10; i++)
//     {
//       printf("%f - ", accountsDatabase[i].balance);
//       printf("%d - ", accountsDatabase[i].state);
//       printf("%s  \n", accountsDatabase[i].primaryAccountNumber);
//     }

    /*
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
    */
    // for (int i = 0; i < 10; i++)
    // {
      // printf("%s %s %s\n", transactionsDatabase[i].cardHolderData.cardHolderName, transactionsDatabase[i].cardHolderData.primaryAccountNumber, transactionsDatabase[i].cardHolderData.cardExpirationDate);
      // printf("%d - ", transactionsDatabase[i].state);
      // printf("%s  \n", transactionsDatabase[i].primaryAccountNumber);
    // }
    // 123456789123456789
    // 898937461543685154
    // ST_accountsDB_t accountReference;



    // ST_cardData_t cardHolderData = {"IslamAlaaEddin", "123456789123456789", "12/25"};
    // ST_terminalData_t terminalData = {3000.0, 10000.0, "20/09/2022"};
    // EN_transState_t transState = APPROVED;
    // uint32_t transactionSequenceNumber = 10;
    // ST_transaction_t transaction = {cardHolderData, terminalData, transState, transactionSequenceNumber};
    //
    // recieveTransactionData(&transaction);
    // transactionsDatabase[0] = transaction;
    // getTransaction(12, &transaction);
    // saveTransaction(&transaction);

    //
    // for (int i = 0; i < 100; i++) {
    //   printf("%f - ", accountsDatabase[i].balance);
    //   printf("%s - ", accountsDatabase[i].state);
    //   printf("%s\n", accountsDatabase[i].primaryAccountNumber);
    //   printf("--------------------------\n");
    // }

    // return 0;
// }
