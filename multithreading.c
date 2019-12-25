#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>
/************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer. My personalised data set is included in the
  code.

  TO  Compile:
    cc -o multithreading multithreading.c -lcrypt
To run:

    ./multithreading > results1.txt

******************************************************************************/
int n_passwords = 4;

char *encrypted_passwords[] = {
"$6$KB$eOk5f/THD7xQr6vKniSca/DdqY.m.gCg6Z.4zNWqD7V4yjkDuwCm2v5raQsqMcDEg344dywrZiRLhY65j4.Wg0",
"$6$KB$8X.3iBYPJ2h9z6w4pyfSxAaDTzQ2d9EvBX3tFiumB/vRZe/dX3hCUZtKd8ODAC/rYJN6YR9VzCTSDouhizU5k0",
"$6$KB$4nK6AiN8cb9rFzgjpJ1AxhQaBm0KMwBrmqtALfde6qVJzCR1SqIfeJCCepWjStZHYnkXLf4KFuvpw/Psf2c/y0",
"$6$KB$ZqbtoRA1d3cqX9Jj5guigg/vIbZyfH5qPUQ6hMdPDKS0Wb81FcaLZl9x8NK9qKzKQHfu6fm1ZX8ht6nyfy9/u."
};


/**
 Required by lack of standard function in C.  
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the
 start of the line. 

void crack(char *encrypted_passwords){
  pthread_t t1,t2;

  void *kernel_function_1();
  void *kernel_function_2();

  pthread_create(&t1, NULL, kernel_function_1, (void *)encrypted_passwords);
  pthread_create(&t2, NULL, kernel_function_2, (void *)encrypted_passwords);
 
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
}

void *kernel_function_1(char *salt_and_encrypted){
  int s, u, n;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(s='A'; s<='M'; s++){
    for(u='A'; u<='Z'; u++){
      for(n=0; n<=99; n++){
        sprintf(plain, "%c%c%02d", s, u, n);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}

void *kernel_function_2(char *salt_and_encrypted){
  int s, u, n;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(s='N'; s<='Z'; s++){
    for(u='A'; u<='Z'; u++){
      for(n=0; n<=99; n++){
        sprintf(plain, "%c%c%02d", s, u, n);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}


int time_difference(struct timespec *start,
                    struct timespec *finish,
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec;
  long long int dn =  finish->tv_nsec - start->tv_nsec;

  if(dn < 0 ) {
    ds--;
    dn += 1000000000;
  }
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}



int main(int argc, char *argv[]){
  int i;
 
 struct timespec start, finish;  
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  for(i=0;i<n_passwords;i<i++) {
    crack(encrypted_passwords[i]);
  }
 
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
                                         (time_elapsed/1.0e9));
  return 0;
}
