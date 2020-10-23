int Socket(float num1, float num2, float num3) {

	int n1 = (int)num1;
	int n2 = (int)num2;
	int n3 = (int)num3;

	DecToHex(n1, n2, n3);


	int clnt_sock;
	struct sockaddr_in serv_addr;

	//

	clnt_sock = socket(PF_INET, SOCK_STREAM, 0);

	if (clnt_sock == -1);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.0.58");
	serv_addr.sin_port = htons(6112);

	if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1);
	if (write(clnt_sock, sendm, sizeof(sendm) - 1) == -1);

	sendm[0] = '\0';

	close(clnt_sock);
	return 0;

}
