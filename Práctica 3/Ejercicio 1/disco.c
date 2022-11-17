#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CAPACITY 5
#define VIPSTR(vip) ((vip) ? "  vip  " : "not vip")

void enter_normal_client(int id)
{

}

void enter_vip_client(int id)
{

}

void dance(int id, int isvip)
{
	printf("Client %2d (%s) dancing in disco\n", id, VIPSTR(isvip));
	sleep((rand() % 3) + 1);
}

void disco_exit(int id, int isvip)
{

}

void *client(void *arg)
{

}

int main(int argc, char *argv[])
{

	return 0;
}
