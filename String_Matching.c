//A brute force approach to string matching

#include <stdio.h>
#include <string.h>

int main() {
    char s1[1000];
    char s2[100];

    printf("Enter the s1: ");
    fgets(s1, sizeof(s1), stdin);
    s1[strcspn(s1, "\n")] = '\0'; // Removing newline character

    printf("Enter the s2: ");
    scanf("%s", s2);

    int s1_length = strlen(s1);
    int s2_length = strlen(s2);
    int found = 0; 
    int position = -1; 

    for (int i = 0; i <= s1_length - s2_length; i++) {
        int j;
        for (j = 0; j < s2_length; j++) {
            if (s1[i + j] != s2[j])
                break;
        }
        if (j == s2_length) {
            found = 1;
            position = i;
            break;
        }
    }

    if (found) {
        printf("s2 found at position: %d\n", position);
    } else {
        printf("s2 not found in the s1.\n");
    }

    return 0;
}
