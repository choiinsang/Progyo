void *thread_main(void *arg)
{
/*
	int i;
	for(i=0; i<10; i++)
	{
		printf("thread");
		fflush(stdout);
	}
	int result = system("/usr/bin/php /var/www/html/index.php");
	printf("%d", result);
	
	fflush(stdout);
*/
/*	
	FILE *fpipe;
	char *command = (char*)"/usr/bin/php /var/www/html/index.php";
	char line[256];
	
	if(!(fpipe = (FILE*)popen(command, "r")))
		return 0;
	
	while(fgets(line, sizeof(line), fpipe))
		printf("%s", line);
	
	pclose(fpipe);
	fflush(stdout);
*/

	printf("thread start \n");
	fflush(stdout);

	int sock, n;
	char haddr[128];
	struct sockaddr_in server_addr;
	
	sprintf(haddr, "%s", "127.0.0.1");
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		printf("socket error1 \n");
		fflush(stdout);
		return 0;
	}
	
	memset((char*)&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(haddr);
	server_addr.sin_port = htons(80);
	
	printf("connect \n");
	if(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
	{
		printf("socket error\n");
		fflush(stdout);
		return 0;
	}
	
	char buf[4096];
	int len;
	int retval;
	memset(buf, 0, sizeof(buf));
	
	sprintf(buf,
						"GET http://117.52.89.33/index.php HTTP/1.1\r\n" 
						"Connection: Keep-Alive\r\n" 
						"Host: localhost\r\n"
						"Accept: text/html\r\n"
						"\r\n");
	
	len = strlen(buf);
	
	printf("send \n");
	retval = send(sock, buf, len, 0);
	if(retval == -1)
	{
		printf("send error \n");
		fflush(stdout);
		return 0;
	}
	
	printf("보낸크기 %d \n", retval);
	printf("보낸데이타 %s \n", buf);
	fflush(stdout);
	
	printf("recv \n");
	retval = recv(sock, buf, 4096, 0);
	if(retval == -1)
	{
		printf("recv error \n");
		fflush(stdout);
		return 0;
	}
	
	printf("받은 크기 %d\n", retval);
	printf("받은 데이타 %s \n", buf);
	fflush(stdout);
	
	close(sock);

	return 0;
}
