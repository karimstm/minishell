#include <stdio.h>
#include <stdlib.h>

	char *
__findenv(const char *name, int *offset)
{
	extern char **environ;
	int len, i;
	const char *np;
	char **p, *cp;
	if (name == NULL || environ == NULL)
		return (NULL);
	for (np = name; *np && *np != '='; ++np)
		;
	len = np - name;
	for (p = environ; (cp = *p) != NULL; ++p) {
		for (np = name, i = len; i && *cp; i--)
			if (*cp++ != *np++)
				break;
		if (i == 0 && *cp++ == '=') {
			*offset = p - environ;
			return (cp);
		}
	}
	return (NULL);
}

char *ft_getenv(const char *name)
{
	int offset;
	return (__findenv(name, &offset));
}

int main(int argc, char *argv[])
{
	int count = 0;
	printf("%s", ft_getenv("PATH"));
	return 0;
}
