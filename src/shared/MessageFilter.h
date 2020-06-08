#ifndef _MESSAGE_FILTER_H_
#define _MESSAGE_FILTER_H_

#include "Sys.h"

enum CLIENT_MSGFILTER_TYPE
{
    CLIENT_MSGFILTER_TYPE_NONE = 0,    //�
    CLIENT_MSGFILTER_TYPE_WARN = 1, //�
    CLIENT_MSGFILTER_TYPE_ERROR = 2,    //����
};

struct ClientMessage
{
    uint64_t time;
    ClientMessage()
    {
        //majorCmd = 0;
        //minorCmd = 0;
        time = 0;
    }
};

class MessageFilter
{
    private:
        /// @brief ��ϴ���Ϣʱ�
        uint64_t m_lastMessageTime;
        uint32_t m_lastMessageMajorCmd;
        uint32_t m_lastMessageMinorCmd;
        uint8_t mode;

        /// @brief �ѭ�����
        ClientMessage *m_messages;
        /// @brief 鵱ǰ��Ϣ���
        uint32_t m_mssIndex;
        /// @brief ������С
        uint32_t m_filterSize;
        /// @brief  ��������Ϣ������
        uint32_t m_filterTime;
        
        /// @brief ���Ϣ��
        uint32_t m_interval;
        uint32_t m_frequentlyMsgCount;
        uint32_t m_frequentlyMsgCountMax;

    public:
        MessageFilter();
        ~MessageFilter();

        uint32_t DoFilter(const ClientMessage& message, char *ip = NULL);
        void Clear();

        inline void SetFilterSize(uint32_t filterSize)
        {
            m_filterSize = filterSize;
            delete [] m_messages;
            m_messages = new ClientMessage[m_filterSize];
        }

        inline void SetFilterTime(uint32_t filterTime)
        {
            m_filterTime = filterTime;
        }

        inline void SetInterval(uint32_t interval)
        {
            m_interval = interval;
        }

        inline void SetFrequentlyMsgCountMax(uint32_t frequentlyMsgCountMax)
        {
            m_frequentlyMsgCountMax = frequentlyMsgCountMax;
        }
};

#endif

