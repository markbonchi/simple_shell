#include "main.h"

/**
 * _strcat - concatenates two strings
 */

char *_strcat(char *dest, const char *src)
{
	int i, j;

	i = 0;
	while(dest[i] != '\0')
		i++;

	for (j = 0; src[j] != '\0'; j++)
		dest[i++] = src[j];

	dest[i] = '\0';
	return (dest);
}

/**
 * _strcpy - copies the string pointed to by src
 */

char *_strcpy(char *dest, char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - compares two strings
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	
	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}

/**
 * _strchr - locates a char in string
 */

char *_strchr(char *s, char c)
{
	unsigned int i;

	for (i = 0; s[i] != '\0'; i++)
		if (s[i] == c)
			return (s[i]);
	if (s[i] == c)
		return (s[i]);
	return ('\0');
}

/**
 * _strspn - gets the length of a prefix substring
 */

int _strspn(char *s, char *accept)
{
	int i, j, bool;

	for (i = 0; s[i] != '\0'; i++)
	{
		bool = 1;
		for (j = 0; accept[j] = '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}

/**
 * _strdup - duplicates a string
 */

char *_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, len + 1);
	return (new);
}

/**
 * _strlen - returns the lenght of a string
 */

int _strlen(const char *s)
{
	int len = 0;

	while(s[len] != '\0')
		len++;
	return (len);
}

/**
 * cmp_char -compares chars of a string
 */

int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}

	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - splits a tring by some delimiter
 */

char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; /*stores first address*/
		i = _strlen(str);
		str_end = &str[i]; /*stores last address*/
	}

	str_start = splitted;
	if (str_start == str_end) /*reaches end*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*breaking loop finding the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;

		/*replacing delimiter for a null char*/
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*str != delim*/
			bool = 1;
	}
	if (bool == 0) /*str == delim*/
		return (NULL);
	return (str_start);
}

/**
 * _isdigit - defines if string passed is a number
 */

int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
		if (s[i] < 48 || s[i] > 57)
			return (0);

	return (1);
}

/**
 * rev_string - reverses a string
 */

void rev_string(char *s)
{
	int count, i, j;
	char *str, temp;

	count = _strlen(s);
	str = s;

	for (i = 0; i < count - 1; i++)
		for (j = i + 1; j > 0; j--)
		{
			temp = str[j];
			str[j] = str[j - 1];
			str[j - 1] = temp;
		}
}


