
# coding: utf-8

# In[6]:


from itertools import product
import hashlib
import _thread
guessedPassList = []


# In[7]:


def foo(characterset,length):
    yield from product(*([characterset] * length))


# In[8]:


def genGuesses(characterset,length):
    for i in range(length+1):
        for x in foo(characterset,i):
            guess = ''.join(x)
            guessedPassList.append(guess)


# In[9]:


def remDuplicates(duplicateList): 
    final_list = [] 
    for num in duplicateList: 
        if num not in final_list: 
            final_list.append(num) 
    return final_list


# In[10]:


genGuesses('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789',2) # sec arg is the length of password
guessedPassList.sort()
guessedPassList = remDuplicates(guessedPassList)
len(guessedPassList)


# In[13]:


password = 's'
PassHash = (hashlib.md5(password.encode())).hexdigest()
print (PassHash)


# In[14]:


for everyguess in guessedPassList:
    guessHash = (hashlib.md5(everyguess.encode())).hexdigest()
    if (guessHash == PassHash):
        print("Cracked Password is: ",everyguess)
        break

