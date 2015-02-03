
#pragma once

#include <malloc.h>

namespace Windows
{
    template <class T>
    class CSinglyLinkedList
    {
        NO_COPY(CSinglyLinkedList);

        struct Node;

    public:
        class CNodePtr
        {
            friend class CSinglyLinkedList;

            NO_COPY(CNodePtr);

            explicit CNodePtr(Node* p)
                : p1st(p)
                , pNode(p)
            {
            }

        public:
            CNodePtr(void)
                : p1st(0)
                , pNode(0)
            {
            }

            ~CNodePtr(void)
            {
                Destroy();
            }

        public:
            T* Detach()
            {
                T* pT = pNode->pT;

                pNode->pT = 0;

                return pT;
            }

        public:
            operator bool() const
            {
                return (pNode && pNode->pT);
            }

            T* operator->() const
            {
                return pNode->pT;
            }

            T& operator*() const
            {
                return *(pNode->pT);
            }

            void operator++(void)
            {
                pNode = static_cast<Node*>(pNode->Next);
            }

        private:
            void Destroy()
            {
                pNode = p1st;

                while (pNode)
                {
                    Node* p = static_cast<Node*>(pNode->Next);

                    delete pNode->pT;

                    _aligned_free(pNode);

                    pNode = p;
                }

                p1st = pNode;
            }

        private:
            Node* p1st;

            Node* pNode;
        };

    public:
        CSinglyLinkedList(void)
            : m_pHeader(static_cast<PSLIST_HEADER>
                        (_aligned_malloc(sizeof(SLIST_HEADER),
                                         MEMORY_ALLOCATION_ALIGNMENT)))
        {
            InitializeSListHead(m_pHeader);
        }

        ~CSinglyLinkedList(void)
        {
            CNodePtr(static_cast<Node*>(InterlockedFlushSList(m_pHeader)));

            _aligned_free(m_pHeader);
        }

    public:
        void PushEntry(T* pT)
        {
            if (!pT)
                DebugBreak();

            Node* pNode =
                static_cast<Node*>(_aligned_malloc(sizeof(Node),
                                                   MEMORY_ALLOCATION_ALIGNMENT));

            ZeroMemory(pNode, sizeof(Node));

            pNode->pT = pT;

            InterlockedPushEntrySList(m_pHeader, pNode);
        }

        void PopEntry(CNodePtr& p)
        {
            p.Destroy();

            p.p1st = p.pNode =
                static_cast<Node*>(InterlockedPopEntrySList(m_pHeader));

            p.pNode->Next = 0;
        }

        void Flush(CNodePtr& p)
        {
            p.Destroy();

            Node* pThis = static_cast<Node*>(InterlockedFlushSList(m_pHeader))
               ,* pPrev = 0;

            while (pThis)
            {
                Node* pNext = static_cast<Node*>(pThis->Next);
                pThis->Next = pPrev;
                pPrev = pThis;
                pThis = pNext;
            }

            p.p1st = p.pNode = pPrev;
        }

        USHORT QueryDepth() const
        {
            return QueryDepthSList(m_pHeader);
        }

    private:
        struct Node : public SLIST_ENTRY
        {
            T* pT;
        };

    private:
        PSLIST_HEADER const m_pHeader;
    };
}
