#ifndef _CPP_CMD_QUEUE_H_
#define _CPP_CMD_QUEUE_H_

#include "Sys.h"
#include "Lock.h"

namespace eagle
{

typedef std::pair<unsigned int , unsigned char *> CmdPair;
//#define m_queueSize    1024

class CCmdQueue
{
    public:
        CCmdQueue(uint32_t queuesize = 102400);
        
        ~CCmdQueue();
        typedef std::pair<volatile bool , CmdPair > CmdQueue;
        CmdPair *get();
        void pop();
        void popNoDel();
        bool push(const void *ptNullCmd, const unsigned int cmdLen);
        void clear();
        
    private:
        
        bool putQueueToArray();

        CmdQueue *cmdQueue;
        std::queue<CmdPair, std::deque<CmdPair> > queueCmd;

    private:
        unsigned int queueWrite;
        unsigned int queueRead;

        uint32_t m_queueSize;
};

class CConCmdQueue
{
    protected:
        CConCmdQueue(uint32_t queuesize, uint32_t onceDoMsgNum = 500)
            :m_rev_queue(queuesize), m_send_queue(queuesize), m_onceDoMsgNum(onceDoMsgNum)
        {
            
        }
        virtual ~CConCmdQueue()
        {
        }

    public:
        //收到消息后的即时处理 或者 push到队列 等待doCmd处理 此处如果即时处理需要考虑多线程
        virtual bool msgParase(void *ptNullCmd ,const unsigned int cmdLen)
        {
            return  m_rev_queue.push((void*)ptNullCmd , cmdLen);
        }
        //doCmd中解析消息  单线程处理
        virtual bool cmdMsgParse(void *,const uint32_t)=0;
        virtual bool doCmd();

        bool PutSendBuf(void *ptNullCmd, const unsigned int cmdLen);
        uint32_t GetSendBuf(unsigned char **ptNullCmd, uint32_t *cmdLen); 

        void ClearQueue();

    private:
        CCmdQueue m_rev_queue;
        CCmdQueue m_send_queue;

        uint32_t m_onceDoMsgNum;
};

};

#endif

