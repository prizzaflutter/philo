
int parcing(char **argv)
{
	int i = 1; 
	while (argv[i])
	{
		if (argv[i][0] == "\0")
			return (-1);
	}
}

int main (int argc, char **argv)
{  
	if (argc != 4 && argc != 5)
		return (printf("invalid args number\n", 0));
}
