#include <linux/time.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <linux/time.h>

int main() {
	int y = 2;
	struct timespec result;
	printf("The initial value of tv-sec: %ld\n", result.tv_sec);
	printf("The initial value of tv_nsec: %ld\n", result.tv_nsec);

	y = syscall(326, &result);

	// check y

	if (y == -14) { //EFAULT
		printf("The timespec is pointing to a null pointer.\n");
		return 0;
	}
	if (y > 0) { //FAIL TO COPY TO USER
		printf("Fail to copy to the user.\n");
		return 0;
	}
	printf("syscall time: %ld\n", result.tv_sec);
	printf("syscall return value:%d\n",y);
	return 2;
}
