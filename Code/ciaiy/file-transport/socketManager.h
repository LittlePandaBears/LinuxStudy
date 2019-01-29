#ifndef _SOCKETMANAGER_H_
#define _SOCKETMANAGER_H_

class socketManager{
    public :
    int getTarget(CJSON *package);
    bool addSocket(int socketfd);
    bool delSocket(int socketfd);
    private :
    vector<int> sockList;
}

#endif