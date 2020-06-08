#ifndef _BYTEBUFFER_H_
#define _BYTEBUFFER_H_

namespace eagle
{
/**
 *  ��ոĳɻ��λ��壬����ÿ�ζ���ݺ󣬽����ڴ濽��
 */

template <typename TYPE>
class CByteBuffer
{
    public:
        CByteBuffer();
        
        /// @brief ��ݷ��뻺�
        inline void Put(const unsigned char *buf,const unsigned int size)
        {
            WrReserve(size);
            bcopy(buf, &m_buffer[m_writePtr], size);
            m_writePtr += size;
        }
        
        /// @brief 嵱ǰ�����дλ�
        inline unsigned char* WrBuf()
        {
            return &m_buffer[m_writePtr];
        }
        
        /// @brief õ�ǰ����ɶ�λ�
        inline unsigned char* RdBuf()
        {
            return &m_buffer[m_readPtr];
        }
        
        /// @brief ��Ƿ�ɶ
        inline bool RdReady() const
        {
            return m_writePtr > m_readPtr;
        }

        /// @brief ��Ƿ��д
        inline unsigned int RdSize() const 
        {
            return m_writePtr - m_readPtr;
        }
        
        /// @brief �����ݵ��
        inline void RdFlip(unsigned int size)
        {
            if (m_readPtr + size <= m_writePtr)
                m_readPtr += size;
            else
                m_readPtr = m_writePtr;
        }

        /// @brief �ʣ������ƶ�
        inline void MoveFlip()
        {
            if(m_writePtr > m_readPtr)
            {
                unsigned int tmp = m_writePtr - m_readPtr;
                if(m_readPtr >= tmp)
                {
                    memmove(&m_buffer[0], &m_buffer[m_readPtr], tmp);
                    m_readPtr = 0;
                    m_writePtr = tmp;
                }
            }
            else
            {
                m_readPtr=0;
                m_writePtr=0;
            }
        }

        /// @brief ��д��ݴ�С
        inline unsigned int WrSize() const
        {
            return m_maxSize - m_writePtr;
        }

        /// @brief д��ݵ��
        inline void WrFlip(const unsigned int size)
        {
            m_writePtr+=size;
        }

        /// @brief ����û�� 
        inline void ReSet()
        {
            m_readPtr=0;
            m_writePtr=0;
        }

        /// @brief 建������С
        inline unsigned int MaxSize() const
        {
            return m_maxSize;
        }
        inline unsigned int ReadPtr() const
        {
            return m_readPtr;
        }
        inline unsigned int WritePtr()const 
        {
            return m_writePtr;
        }

        /// @brief �����size
        inline void WrReserve(const unsigned int size);
    private:
        unsigned int m_maxSize;
        unsigned int m_readPtr;
        unsigned int m_writePtr;
        TYPE m_buffer;
};
typedef CByteBuffer<std::vector<unsigned char> > buffercmdqueue;
    template<>
inline void buffercmdqueue::WrReserve(const unsigned int size)
{
    if(WrSize() < size)
    {
        m_maxSize += (ServerSize * ServerCount(size));
        m_buffer.resize(m_maxSize);
    }
}

typedef CByteBuffer<unsigned char[PACKET_ZIP_BUFFER]> stackcmdqueue;
    template<>
inline void stackcmdqueue::WrReserve(const unsigned int size)
{
}

};

#endif
