#######WRAPPER
#modifications before and after a fxn call without affecting fxn itself...
import random

def d1(f):
    r = f()
    return r+r

def doubler(f):
    def inner():
        r = f()
        return r+r
    return inner

#take get_name and put it in the doubler fxn, and put it back --> sending back a fxn to replace the original
#same as get_name = doubler(get_name) after the get_name definition


# If there is more than one macro, then it will "wrap" the fxn in order
#ex:
#   @Capital
#   @Doubler
# captial, then doubler would be executed

@doubler
def get_name():
    names =['tom','harry','dana','sue','sarah','horatio','bob','ralph']
    return random.choice(names)

def lnames():
    s = [get_name() for x in range(10)]
    return s

def argexample (*arg, **kwargs):
    #* means to collect other arguments as a tuple
    # ** means to gather all keyword args (ex: name="hello") and put in dictionary
    #KEYWORD ARGS MUST ALWAYS BE AFTER REGULAR ARGS
    print len(args)
    print args
    print kwargs


def argprint1(f):
    def inner(*args, **kwargs):
        print args
        print f.__name__
        r = f(*args, **kwargs)
        #do validation/logging stuff here
        return r
    return inner

def f1(a,b):
    print a,b

#IN PYTHON: __ means thunder name?
#doubler(get_name) returns a fxn.....
#get_name = doubler(get_name)
#get_name() will now be transformed into a new fxn that prints out names twice
#and LNAME WILL BE TRANSFORMED INTO PRINTING OUT DOUBLE AS WELL

#f1.__name__ ==> inner from outside (because you're calling f1 = arprint1(f1) essentially...)
#f1.__name__ ==> f1 from inside (has not been assigned yet)

#This is a problem--all of our __name__ will be the same if we still have the same wrapper!

#@wraps(f) takes fxn name and assigns __name__ to the original name, fixing this problem.    
