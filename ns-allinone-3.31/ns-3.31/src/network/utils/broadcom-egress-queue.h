//yibo: one queue per port, also handle scheduling

#ifndef BROADCOM_EGRESS_H
#define BROADCOM_EGRESS_H


#include <queue>
#include "ns3/packet.h"
#include "queue.h"
#include "drop-tail-queue.h"
#include "ns3/point-to-point-net-device.h"
#include "ns3/event-id.h"

namespace ns3 {

class TraceContainer;

template <typename Item>
class BEgressQueue : public Queue<Item>
{
public:
  static TypeId GetTypeId (void);
  static const unsigned fCnt = 128; //max number of queues, 128 for NICs
  static const unsigned qCnt = 8; //max number of queues, 8 for switches
  BEgressQueue ();
  virtual ~BEgressQueue();
  bool Enqueue (Ptr<Item> p, uint32_t qIndex);
  Ptr<Item> Dequeue (bool paused[]);
  Ptr<Item> DequeueRR (bool paused[]);
  Ptr<Item> DequeueNIC (bool paused[]);//QCN disable NIC
  Ptr<Item> DequeueQCN (bool paused[], Time avail[], uint32_t m_findex_qindex_map[]);//QCN enable NIC
  uint32_t GetNBytes (uint32_t qIndex) const;
  uint32_t GetNBytesTotal () const;
  uint32_t GetLastQueue ();
  uint32_t m_fcount;
  void RecoverQueue(Ptr<DropTailQueue<Item>> buffer, uint32_t i);

private:
  bool DoEnqueue (Ptr<Item> p, uint32_t qIndex);
  Ptr<Item> DoDequeue (bool paused[]);
  Ptr<Item> DoDequeueNIC (bool paused[]);
  Ptr<Item> DoDequeueRR (bool paused[]);
  Ptr<Item> DoDequeueQCN (bool paused[], Time avail[], uint32_t m_findex_qindex_map[]);
  //for compatibility
  virtual bool DoEnqueue (Ptr<Item> p);
  virtual Ptr<Item> DoDequeue (void);
  virtual Ptr<const Item> DoPeek (void) const;
  std::queue<Ptr<Item> > m_packets;
  uint32_t m_maxPackets;
  double m_maxBytes; //total bytes limit
  uint32_t m_qmincell; //guaranteed see page 126
  uint32_t m_queuelimit; //limit for each queue
  uint32_t m_shareused; //used bytes by sharing
  uint32_t m_bytesInQueue[fCnt];
  uint32_t m_bytesInQueueTotal;
  uint32_t m_rrlast;
  uint32_t m_qlast;
  std::vector<Ptr<Queue<Item>> > m_queues; // uc queues
  //For strict priority
  Time m_bwsatisfied[qCnt];
  DataRate m_minBW[qCnt];

  using Queue<Item>::begin;
  using Queue<Item>::end;
  using Queue<Item>::DoEnqueue;
  using Queue<Item>::DoDequeue;
  using Queue<Item>::DoRemove;
  using Queue<Item>::DoPeek;
  using Queue<Item>::m_nBytes;               //!< Number of bytes in the queue
  using Queue<Item>:: m_nTotalReceivedBytes;               //!< Total received bytes
  using Queue<Item>::m_nPackets;             //!< Number of packets in the queue
  using Queue<Item>:: m_nTotalReceivedPackets;             //!< Total received packets
  using Queue<Item>:: m_nTotalDroppedBytes;                //!< Total dropped bytes
  using Queue<Item>:: m_nTotalDroppedBytesBeforeEnqueue;   //!< Total dropped bytes before enqueue
  using Queue<Item>:: m_nTotalDroppedBytesAfterDequeue;    //!< Total dropped bytes after dequeue
  using Queue<Item>:: m_nTotalDroppedPackets;              //!< Total dropped packets
  using Queue<Item>:: m_nTotalDroppedPacketsBeforeEnqueue; //!< Total dropped packets before enqueue
  using Queue<Item>:: m_nTotalDroppedPacketsAfterDequeue;  //!< Total dropped packets after dequeue

  using Queue<Item>::m_maxSize;                //!< max queue size

};

} // namespace ns3

#endif /* DROPTAIL_H */
