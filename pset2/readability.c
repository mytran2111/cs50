# include <cs50.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>

bool check_duplicate(string s)
{
    bool alpha[256];
    memset(alpha, 0, sizeof(alpha));
    // printf("validating string %s with length %i\n", s, (int)strlen(s));
    for ( int i = 0, n = strlen(s); i < n; i++)
    {
        // ! is not
        if (!alpha[(int) s[i]])
        {
            alpha[ (int) s[i]] = 1;
        }
        else
        {
            return 1;
            // There is at least one duplicate
        }

    }
    return 0;
}

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    // Message when user does not type in KEY
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha( argv[1][i]) == 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

    }
    // TODO: Check the duplicate of the key and display message "Key must not contain repeated characters"
    if (check_duplicate(argv[1]))
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    string text = get_string("plaintext: ");
    char cipher[256];
    // set ve gia tri mac dinh
    memset(cipher, 0, sizeof(cipher));
    int index;
    for (int i = 0, n = strlen(text); i < n; i++)
    {

        if ( isalpha(text[i]) == 0)
        {
            cipher[i] = text[i];
        }
        if ( islower(text[i]) != 0)
        {
            index = text[i] - 'a';
            if (islower(argv[1][index]) != 0 )
            {
                cipher[i] = argv[1][index];
            }
            else
            {
                cipher[i] = argv[1][index] + 32;
            }
        }
        else if (isupper(text[i]) != 0)
        {
            index = text[i] - 'A';
            if (isupper(argv[1][index]) != 0 )
            {
                cipher[i] = argv[1][index];
            }
            else
            {
                cipher[i] = argv[1][index] - 32;
            }
        }
    }
    printf("ciphertext: %s\n", cipher);

}
