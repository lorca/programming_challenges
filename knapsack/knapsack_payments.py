#
# toy program to show how to run knapsack 
# for a made-up payments problem.
#
# Steve A <iradik@gmail.com>
#

from math import ceil

#
# dynamic 1-0 knapsack solution
#
# time and space complexity is O(nW)
#
# returns the indexes for items that are put into the sack.
#
def knapsack(weights,values,limit):
    m={}
    for i in range(0,len(weights)+1):
        m[i]={}
        for w in range(0,limit+1):
           if i == 0 or w == 0: m[i][w] = 0
           elif weights[i-1] > w: m[i][w] = m[i-1][w]
           else: m[i][w] = max(m[i-1][w], m[i-1][w-weights[i-1]]+values[i-1])
    k=limit
    item_indicies=[]
    for i in range(len(weights),0,-1):
        if m[i][k] != m[i-1][k]:
            k=k-weights[i-1]
            item_indicies.append(i-1)
    return item_indicies

#
# Run knapsack on accounts that need to be settled.
#
# setting is_round=True gives a 100x boost
# by rounding to the nearest dollar when running knapsack.
#
def knapsack_settlements(accounts,limit,is_round=False):
    weights=[account[1] for account in accounts]
    values=[account[3] for account in accounts]
    if is_round:
        limit=int(ceil(limit/100))
        weights = [int(ceil(w/100)) for w in weights]
    settled_indicies = knapsack(weights,values,limit)
    settled_accounts = [accounts[i] for i in settled_indicies]
    for account in settled_accounts: 
        print account


max_allowed_settlement_in_cents = 64500

#account_id, balance, bank, rebate
accounts = [
    [1, 15300, "BofA",   232],
    [2,  5300,  "WFC",    73],
    [3, 19100, "Chase",  201],
    [4,  6605, "M&T",     50],
    [5, 23999, "BB&T",   141],
    [6, 13755, "First National", 79],
    [7, 14578, "PNC",     48],
    [8, 24943, "HSBC",    38],
    [9,  4301, "Bank of the West", 131]]

knapsack_settlements(accounts, max_allowed_settlement_in_cents, is_round=False)

