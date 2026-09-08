#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
	int		sock, connfd;
	struct sockaddr_in saddr, caddr;
	char		buf[1024];
	int		port;
	socklen_t	addr_len;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	port = atoi(argv[1]);

	if (port <= 0 || port > 65535)
	{
		fprintf(stderr, "Invalid port number: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	memset(&saddr, 0, sizeof(saddr));

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock,
		 (struct sockaddr *)&saddr,
		 sizeof(saddr)) < 0)
	{
		perror("bind failed");
		close(sock);
		exit(EXIT_FAILURE);
	}

	if (listen(sock, 5) < 0)
	{
		perror("listen failed");
		close(sock);
		exit(EXIT_FAILURE);
	}

	printf("TCP Chat Server listening on port %d...\n", port);
	printf("Waiting for clients...\n\n");

	int		cnum = 0;

	while (1)
	{
		addr_len = sizeof(caddr);

		connfd = accept(sock,
				(struct sockaddr *)&caddr,
				&addr_len);

		if (connfd < 0)
		{
			perror("accept failed");
			continue;
		}

		cnum++;

		printf("Client %d connected.\n", cnum);

		if (fork() == 0)
		{
			close(sock);

			char		message[1024];

			sprintf(message,
				"You are Client %d",
				cnum);

			send(connfd,
			     message,
			     strlen(message),
			     0);

			while (1)
			{

				int		n = recv(connfd,
							 buf,
							 1024 - 1,
							 0);

				if (n <= 0)
				{
					break;
				}

				buf[n] = '\0';

				buf[strcspn(buf, "\n")] = '\0';

				if (strcmp(buf, "quit") == 0 ||
				    strcmp(buf, "/quit") == 0)
				{
					break;
				}

				printf("Client %d: %s\n",
				       cnum,
				       buf);

				printf("You(Server): ");

				if (fgets(message,
					  1024,
					  stdin) == NULL)
				{
					strcpy(message, "quit");
				}

				message[strcspn(message, "\n")] = '\0';

				char		output[1024];

				sprintf(output,
					"You(Server): %s",
					message);

				send(connfd,
				     output,
				     strlen(output),
				     0);

				if (strcmp(message, "quit") == 0 ||
				    strcmp(message, "/quit") == 0)
				{
					break;
				}
			}

			printf("Client %d has left the chat.\n",
			       cnum);

			close(connfd);

			exit(0);
		}

		close(connfd);

		waitpid(-1, NULL, WNOHANG);
	}

	close(sock);

	return 0;
