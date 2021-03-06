#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>

int main(){
    int current_uid = getuid();
    printf("My UID is: %d. My GID is: %dn", current_uid, getgid());
    system("/usr/bin/id");
    if (setuid(0))
    {
        perror("setuid");
        return 1;
    }
    //I am now root!
    printf("My UID is: %d. My GID is: %dn", getuid(), getgid());
    system("/usr/bin/id");
    //Time to drop back to regular user privileges
    setuid(current_uid);
    printf("My UID is: %d. My GID is: %dn", getuid(), getgid());
    system("/usr/bin/id");
    return 0;
}
