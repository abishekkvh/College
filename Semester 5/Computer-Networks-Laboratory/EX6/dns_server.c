#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 6001
#define MAXLINE 1024
#define MAX_RECORDS 100

struct DNSRecord
{
	char		domain[100];
	char		ip[INET_ADDRSTRLEN];
};

int
main()
{
	int		sockfd;
	char		buffer[MAXLINE];

	struct sockaddr_in servaddr, cliaddr;

	struct DNSRecord table[MAX_RECORDS];
	int		recordCount = 0;

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	if (bind(sockfd,
		 (const struct sockaddr *)&servaddr,
		 sizeof(servaddr)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	printf("DNS Server running on port %d...\n\n", PORT);

	socklen_t	len = sizeof(cliaddr);

	while (1)
	{
		int		n;
		int		found = 0;

		memset(buffer, 0, MAXLINE);

		n = recvfrom(sockfd,
			     buffer,
			     MAXLINE - 1,
			     0,
			     (struct sockaddr *)&cliaddr,
			     &len);

		if (n < 0)
		{
			perror("recvfrom failed");
			continue;
		}

		buffer[n] = '\0';

		if (strcmp(buffer, "exit") == 0)
		{
			printf("Client disconnected.\n");
			break;
		}

		printf("Client requested: %s\n", buffer);

		for (int i = 0; i < recordCount; i++)
		{
			if (strcmp(table[i].domain, buffer) == 0)
			{
				found = 1;

				printf("Found in local DNS table.\n");
				printf("%s -> %s\n\n",
				       table[i].domain,
				       table[i].ip);

				sendto(sockfd,
				       table[i].ip,
				       strlen(table[i].ip),
				       0,
				       (const struct sockaddr *)&cliaddr,
				       len);

				break;
			}
		}

		if (!found)
		{
			struct addrinfo	hints;
			struct addrinfo *result;

			memset(&hints, 0, sizeof(hints));

			hints.ai_family = AF_INET;
			hints.ai_socktype = SOCK_DGRAM;

			int		status = getaddrinfo(buffer, NULL, &hints, &result);

			if (status != 0)
			{
				printf("Unable to resolve domain: %s\n\n", buffer);

				char		errorMessage[] = "Domain not found";

				sendto(sockfd,
				       errorMessage,
				       strlen(errorMessage),
				       0,
				       (const struct sockaddr *)&cliaddr,
				       len);

				continue;
			}

			struct sockaddr_in *address;
			char		ip[INET_ADDRSTRLEN];

			address = (struct sockaddr_in *)result->ai_addr;

			inet_ntop(AF_INET,
				  &(address->sin_addr),
				  ip,
				  sizeof(ip));

			printf("Resolved using DNS.\n");
			printf("%s -> %s\n", buffer, ip);

			if (recordCount < MAX_RECORDS)
			{
				strcpy(table[recordCount].domain, buffer);
				strcpy(table[recordCount].ip, ip);

				recordCount++;

				printf("Stored in local DNS table.\n\n");
			}

			sendto(sockfd,
			       ip,
			       strlen(ip),
			       0,
			       (const struct sockaddr *)&cliaddr,
			       len);

			freeaddrinfo(result);
		}
	}

	close(sockfd);

	return 0;
}