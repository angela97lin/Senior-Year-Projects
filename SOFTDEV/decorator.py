from functools import wraps

##DYNAMIC PROGRAMMING:
#Using memory, which is cheap, we can rewrite recursive fxns for father

#MEMOIZATION: like writing down a memo to quickly calculate things
#A nicer way to compute fib numbers using dynamic programming (yet, not entirely since recursive calls)

#As long as some unique key returns some unique output, it can be memoized
def memoize(f):
    t = {}
    @wraps(f)
    def inner(*args):
        if args in t:
                return t[args]
        else:
                t[args] = f(*args)
                return t[args]
    return inner

@memoize
def lcslength(s1, s2, i, j):
    #i and j are index in s1 and s2, respectively
    if i >= len(s1) or j>=len(s2):
        #no common substring left
        return 0
    elif s1[i] == s2[j]:
        return 1+lcslength(s1, s2, i+1, j+1)
    else:
        #do not match
        return max(lcslength(s1, s2, i+1, j),lcslength(s1,s2, i, j+1))

#going from left to right, if you removed other chars, what is the largest substring you could return that is found in both given strings?
    ##abc, xyb = 1
    ##abc, ayb = 2

import string, random

def make_string(n):
    return "".join(random.choice(string.ascii_uppercase+string.digits) for x in range(n))

@memoize
def fib2(x,t={}):
    if x in t:
        return t[x]
    elif x < 2:
        return 1
    else:
        t[x] = fib2(x-1,t) + fib2(x-2,t)
        return t[x]


# @decorate
# def hello(name)...
# is equivalent to hello = decorate(hello)

#so if you have @decorate("message")
#it becomes hello = decorate("message")(hello)
#which is quirky since the first part will be
#executed first
#hence, in decorate, we must have another decorator as a shell
#so that
#hello = dec_wtf("message")
