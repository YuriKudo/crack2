#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *crack =md5(plaintext, strlen(plaintext));
    // Open the hash file
    FILE *hashFile = fopen(hashFilename, "r");
    if (!hashFile)
    {
        printf("Cant open the file for reading\n");
        exit(1);
    }
    // Loop through the hash file, one line at a time.
    char hashTxt[HASH_LEN];
    char word[100];
    while (fgets(hashTxt, 33, hashFile))
    {
        char *newLine =strchr(hashTxt, '\n');
        if(newLine) *newLine ='\0';
    
        // Attempt to match the hash from the file to the
        // hash of the plaintext.
        // If there is a match, you'll return the hash.
        // If not, return NULL.
        if (strcmp(crack, hashTxt)==0)
        {
            printf("%s %s\n", hashTxt, plaintext);
            free(crack);
            fclose(hashFile);
            return strdup(hashTxt);
        }
        
       

        // Before returning, do any needed cleanup:
        //   Close files?
        //   Free memory?

        // Modify this line so it returns the hash
        // that was found, or NULL if not found.
    }
    free(crack);
    fclose(hashFile);
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // These two lines exist for testing. When you have
    // tryWord working, it should display the hash for "hello",
    // which is 5d41402abc4b2a76b9719d911017c592.
    // Then you can remove these two lines and complete the rest
    // of the main function below.
    //char *found = tryWord("hello", "hashes00.txt");
    //printf("%s %s\n", found, "hello");


    // Open the dictionary file for reading.
    
    FILE *d = fopen(argv[2], "r"); 
    if (!d)
    {
        printf("Can't open %s for reading\n", argv[2]);
        exit(1);
    }
    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    // If we got a match, display the hash and the word. For example:
    //   5d41402abc4b2a76b9719d911017c592 hello
    char plaintext[100];
    int counter =0;
    while(fgets(plaintext, 100, d))
    {
        plaintext[strcspn(plaintext, "\n")] = '\0';
        char *found = tryWord(plaintext, argv[1]);
        if(found)
        {
            counter++;
        }
    }
    // Close the dictionary file.
    // Display the number of hashes that were cracked.
    // Free up any malloc'd memory?
    fclose(d);
    printf("%d hashes cracked!\n", counter);
    return 0;
}

