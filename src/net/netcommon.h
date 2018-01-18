#ifndef _NET_COMMON_H_
#define _NET_COMMON_H_

namespace NetTool {
    inline int setnoblocking(int sockfd)
    {
        int opts = fcntl(sockfd, F_GETFL);
        if (opts < 0)
            return -1; 

        opts = opts | O_NONBLOCK;

        if (fcntl(sockfd, F_SETFL, opts) < 0)
            return -1;
        else 
            return 0;
    }
}



#endif //_NET_COMMON_H_
