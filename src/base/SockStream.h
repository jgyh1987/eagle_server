#ifndef _SOCKSTREAM_H_
#define _SOCKSTREAM_H_

#include "Sys.h"
#include "Noncopyable.h"
#include "Eagle_Time.h"
#include "ByteBuffer.h"
#include "Lock.h"

namespace eagle
{

/// @brief 数据包包头大小
#define PH_LEN  (UINT32_LEN * 2)
/// @brief 数据包压缩最小大小
#define PACKET_ZIP_MIN  32
/// @brief 数据包压缩标志
#define PACKET_ZIP 0x40000000
/// @brief 数据包掩码
#define PACKET_MASK  (ServerSize - 1)
/// @brief 数据最大大小
#define MAX_DATABUFFERSIZE  PACKET_MASK
/// @brief 压缩数据最大大小
#define MAX_DATASIZE (MAX_DATABUFFERSIZE - PH_LEN)
/// @brief 用户数据最大大小
#define MAX_USERDATASIZE (MAX_DATASIZE - 128)
/// @brief 压缩标志
#define PACKET_FLAGS_ZIP  0x03
/// @brief 加密标志
#define PACKET_FLAGS_ENC  0xFC
#define PACKET_FLAGS_ZLIB  0x01
//ws min package head
#define PACKET_WS_MIN_LEN 2

#define SERVER_COMMAND_MAX_LENGTH 1024 * 1024 * 8

class CSockStream :private CNoncopyable
{
    public:
        /// @brief 数据读超时
        static const int T_RD_MSEC = 2100;
        /// @brief 数据写超时
        static const int T_WR_MSEC = 5100;
        /// @brief 读取不完全标志
        static const unsigned int INCOMPLETE_READ = 0x00000001;
        /// @brief 写不完全标志
        static const unsigned int INCOMPLETE_WRITE = 0x00000002;

        CSockStream();
        virtual ~CSockStream();

        uv_buf_t* GetReadBuf(bool isReset = false);
        //uv_buf_t* GetSendBuf();

        uint32_t RecvToBufNoPoll(ssize_t);
        virtual uint32_t RecvToCmdNoPoll(void *pstrCmd,const int nCmdLen);
        virtual uint32_t RecvToHttpNoPoll(void *pstrCmd, const int nCmdLen);
        virtual uint32_t RecvToWSNoPoll(void *pstrCmd, const int nCmdLen, bool &ready);
        uint32_t UnPackBufToCmd(unsigned char *buf, const uint32_t nBuffLen, void *pstrCmd,const int nCmdLen, int *mask = NULL);
        /// @brief 发送指令
        /// @param pstrCmd 待发送的内容
        /// @param nCmdLen 待发送内容的大小
        /// @param buffer 是否需要缓冲
        /// @return 发送是否成功
        //bool SendCmd(const void *pstrCmd, const int nCmdLen, stackcmdqueue &rawQueue);
        bool SendCmd(const void *pstrCmd, const int nCmdLen, unsigned char *outBuf, uint32_t &nBufLen, int mask = 0);
        virtual bool SendWSCmd(const void *pstrCmd, const int nCmdLen, unsigned char *outBuf, uint32_t &nBufLen);

        inline int RecvBufferSize() const 
        {
            return m_rcvQueue.MaxSize();
        }

        inline void ArrangementBuff()
        {
            return m_rcvQueue.MoveFlip();
        }

        void Clear();
private:
    /// @brief 套接口读写掩码
    inline void SetFlag(unsigned int f) { m_bitMask |= f; }
    inline bool IssetFlag(unsigned int f) const { return m_bitMask && f; }
    inline void ClearFlag(unsigned int f) { m_bitMask &= ~f; }

    inline unsigned int PacketMinSize() const { return PH_LEN; }
    inline unsigned int PacketWSMinSize() const { return PACKET_WS_MIN_LEN; }
    inline unsigned int PacketSize(const unsigned char *in) const ;
    inline unsigned int PacketWSSize(const unsigned char *req, uint32_t len) const;
    /// @brief 拆包
    /// @param in 输入数据
    /// @param nPacketLen 输入数据包长度
    /// @param out 输出数据
    /// @param outLen 输出数据长度
    inline unsigned int PacketUnpack(unsigned char *in, const unsigned int nPacketLen, unsigned char *out, const unsigned int outLen, int *mask = NULL);
    inline unsigned int PacketWSUnpack(unsigned char *req, unsigned char *out, const unsigned int outLen, bool &ready);
    /// @brief 
    /// @param pData
    /// @param nLen
    /// @param cmd_queue
    /// @return
    template<typename buffer_type>
    inline unsigned int PacketAppend(const void *pData, const unsigned int nLen, buffer_type &cmd_queue);
    /// @brief
    /// @param pData
    /// @param nLen
    /// @param cmd_queue
    /// @return
    template<typename buffer_type>
    inline unsigned int PacketAppendNoEnc(const void *pData, const unsigned int nLen, buffer_type &cmd_queue);
    /// @brief 
    /// @param pData
    /// @param nLen
    /// @param cmd_queue
    /// @return
    template <typename buffer_type>
    inline unsigned int PacketPackZip(const void *pData,const unsigned int nLen,buffer_type &cmd_queue,const bool _compress=false);

    unsigned int PacketPackAppend(const void*pData, const unsigned int nLen, unsigned char *cmd_queue, int mask = 0, const bool _compress=false);

private:
        uv_buf_t m_read_buf;
        uv_buf_t m_write_buf;

        /// @brief 接收缓冲
        buffercmdqueue m_rcvQueue;
        /// @brief 接收缓冲数据大小 
        unsigned int m_rcvRawSize;

        CMutex m_lock;

        /// @brief 位标志
        unsigned int m_bitMask;
};

};

#endif
