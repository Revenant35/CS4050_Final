#include <stdlib.h>
#include <stdbool.h>
#define MAX_BALANCE (1000000000000)
#define MIN_BALANCE (0)

// https://leetcode.com/problems/simple-bank-system/

typedef struct {
    long long * balance;
    int balanceSize;
} Bank;


Bank* bankCreate(long long* balance, int balanceSize) {
    Bank *obj = malloc(sizeof(Bank));

    if(!obj){
        return NULL;
    }

    obj->balanceSize = balanceSize;
    obj->balance = malloc(sizeof(long long) * balanceSize);

    if(!obj->balance){
        free(obj);
        return NULL;
    }

    for(int i = 0; i < balanceSize; i++){
        obj->balance[i] = balance[i];
    }

    return obj;

}

bool bankTransfer(Bank* obj, int account1, int account2, long long money) {
    if(account1 > obj->balanceSize || obj->balance[account1-1] - money < MIN_BALANCE) {
        return false;
    }
    if(account2 > obj->balanceSize) {
        return false;
    }

    obj->balance[account1-1] -= money;
    obj->balance[account2-1] += money;

    return true;
}

bool bankDeposit(Bank* obj, int account, long long money) {
    if(account > obj->balanceSize) {
        return false;
    }

    obj->balance[account-1] += money;

    return true;
}

bool bankWithdraw(Bank* obj, int account, long long money) {
    if(account > obj->balanceSize || obj->balance[account-1] - money < MIN_BALANCE) {
        return false;
    }

    obj->balance[account-1] -= money;

    return true;
}

void bankFree(Bank* obj) {
    free(obj->balance);
    free(obj);
}

/**
 * Your Bank struct will be instantiated and called as such:
 * Bank* obj = bankCreate(balance, balanceSize);
 * bool param_1 = bankTransfer(obj, account1, account2, money);
 
 * bool param_2 = bankDeposit(obj, account, money);
 
 * bool param_3 = bankWithdraw(obj, account, money);
 
 * bankFree(obj);
*/