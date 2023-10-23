#include "iostream"
#include "sys/socket.h" // close . select
#include "netinet/in.h"
#include "vector"

#define MAX 77777

int sock, conn, top, rune; 
int num = 0;

struct sockaddr_in servaddr, cli;

fd_set  AA, RR, WW;
socklen_t   len = sizeof(cli);

std::vector<int> uuid( MAX );
std::vector<std::string> msgs( MAX );

char    buff[1024 + 1];

std::string head;

int extract_message(std::string & buf, std::string & msg);
void speak(int, const std::string &);
void fate();

int main(int ac, char **v) {
    if (ac ^ 2) {
        std::cerr << "Wrong number of arguments" << std::endl;
        exit(1);
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        fate();

    memset( & servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433); // 127.0.0.1
    servaddr.sin_port = htons(atoi(v[1]));

    if (bind(sock, (const struct sockaddr * ) & servaddr, sizeof(servaddr)) == -1)
        fate();
    else if (listen(sock, 10) == -1)
        fate();

    FD_ZERO(&AA);
    FD_SET(sock, &AA);
    top = sock;

    while (true) {
        RR = WW = AA;
        if (select(top + 1, & RR, & WW, nullptr, nullptr) < 0)
            fate();

        int fd = -1;

        while (++fd <= top) {

            if (!FD_ISSET(fd, & RR))
                continue;

            if (fd == sock) {
                if ((conn = accept(sock, (struct sockaddr *) & cli, & len)) < 0)
                    fate();
                top = std::max(top, conn);
                uuid[conn] = num++;
                msgs[conn] = "";
                speak(conn, "server: client " + std::to_string(uuid[conn]) + " just arrived\n");
                FD_SET(conn, & AA);
            } else if ((rune = recv(fd, buff, 1024, 0)) < 1) {
                speak(fd, "server: client " + std::to_string(uuid[fd]) + " just left\n");
                close(fd);
                msgs[fd] = "";
                FD_CLR(fd, & AA);
                break;
            }
            buff[rune] = 0;
            msgs[fd] += buff;
            std::string s;
            extract_message(msgs[fd], s);
            speak(fd, "client " + std::to_string(uuid[fd]) + ": " + s);
            /* for (std::string s; extract_message(msgs[fd], s);)
                speak(fd, "client " + std::to_string(uuid[fd]) + ": " + s); */
        }
    }
}

// 

void speak(int ff, const std::string & s)
{
    int fd = -1;
    while (++fd < top + 1) {
        if (FD_ISSET(fd, & WW) && fd != ff)
            send(fd, s.c_str(), s.length(), 0);
    }
}

void fate()
{
    std::cerr << "Fatal error\n";
    exit(1);
}

int extract_message(std::string & buf, std::string & msg)
{
    if (buf.empty())
        return 0;
    size_t newline_pos = buf.find('\n');
    if (newline_pos != std::string::npos)
    {
        msg = buf.substr(0, newline_pos + 1);
        buf = buf.substr(newline_pos + 1);
        return 1;
    }
    return 0;
}
