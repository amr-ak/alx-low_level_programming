#include "main.h"
#include <stdlib.h>

/**
 * string_nconcat - concatenates two strings
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to copy from s2
 * Return: pointer to the concatenated string
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
    char *concat;
    unsigned int i, j, len1, len2;

    /* check for NULL strings */
    if (s1 == NULL)
        s1 = "";
    if (s2 == NULL)
        s2 = "";

    /* calculate the lengths of the strings */
    for (len1 = 0; s1[len1]; len1++)
        ;
    for (len2 = 0; s2[len2]; len2++)
        ;

    /* allocate memory for the concatenated string */
    if (n >= len2) /* use the entire s2 */
        concat = malloc(sizeof(char) * (len1 + len2 + 1));
    else /* use only n bytes of s2 */
        concat = malloc(sizeof(char) * (len1 + n + 1));

    if (concat == NULL) /* check for memory allocation failure */
        return (NULL);

    /* copy the strings to the concatenated string */
    for (i = 0; i < len1; i++) /* copy s1 */
        concat[i] = s1[i];
    for (j = 0; j < n && s2[j]; j++) /* copy n bytes of s2 */
        concat[i + j] = s2[j];
    concat[i + j] = '\0'; /* add null terminator */

    return (concat); /* return the pointer to the concatenated string */
}
