#
# toy program to show how to run knapsack 
# for a made-up payments problem.
#
# Steven Alyari <iradik@gmail.com>
#

from array import array
from math import ceil

MAX_SETTLEMENT_AMOUNT_PER_DAY = 64500
ACCOUNTS = [
#account_id, balance, bank, rebate
#
[1, 15300, "BofA",   232],
[2,  5300,  "WFC",    73],
[3, 19100, "Chase",  201],
[4,  6605, "M&T",     50],
[5, 23999, "BB&T",   141],
[6, 13755, "First National", 79],
[7, 14578, "PNC",     48],
[8, 24943, "HSBC",    38],
[9,  4301, "Bank of the West", 131] ]

#
# dynamic 1-0 knapsack solution
#
# time and space complexity is O(nW)
#
# returns the indexes for items that are put into the sack.
#
def knapsack(W,V,limit):
    M={}
    for i in range(0,len(W)+1):
        M[i]={}
        for w in range(0,limit+1):
           if i == 0 or w == 0: M[i][w] = 0
           elif W[i-1] > w: M[i][w] = M[i-1][w]
           else: M[i][w] = max(M[i-1][w], M[i-1][w-W[i-1]]+V[i-1])
    k=limit
    I=[]
    for i in range(len(W),0,-1):
        if M[i][k] != M[i-1][k]:
            k=k-W[i-1]
            I.append(i-1)
    return I

#
# Run knapsack on accounts that need to be settled.
#
# setting is_round=True gives a 100x boost
# by rounding to the nearest dollar when running knapsack.
#
def knapsack_settlements(accounts,limit,is_round=False):
    W=[account[1] for account in accounts]
    V=[account[3] for account in accounts]
    if is_round:
        limit=int(ceil(limit/100))
        W = [int(ceil(w/100)) for w in W]
    I = knapsack(W,V,limit)
    settled_accounts = [accounts[i] for i in I]
    for account in settled_accounts:
        print account

knapsack_settlements(ACCOUNTS, MAX_SETTLEMENT_AMOUNT_PER_DAY, is_round=False)

