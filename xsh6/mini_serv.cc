#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <netinet/ip.h>
#include <sys/select.h>
#include <unistd.h>

using namespace std;

#define TwoPow16 65536 //4294967296
#define LEN 1024

fd_set rfds;
fd_set wfds;
fd_set allfds;

int UniqFD = 0;
int MaxFD = 0;

int IDs[ TwoPow16 ];
char *Inbox[ TwoPow16 ];

char buff_read[LEN + 1];
char Newsline[42];

void fatal();
void Send_everyone_except_sender(int, const char *);
void reg_client(int /*fd*/);
void rmv_client(int /*fd*/);
void send_msg(int /*fd*/);
int make_sock();
int unzip_msg(char **, char **);
char *strjoin(char *, char *);

int main(int argc, char ** argv)
{
    if (argc ^ 2)
    {
        cerr << "Wrong number of arguments\n";
        exit(1);
    }

    FD_ZERO( & allfds);
    int sockfd = make_sock();

    struct sockaddr_in servaddr;
    memset(& servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433); // localhost
    servaddr.sin_port = htons( atoi(argv[1]) );  // use : nc lc 8080

    if (bind(sockfd, reinterpret_cast<const sockaddr *>(& servaddr), sizeof(servaddr)))
        fatal();
    else if (listen(sockfd, SOMAXCONN))
        fatal();

    while (730)
    {
        rfds = wfds = allfds;
        if (select(MaxFD + 1, & rfds, & wfds, nullptr, nullptr) < 0)
            fatal();
        int i = -1;
        while (++i < MaxFD + 1)
        {
            if (!FD_ISSET(i, & rfds))
                continue;
            if (i == sockfd)
            {
                socklen_t addr_len = sizeof(servaddr);
                int client_fd = accept(
                    sockfd,
                    reinterpret_cast<struct sockaddr *>(& servaddr),
                    & addr_len
                );
                if (client_fd > -1)
                {
                    reg_client(client_fd);
                    break;
                }
            }
            else
            {
                int bytesread = recv(
                    i,
                    buff_read,
                    LEN,
                    0
                );
                if (bytesread < 1)
                {
                    rmv_client(i);
                    break;
                }
                buff_read[bytesread] = 0;
                Inbox[i] = strjoin(Inbox[i], buff_read);
                send_msg(i);
            }
        }
    }
}

int unzip_msg(char **buff, char **msg)
{
    char *buff_in;
    int i;

    *msg = nullptr;
    if ( * buff == nullptr)
        return 0;
    i = 0;
    while ((*buff)[i])
    {
        if ((*buff)[i] == '\n')
        {
            buff_in = new char[strlen(*buff + i + 1) + 1];

            if (buff_in == nullptr)
                return -1;
            strcpy(buff_in, * buff + i + 1);
            * msg = * buff;
            (* msg)[i + 1] = 0;
            *buff = buff_in;
            return 1;
        }
        i++;
    }
    return 0;
}

char *strjoin(char *buff, char *add)
{
    char * buff_in;
    int    len = (buff == nullptr) ? 0 : strlen(buff);

    buff_in = new char[len + strlen(add) + 1];
    if (buff_in == nullptr)
        return nullptr;
    buff_in[0] = 0;
    if (buff != nullptr)
        strcat(buff_in, buff);
    delete[] buff;
    strcat(buff_in, add);
    return buff_in;
}

void fatal()
{
    cerr << "Fatal error\n";
    exit(1);
}

void Send_everyone_except_sender(int senderfd, const char *str)
{
    int i = -1;
    while (++i < MaxFD + 1)
    {
        if (FD_ISSET(i, & wfds) && i ^ senderfd)
            send(i, str, strlen(str), 0);
    }
}

void reg_client(int fd)
{
    MaxFD = fd > MaxFD ? fd : MaxFD; // update the MaxFD which is a global

    IDs[fd] = UniqFD++;
    // this client is identified by IDs[fd]
    // the client is also assigned a unique client id: UniqFD | CountFD

    Inbox[fd] = nullptr;
    // init Inbox as null

    FD_SET(fd, & allfds);
    // + fd to allfds set

    // prepare a buffer to write w/ sprintf
    // announcement made using the buffer as msg
    sprintf(Newsline, "server: client %d just arrived\n", IDs[fd]);
    Send_everyone_except_sender(fd, Newsline);
}

void rmv_client(int fd)
{
    // announcement w/ a msg
    sprintf(Newsline, "server: client %d just left\n", IDs[fd]);
    Send_everyone_except_sender(fd, Newsline);

    // free the memory: free Inbox, clear fd, close fd
    delete [] Inbox[fd];
    FD_CLR(fd, & allfds);
    close(fd);
}

void send_msg(int fd)
{
    char * msg;

    while (unzip_msg( & Inbox[fd], &msg))
    {
        sprintf(Newsline, "client %d: ", IDs[fd]);
        Send_everyone_except_sender(fd, Newsline);
        Send_everyone_except_sender(fd, msg);
        delete [] msg;
    }
}

int make_sock()
{
    MaxFD = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );
    if (MaxFD < 0)
        fatal();
    FD_SET(MaxFD, & allfds);
    return MaxFD;
}

