//Angela Lin
//Work 1: If you like it then you should've put a string on it
//Systems
//Period 4

#include <stdio.h>
#include <stdlib.h>

//~~~~functions to be used in this file declared before main~~~~//
int mystrlen(char *s);
char* mystrcpy(char *dest, char *source);
char* mysterncpy(char *dest, char *source, int n);
char* mysterncat(char *s1, char *s2, int n);
char* mystercat(char *s1, char *s2);
int mystrcmp(char *s1, char *s2);
char* mystrchr(char *s, char c);
char* mystrstr(char *s, char* key);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~end~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~main fxn: fxn called when running a.out~~~~~~~~~~//
int main(){
  char s[6]="Hello";
  char d[4]="Cat";
  //Printing strings:
  printf("Now testing printing strings...\n");
  printf("String s is: %s\n", s);
  printf("String d is: %s\n", d);

  //Testing mystrlen:
  printf("\n\nNow testing mystrlen:\n");
  printf("The expected length of string s: 5\n");
  printf("The length of the string as returned by mystrlen: %d\n",mystrlen(s));
  if (mystrlen(s)==5)
    printf("Success!\n");
  printf("The expected length of string d: 3\n");
  printf("The length of the string as returned by mystrlen: %d\n",mystrlen(d));
  if (mystrlen(d)==3)
    printf("Success!\n");

  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
 
 //Testing mystrcpy:
  char empty[20] = "";
  char copy[10]="Test Copy";
  printf("\nNow testing mystrcopy...\n");
  printf("Copying string copy into empty:\n");
  printf("Before copying...\n");
  printf("String Empty: %s\n",empty);
  printf("Length of empty: %d\n", mystrlen(empty));
  printf("String copy: %s\n", copy);
  printf("Length of copy: %d\n", mystrlen(copy));
  
  mystrcpy(empty,copy);
  
  printf("\nAfter testing mystrcopy...\n");
  printf("String Empty should now be: Test Copy\n");
  printf("String Empty: %s\n",empty);
  printf("Length of Empty: %d\n", mystrlen(empty));
  printf("String copy: %s\n", copy);
  printf("Length of copy: %d\n", mystrlen(copy));
  if (mystrlen(empty)==9)
    printf("Yippee! This case works.\n");
  
  //Testing mystrcpy again:
  printf("\nStill testing mystrcopy:\n");
  
  char cpy1[100]="Hello!!!!!!";
  char cpy2[9]="cake";
  printf("Copying string cpy2 into cpy1:\n");
  printf("Before copying...\n");
  printf("String cpy1 is: %s\n", cpy1);
  printf("Length of cpy1: %d\n", mystrlen(cpy1));
  printf("String cpy2 is: %s\n", cpy2);  
  printf("Length of cpy2: %d\n", mystrlen(cpy2));

  mystrcpy(cpy1, cpy2);

  printf("\nAfter testing mystrcopy...\n");
  printf("String cpy1: %s\n",cpy1);
  printf("String cpy1 should now be: cakeo!!!!!!\n");
  printf("Length of cpy1: %d\n", mystrlen(cpy1));
  printf("String cpy2: %s\n", cpy2);
  printf("Length of cpy2: %d\n", mystrlen(cpy2));

  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
 
 //Testing mysterncpy:
  char emptyr[20] = "";
  char copyr[10]="Test Copy";
  printf("\nNow testing mysterncopy...\n");
  printf("Copying string copyr into emptyr:\n");
  printf("Before copying...\n");
  printf("String emptyr: %s\n",emptyr);
  printf("Length of emptyr: %d\n", mystrlen(emptyr));
  printf("String copyr: %s\n", copyr);
  printf("Length of copyr: %d\n", mystrlen(copyr));
  
  mysterncpy(emptyr,copyr, 4);
  
  printf("\nAfter testing mysterncopy with n = 4:\n");
  printf("String emptyr should now be: Test\n");
  printf("String emptyr: %s\n",emptyr);
  printf("Length of empty: %d\n", mystrlen(emptyr));
  printf("String copyr: %s\n", copyr);
  printf("Length of copyr: %d\n", mystrlen(copyr));
  if (mystrlen(emptyr)==4)
    printf("Yippee! This case works.\n");
  
  //Testing mysterncpy again:
  printf("\nStill testing mysterncopy:\n");
  
  char cpy1r[100]="Hello!!!!!!";
  char cpy2r[9]="cake";
  printf("Copying string cpy2r into cpy1r:\n");
  printf("Before copying...\n");
  printf("String cpy1r is: %s\n", cpy1r);
  printf("Length of cpy1r: %d\n", mystrlen(cpy1r));
  printf("String cpy2r is: %s\n", cpy2r);  
  printf("Length of cpy2r: %d\n", mystrlen(cpy2r));

  mysterncpy(cpy1r, cpy2r, 1);

  printf("\nAfter testing mysterncopy...\n");
  printf("String cpy1r: %s\n",cpy1r);
  printf("String cpy1r should now be: cello!!!!!!\n");
  printf("Length of cpy1r: %d\n", mystrlen(cpy1r));
  printf("String cpy2r: %s\n", cpy2r);
  printf("Length of cpy2r: %d\n", mystrlen(cpy2r));
 if (mystrlen(cpy1r)==11)
    printf("Yippee! This case works.\n");
  
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");  

  //Testing mysterncat:
  char cat1[100]="My stern";
  char cat2[100]=" kittycat";
  printf("Testing mysterncat:\n");
  printf("Concatenating cat2 to cat1:\n");
  printf("Before concatenating...\n");
  printf("String cat1 is: %s\n", cat1);
  printf("Length of cat1: %d\n", mystrlen(cat1));
  printf("String cat2 is: %s\n", cat2);  
  printf("Length of cat2: %d\n", mystrlen(cat2));

  mysterncat(cat1, cat2, 6);

  printf("\nAfter cat-ing 6 char:\n");
  printf("String cat1: %s\n",cat1);
  printf("String cat1 should now be: My stern kitty\n");
  printf("Length of cat1: %d\n", mystrlen(cat1));
  printf("String cat2: %s\n", cat2);
  printf("Length of cat2: %d\n", mystrlen(cat2));
 if (mystrlen(cat1)==14)
    printf("Yippee! This case works.\n\n");
 /////////////////////////////////////////////////////////////
  printf("Testing mysterncat again (null case):\n");
  char cat3[100]="My stern";
  char cat4[100]=" kittycat";
  printf("Testing mysterncat:\n");
  printf("Concatenating cat4 to cat3:\n");
  printf("Before concatenating...\n");
  printf("String cat3 is: %s\n", cat3);
  printf("Length of cat3: %d\n", mystrlen(cat3));
  printf("String cat4 is: %s\n", cat4);  
  printf("Length of cat4: %d\n", mystrlen(cat4));

  mysterncat(cat3, cat4, 100);//should trigger null case

  printf("\nAfter cat-ing 100 (!) char:\n");
  printf("String cat3: %s\n",cat3);
  printf("String cat3 should now be: My stern kittycat\n");
  printf("Length of cat3: %d\n", mystrlen(cat3));
  printf("String cat4: %s\n", cat4);
  printf("Length of cat4: %d\n", mystrlen(cat4));
 if (mystrlen(cat3)==17)
    printf("Yippee! This case works.\n");

 printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");  
 //testing mystercat:
  char cat1r[100]="My ster";
  char cat2r[100]=" kittycat";
  printf("Testing mystercat:\n");
  printf("Concatenating cat2r to cat1r:\n");
  printf("Before concatenating...\n");
  printf("String cat1r is: %s\n", cat1r);
  printf("Length of cat1r: %d\n", mystrlen(cat1r));
  printf("String cat2r is: %s\n", cat2r);  
  printf("Length of cat2r: %d\n", mystrlen(cat2r));

  mystercat(cat1r, cat2r);

  printf("\nAfter cat-ing:\n");
  printf("String cat1r: %s\n",cat1r);
  printf("String cat1r should now be: My ster kittycat\n");
  printf("Length of catr1: %d\n", mystrlen(cat1r));
  printf("String cat2r: %s\n", cat2r);
  printf("Length of cat2r: %d\n", mystrlen(cat2r));
 if (mystrlen(cat1r)==16)
    printf("Yippee! This case works.\n\n");
 
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");  

  //testing mystrcmp:
  char cmp1[100]="hello";
  char cmp2[100]="hello";

  printf("Testing mystrcmp (the equal case):\n");
  printf("String cmp1 is: %s\n", cmp1);
  printf("Length of cat3: %d\n", mystrlen(cmp1));
  printf("String cmp2 is: %s\n", cmp2);  
  printf("Length of cmp2: %d\n", mystrlen(cmp2));
  printf("Comparing cmp1 and cmp2 should yield a 0.\n");
  printf("mystrcmp returns: %d\n", mystrcmp(cmp1, cmp2));
  if (mystrcmp(cmp1,cmp2) == 0)
    printf("Success!\n");
  ///////////////////////////////////////////////////////////
  char cmp3[100]="apple";
  char cmp4[100]="hello";

  printf("\nTesting mystrcmp (the not equal but same length case):\n");
  printf("String cmp3 is: %s\n", cmp3);
  printf("Length of cat3: %d\n", mystrlen(cmp3));
  printf("String cmp4 is: %s\n", cmp4);  
  printf("Length of cmp4: %d\n", mystrlen(cmp4));
  printf("Comparing cmp3 and cmp4 should yield a negative value.\n");
  printf("mystrcmp returns: %d\n", mystrcmp(cmp3, cmp4));
  if (mystrcmp(cmp3,cmp4) < 0)
    printf("Success!\n");
  ///////////////////////////////////////////////////////////
  char cmp5[100]="h";
  char cmp6[100]="hello";

  printf("\nTesting mystrcmp (the not equal length case):\n");
  printf("String cmp5 is: %s\n", cmp5);
  printf("Length of cat5: %d\n", mystrlen(cmp5));
  printf("String cmp6 is: %s\n", cmp6);  
  printf("Length of cmp6: %d\n", mystrlen(cmp6));
  printf("Comparing cmp5 and cmp6 should yield a negative value.\n");
  printf("mystrcmp returns: %d\n", mystrcmp(cmp5, cmp6));
  if (mystrcmp(cmp5,cmp6) < 0)
    printf("Success!\n");

  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");  
  //Testing mystrchr:
  char strchar1[100]="abcdef";
  printf("Testing mystrchar:\n");
  printf("strchar1 is:%s\n", strchar1);
  printf("The memory allocation of strchar1 begins at:%d\n", strchar1);
  //finding a
  printf("Finding 'a' should return the value of strchar:\n");
  printf("mystrchr(strchar1,'a'):%d\n",mystrchr(strchar1,'a'));
  if (mystrchr(strchar1,'a')==strchar1)
    printf("Yep! It does!\n");
  //finding f
  printf("Finding 'f' should return the value of strchar +/- 5:\n"); 
  printf("mystrchr(strchar1,'f'):%d\n",mystrchr(strchar1,'f'));
  if (mystrchr(strchar1, 'f')==strchar1+5 ||mystrchr(strchar1, 'f')==strchar1-5)
    printf("Yep! It does! :)\n");mystrchr(strchar1,'z');
  //finding z
  printf("Finding 'z' should return 0:\n");
  printf("mystrchr(strchar1,'z'):%d\n",mystrchr(strchar1,'z'));
  if (mystrchr(strchar1,'z')==0)
    printf("Yahoo!!!!\n");

  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");  
  //Testing mystrstr:
  char strstr1[100] = "woopdy woop!";
 
  printf("Testing mystrstr:\n");
  printf("strstr1 is:%s\n", strstr1);
  printf("The memory allocation of strstr1 begins at:%d\n", strstr1);
 //finding "woop"
  printf("Finding 'woop' should return the value of strstr1:\n");
  printf("mystrstr(strstr1,'woop'):%d\n",mystrstr(strstr1,"woop"));
  if (mystrstr(strstr1,"woop")==strstr1)
    printf("Yep! It does!\n");
  
  printf("\nTesting mystrstr again:\n");
  printf("strstr1 is:%s\n", strstr1);
  printf("The memory allocation of strstr1 begins at:%d\n", strstr1);
 //finding "woop!"
  printf("Finding 'woop!' should return strstr1 +/- 7:\n");
  printf("mystrstr(strstr1,'woop!'):%d\n",mystrstr(strstr1,"woop!"));
  if ((mystrstr(strstr1,"woop!")==strstr1+7) || (mystrstr(strstr1,"woop!")==strstr1-7))
    printf("Yep! It does!\n");
    
  printf("\nTesting mystrstr (does not exist case):\n");
  printf("strstr1 is:%s\n", strstr1);
  printf("The memory allocation of strstr1 begins at:%d\n", strstr1);
 //finding "wood"
  printf("Finding 'wood' should return 0:\n");
  printf("mystrstr(strstr1,'wood'):%d\n",mystrstr(strstr1,"wood"));
  if (mystrstr(strstr1,"wood")==0)
    printf("Yep! It does!\n");
    
  
  return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~end main~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~~~~~~~~~Stringy fxns~~~~~~~~~~~~~~~~~~~~~~~~~~//
int mystrlen(char *s){
  int i = 0;
  while (s[i]){//0 is false; string terminates at 0
    i++;
  }
  return i;
}

char* mystrcpy(char *dest, char *source){
  int i = 0;
  while (source[i]){
    dest[i] = source[i];
    i++;
  }
  dest[i] = 0;
  return dest;
  }

char* mysterncpy(char *dest, char *source, int n){
  int i = 0;
  while (source[i] && i<n){
    dest[i] = source[i];
    i++;
  }
  return dest;
  }

char* mysterncat(char *s1, char *s2, int n){
  int i = 0;
  int len = mystrlen(s1);
  while (s2[i] && i<n){
    s1[len+i] = s2[i];
    i++;
  }
  s1[len+i] = 0;
  return s1;
}

char* mystercat(char *s1, char *s2){
  int i = 0;
  int len = mystrlen(s1);
  while (s2[i]){
    s1[len+i] = s2[i];
    i++;
  }
  s1[len+i] = 0;
  return s1;
}

int mystrcmp(char *s1, char *s2){
  int i = 0;
  while (s1[i] && s2[i]){
    //printf("s1[i]: %d, s2[i]: %d\n", s1[i],s2[i]);
    if (s1[i]!=s2[i])//not same char
      //printf("s1 is not equal to s2\n");
      return (s1[i]-s2[i]);
    i++;
  }
  return (mystrlen(s1)-mystrlen(s2));
}


char* mystrchr(char *s, char c){
  int i = 0;
  while (s[i]){
    if (s[i] == c)
      return s+i;
    i++;
  }
  return 0;
}

char* mystrstr(char *s, char* key){
  int i = 0;
  while (s[i]){//loops through the string
    if (s[i] == key[0]){
      int keyi = 0;
      while (s[i]== key[keyi] && key[keyi]){
	i++;
	keyi++;
      }
      if (keyi == mystrlen(key))
	return s+i-mystrlen(key);
    }
    i++;
  }
    return 0;
}
//~~~~~~~~~~~~~~~~~~end stringy fxns~~~~~~~~~~~~~~~~~~~~~~~//
