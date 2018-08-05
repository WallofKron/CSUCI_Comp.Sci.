/*
 *  testSolvency.c
 *  Created by AJ Bieszczad on 3/11/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 * A test on solvency of a bank.
 * Usage:
 *	       testSolvency <input file>
 * e.g.
 *	       testSolvency in.txt
 * Once this is entered, the user can interact as explained further.
 */

#define MAX_NUM_IN_LINE 256

#include <unistd.h>
#include "bank.h"

void readLine(int[]);
void strToUpper(char **);

int numOfCustomers;
int numOfAccounts;

void simulateBank();
void loadBankState();

int main(int argc, char *argv[])
{
   int savedstdin = dup(STDIN_FILENO);
   if (argc > 1)
      if (freopen(argv[1], "r", stdin) == NULL)
      {
         printf("Cannot read from file %s\n%s (errno = %d)).\n", argv[1], strerror(errno), errno);
         exit(1);
      }

   // get the name of the input file
   loadBankState();

   fflush(stdin);
   fclose(stdin);
   stdin = fdopen(savedstdin, "r");

   // run the simulation
   simulateBank();
}

/*
 In a loop, take input from the standard console until 'Q' or 'q' is entered.

 Each input should have the following syntax:

 {Q | ST | BO | RE] <customer number>  {<account funds> ...}}

 e.g. (for 3 accounts and with at least 2 customers):

 ST
 BO 1 3 2 1
 RE 1 1 0 1
 Q

 */
void simulateBank()
{
   // now loop reading requests to withdraw or deposit funds
   int request[numOfAccounts];
   char *inp = calloc(MAX_NUM_IN_LINE, sizeof(int));
   while (fgets(inp, MAX_NUM_IN_LINE, stdin) != 0)
   {
      if (strlen(inp) == 0)
         continue;

      // need a copy, since "line" will be used for tokenizing, so
      // it will change until it gets NULL; we would nnot be able to re-use it
      char *line = strdup(inp);

      // get transaction type - borrow (BO) or repay (RE) or ST (status)
      line[strlen(line) - 1] = '\0';
      char *trans = strsep(&line, " ,\t");
      strToUpper(&trans); // so the case does not matter

      printf("\nREQUEST: %s", trans);
      if (trans[0] == 'Q')
      {
         displayBankState();
         exit(1);
      }
      else if (strcmp(trans, "ST") == 0)
         displayBankState();
      else
      {
         if ((strcmp(trans, "BO") != 0) && (strcmp(trans, "RE") != 0))
         {
            printf("\nExpected input: Q | ST | [BO | RE] <customer number> <resource #1> <#2> <#3> ...\n");
            continue;
         }

         // get the customer number making the transaction
         int custNum = atoi(strsep(&line, " "));
         printf(" %d: ", custNum);

         // get the resources involved in the transaction
         for (int i = 0; i < numOfAccounts; i++)
            request[i] = atoi(strsep(&line, " ,\t"));

         display(request, numOfAccounts);

         // now check the transaction type
         if (strcmp(trans, "BO") == 0)
         {
            if (borrow(custNum, request) == TRUE)
               printf("\n*APPROVED*\n");
            else
               printf("\n*DENIED*\n");
         }
         else if (strcmp(trans, "RE") == 0)
         {
            if (repay(custNum, request) == TRUE)
               printf("\n*APPROVED*\n");
            else
               printf("\n*DENIED*\n");
         }
      }
   }
}

/*
 Read the state of the bank from a file.

 The file format is as follows:

 <num of customers> <num of accounts>
 <initial state of accounts>
 <max needs for each customer>

 e.g.,

 5 3
 15 10 5
 7,5,3
 3,2,2
 9,0,2
 2,2,2
 4,3,3

 Any of  ", \n\t" is a valid separator

 */
void loadBankState()
{
   // now get the customers and accounts
   int in[2]; // consume the line
   readLine(in);
   numOfCustomers = in[0];
   numOfAccounts = in[1];

   // the initial state of the funds
   int accountState[numOfAccounts];
   readLine(accountState);

   // create the bank
   initBank(accountState, numOfCustomers, numOfAccounts);

   int *maxDemand[numOfCustomers];

   // read initial values for maximum array
   int i;
   for (i = 0; i < numOfCustomers; i++)
   {
      maxDemand[i] = calloc(numOfAccounts, sizeof(int));
      readLine(maxDemand[i]);

      addBankCustomer(i, maxDemand[i]);
   }
}

/*
 Read a line of values separated by a set of delimeters from a file into an array
 */
void readLine(int array[])
{
   char *line = calloc(MAX_NUM_IN_LINE, sizeof(int));
   fgets(line, MAX_NUM_IN_LINE, stdin);
   char *tok;
   int i = 0;
   while ((tok = strsep(&line, ", \n\t")) != NULL)
      if (strlen(tok) > 0)
         array[i++] = atoi(tok);
}

/*
 Transcode the string to upper case
 */
void strToUpper(char **s)
{
   char *c;
   for(c = *s; *c ; c++)
      if (isascii(*c) && islower(*c))
         *c = toupper(*c);
}
