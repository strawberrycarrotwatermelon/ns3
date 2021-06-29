/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*

 */
#include <iostream>
#include <stdio.h>
#include "ns3/log.h"
#include "ns3/enum.h"
#include "ns3/uinteger.h"
#include "ns3/double.h"
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "drop-tail-queue.h"
#include "broadcom-egress-queue.h"

NS_LOG_COMPONENT_DEFINE ("BEgressQueue");

namespace ns3 {

//NS_OBJECT_ENSURE_REGISTERED (BEgressQueue);

template <typename Item>
TypeId BEgressQueue<Item>::GetTypeId (void) 
{
  static TypeId tid = TypeId ("ns3::BEgressQueue")
    .SetParent<Queue<Item>> ()
    .template AddConstructor<BEgressQueue<Item>> ()
	/*
    .AddAttribute ("Mode", 
                   "Whether to use bytes (see MaxBytes) or packets (see MaxPackets) as the maximum queue size metric.",
                   EnumValue (QUEUE_MODE_BYTES),
                   MakeEnumAccessor (&BEgressQueue::SetMode),
                   MakeEnumChecker (QUEUE_MODE_BYTES, "QUEUE_MODE_BYTES",
                                    QUEUE_MODE_PACKETS, "QUEUE_MODE_PACKETS")) */
    .AddAttribute ("MaxBytes", 
                   "The maximum number of bytes accepted by this BEgressQueue.",
                   DoubleValue (1000.0 * 1024 * 1024),
                   MakeDoubleAccessor (&BEgressQueue::m_maxBytes),
                   MakeDoubleChecker<double> ())
  ;

  return tid;
}
template <typename Item>
BEgressQueue<Item>::BEgressQueue () :
  Queue<Item> ()
{
  NS_LOG_FUNCTION_NOARGS ();
  m_bytesInQueueTotal=0;
  m_shareused = 0;
  m_rrlast = 0;
  for (uint32_t i=0;i<fCnt;i++)
  {
	m_bytesInQueue[i]=0;
	m_queues.push_back( CreateObject<DropTailQueue<Item>>() );
  }
  m_fcount = 1; //reserved for highest priority
  for (uint32_t i = 0; i < qCnt; i++)
  {
	  m_bwsatisfied[i] = Time(0);
	  m_minBW[i] = DataRate("10Gb/s");
  }
  m_minBW[3] = DataRate("10Gb/s");
}

template <typename Item>
BEgressQueue<Item>::~BEgressQueue ()
{
  NS_LOG_FUNCTION_NOARGS ();
}

template <typename Item>
bool 
BEgressQueue<Item>::DoEnqueue (Ptr<Item> p, uint32_t qIndex)
{
  NS_LOG_FUNCTION (this << p);

  if (m_bytesInQueueTotal+p->GetSize()<m_maxBytes)  //infinite queue
  {
	  m_queues[qIndex]->Enqueue(p);
	  m_bytesInQueueTotal += p->GetSize();
	  m_bytesInQueue[qIndex] += p->GetSize();
  }
  else
  {
	  return false;
  }
  return true;
}
template <typename Item>
Ptr<Item>
BEgressQueue<Item>::DoDequeue (bool paused[]) //this is for switch only
{
  NS_LOG_FUNCTION (this);
  
  if (m_bytesInQueueTotal==0)
    {
      NS_LOG_LOGIC ("Queue empty");
      return 0;
    }

  //strict
  bool found=false;
  uint32_t qIndex;
  for (qIndex=1;qIndex<=qCnt;qIndex++)
  {
	  if (!paused[(qCnt-qIndex)%qCnt] && m_queues[(qCnt-qIndex)%qCnt]->GetNPackets()>0)
	  {
		  found = true;
		  break;
	  }
  }
  qIndex=(qCnt-qIndex)%qCnt;
	if (found)
	{
		Ptr<Packet> p = m_queues[qIndex]->Dequeue();
		m_bytesInQueueTotal -= p->GetSize();
		m_bytesInQueue[qIndex]-=p->GetSize();
		m_rrlast = qIndex;
		NS_LOG_LOGIC ("Popped " << p);
		NS_LOG_LOGIC ("Number bytes " << m_bytesInQueueTotal);
		return p;
	}
  NS_LOG_LOGIC ("Nothing can be sent");
  return 0;
}

template <typename Item>
Ptr<Item>
BEgressQueue<Item>::DoDequeueNIC (bool paused[])
{
  NS_LOG_FUNCTION (this);
  if (m_bytesInQueueTotal==0)
    {
      NS_LOG_LOGIC ("Queue empty");
      return 0;
    }
  bool found=false;
  uint32_t qIndex;
  for (qIndex=1;qIndex<=qCnt;qIndex++)  //round robin
  {
	  if (!paused[(qIndex+m_rrlast)%qCnt] && m_queues[(qIndex+m_rrlast)%qCnt]->GetNPackets()>0)
	  {
		  found = true;
		  break;
	  }
  }
  qIndex=(qIndex+m_rrlast)%qCnt;
	if (found)
	{
		Ptr<Packet> p = m_queues[qIndex]->Dequeue();
		m_bytesInQueueTotal -= p->GetSize();
		m_bytesInQueue[qIndex]-=p->GetSize();
		m_rrlast = qIndex;
		NS_LOG_LOGIC ("Popped " << p);
		NS_LOG_LOGIC ("Number bytes " << m_bytesInQueueTotal);
		m_qlast = qIndex;
		return p;
	}
  NS_LOG_LOGIC ("Nothing can be sent");
  return 0;
}

template <typename Item>
Ptr<Item>
BEgressQueue<Item>::DoDequeueRR (bool paused[]) //this is for switch only
{
  NS_LOG_FUNCTION (this);
  
  if (m_bytesInQueueTotal==0)
    {
      NS_LOG_LOGIC ("Queue empty");
      return 0;
    }
  bool found=false;
  uint32_t qIndex;

  if (m_queues[qCnt-1]->GetNPackets()>0) //7 is the highest priority
  {
	  found = true;
	  qIndex = qCnt - 1;
  }
  else
  {
	  for (qIndex = qCnt - 2; qIndex < qCnt; qIndex--) //strict policy
	  {
		  if (m_bwsatisfied[qIndex].GetTimeStep()<Simulator::Now().GetTimeStep() && m_queues[qIndex]->GetNPackets()>0 && !paused[qIndex])
		  {
			  found = true;
			  break;
		  }
	  }
	  if (!found)
	  {
		  for (qIndex = 1; qIndex <= qCnt; qIndex++)
		  {
			  if (!paused[(qIndex + m_rrlast) % qCnt] && m_queues[(qIndex + m_rrlast) % qCnt]->GetNPackets() > 0)  //round robin
			  {
				  found = true;
				  break;
			  }
		  }
		  qIndex = (qIndex + m_rrlast) % qCnt;
	  }
  }
	if (found)
	{
		Ptr<Packet> p = m_queues[qIndex]->Dequeue();
		m_bytesInQueueTotal -= p->GetSize();
		m_bytesInQueue[qIndex]-=p->GetSize();
		m_bwsatisfied[qIndex] = m_bwsatisfied[qIndex] + m_minBW[qIndex].CalculateBytesTxTime(p->GetSize());
		if (Simulator::Now() > Seconds (static_cast<double>(m_bwsatisfied[qIndex])))
			m_bwsatisfied[qIndex] = Simulator::Now();
		if (qIndex != qCnt-1)
		{
			m_rrlast = qIndex;
		}
		m_qlast = qIndex;
		NS_LOG_LOGIC ("Popped " << p);
		NS_LOG_LOGIC ("Number bytes " << m_bytesInQueueTotal);
		return p;
	}
  NS_LOG_LOGIC ("Nothing can be sent");
  return 0;
}
template <typename Item>
Ptr<Item>
BEgressQueue<Item>::DoDequeueQCN (bool paused[], Time avail[], uint32_t m_findex_qindex_map[])
{
  NS_LOG_FUNCTION (this);
  if (m_bytesInQueueTotal==0)
    {
      NS_LOG_LOGIC ("Queue empty");
      return 0;
    }
  bool found=false;
  uint32_t qIndex;
  if (m_queues[0]->GetNPackets()>0)  //priority 0 is the highest priority in qcn
  {
	  found = true;
	  qIndex = 0;
  }
  else
  {
	  for (qIndex=1;qIndex<=m_fcount;qIndex++)
	  {
		  if (!paused[m_findex_qindex_map[(qIndex+m_rrlast)%m_fcount]] && m_queues[(qIndex+m_rrlast)%m_fcount]->GetNPackets()>0)
		  {
			  if (avail[(qIndex+m_rrlast)%m_fcount].GetTimeStep() > Simulator::Now().GetTimeStep()) //not available now
				  continue;
			  found = true;
			  break;
		  }
	  }
	  qIndex=(qIndex+m_rrlast)%m_fcount;
  }
	if (found)
	{
		Ptr<Packet> p = m_queues[qIndex]->Dequeue();
		m_bytesInQueueTotal -= p->GetSize();
		m_bytesInQueue[qIndex]-=p->GetSize();
		if (qIndex!=0)
		{
			m_rrlast = qIndex;
		}
		m_qlast = qIndex;
		NS_LOG_LOGIC ("Popped " << p);
		NS_LOG_LOGIC ("Number bytes " << m_bytesInQueueTotal);
		return p;
	}
  NS_LOG_LOGIC ("Nothing can be sent");
  return 0;
}

template <typename Item>
bool 
BEgressQueue<Item>::Enqueue (Ptr<Item> p, uint32_t qIndex)
{
	NS_LOG_FUNCTION (this << p);
	//
	// If DoEnqueue fails, Queue::Drop is called by the subclass
	//
	bool retval = DoEnqueue (p, qIndex);
	if (retval)
	{
		NS_LOG_LOGIC ("m_traceEnqueue (p)");
		m_traceEnqueue (p);

		uint32_t size = p->GetSize ();
		m_nBytes += size;
		m_nTotalReceivedBytes += size;

		m_nPackets++;
		m_nTotalReceivedPackets++;
	}
	return retval;
}
template <typename Item>
Ptr<Item>
BEgressQueue<Item>::Dequeue (bool paused[])
{
	NS_LOG_FUNCTION (this);
	Ptr<Item> packet = DoDequeue (begin ());;
	if (packet != 0)
	{
		NS_ASSERT (m_nBytes >= packet->GetSize ());
		NS_ASSERT (m_nPackets > 0);
		m_nBytes -= packet->GetSize ();
		m_nPackets--;
		NS_LOG_LOGIC ("m_traceDequeue (packet)");
		m_traceDequeue (packet);
	}
	return packet;
}

template <typename Item>
Ptr<Item>
BEgressQueue<Item>::DequeueNIC (bool paused[])
{
	NS_LOG_FUNCTION (this);
	Ptr<Item> packet = DoDequeueNIC ();
	if (packet != 0)
	{
		NS_ASSERT (m_nBytes >= packet->GetSize ());
		NS_ASSERT (m_nPackets > 0);
		m_nBytes -= packet->GetSize ();
		m_nPackets--;
		NS_LOG_LOGIC ("m_traceDequeue (packet)");
		m_traceDequeue (packet);
	}
	return packet;
}
template <typename Item>
Ptr<Item>
BEgressQueue<Item>::DequeueRR (bool paused[])
{
	NS_LOG_FUNCTION (this);
	Ptr<Item> packet = DoDequeueRR (paused);
	if (packet != 0)
	{
		NS_ASSERT (m_nBytes >= packet->GetSize ());
		NS_ASSERT (m_nPackets > 0);
		m_nBytes -= packet->GetSize ();
		m_nPackets--;
		NS_LOG_LOGIC ("m_traceDequeue (packet)");
		m_traceDequeue (packet);
	}
	return packet;
}
template <typename Item>
Ptr<Item> 
BEgressQueue<Item>::DequeueQCN (bool paused[], Time avail[], uint32_t m_findex_qindex_map[])  //do all DequeueNIC does, plus QCN
{
	NS_LOG_FUNCTION (this);
	Ptr<Item> packet = DoDequeueQCN(paused, avail, m_findex_qindex_map);
	if (packet != 0)
	{
		NS_ASSERT (m_nBytes >= packet->GetSize ());
		NS_ASSERT (m_nPackets > 0);
		m_nBytes -= packet->GetSize ();
		m_nPackets--;
		NS_LOG_LOGIC ("m_traceDequeue (packet)");
		m_traceDequeue (packet);
	}
	return packet;
}


template <typename Item>
bool 
BEgressQueue<Item>::DoEnqueue (Ptr<Item> p)	//for compatiability
{
	std::cout<<"Warning: Call Broadcom queues without priority\n";
	uint32_t qIndex=0;
  NS_LOG_FUNCTION (this << p);
  if (m_bytesInQueueTotal+p->GetSize()<m_maxBytes)
  {
	  m_queues[qIndex]->Enqueue(p);
	  m_bytesInQueueTotal += p->GetSize();
	  m_bytesInQueue[qIndex] += p->GetSize();
  }
  else
  {
	  //std::cout<<"Dropped in compatiable egress queue!!!\n";
	  //exit(0);
	  return false;

  }
  return true;
}

template <typename Item>
Ptr<Item> 
BEgressQueue<Item>::DoDequeue (void)
{
	std::cout<<"Warning: Call Broadcom queues without priority\n";
	uint32_t paused[qCnt]={0};
	NS_LOG_FUNCTION (this);

	if (m_bytesInQueueTotal==0)
	{
		NS_LOG_LOGIC ("Queue empty");
		return 0;
	}

	bool found=false;
	uint32_t qIndex;
	for (qIndex = 1; qIndex <= qCnt; qIndex++)
	{
		if (paused[(qIndex + m_rrlast) % qCnt] == 0 && m_queues[qIndex]->GetNPackets() > 0)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		Ptr<Packet> p = m_queues[qIndex]->Dequeue();
		m_bytesInQueueTotal -= p->GetSize();
		m_bytesInQueue[qIndex]-=p->GetSize();
		m_rrlast = qIndex;
		NS_LOG_LOGIC ("Popped " << p);
		NS_LOG_LOGIC ("Number bytes " << m_bytesInQueueTotal);
		return p;
	}
	NS_LOG_LOGIC ("Nothing can be sent");
	return 0;
}

template <typename Item>
Ptr<const Item> 
BEgressQueue<Item>::DoPeek (void) const	//DoPeek doesn't work for multiple queues!!
{
	std::cout<<"Warning: Call Broadcom queues without priority\n";
	NS_LOG_FUNCTION (this);
	if (m_bytesInQueueTotal==0)
	{
		NS_LOG_LOGIC ("Queue empty");
		return 0;
	}
	NS_LOG_LOGIC ("Number packets " << m_packets.size ());
	NS_LOG_LOGIC ("Number bytes " << m_bytesInQueue);
	return m_queues[0]->Peek();
}
template <typename Item>
uint32_t 
BEgressQueue<Item>::GetNBytes (uint32_t qIndex) const
{
	return m_bytesInQueue[qIndex];
}

template <typename Item>
uint32_t 
BEgressQueue<Item>::GetNBytesTotal () const
{
	return m_bytesInQueueTotal;
}
template <typename Item>
uint32_t 
BEgressQueue<Item>::GetLastQueue ()
{
	return m_qlast;
}
template <typename Item>
void
BEgressQueue<Item>::RecoverQueue(Ptr<DropTailQueue<Item>> buffer, uint32_t i)
{
	Ptr<Item> packet;
	Ptr<DropTailQueue<Item>> tmp = CreateObject<DropTailQueue<Item>>();
	//clear orignial queue
	while (!m_queues[i]->IsEmpty())
	{
		packet = m_queues[i]->Dequeue();
		m_bytesInQueue[i] -= packet->GetSize();
		m_bytesInQueueTotal -= packet->GetSize();
	}
	//recover queue and preserve buffer
	while (!buffer->IsEmpty())
	{
		packet = buffer->Dequeue();
		tmp->Enqueue(packet->Copy());
		m_queues[i]->Enqueue(packet->Copy());
		m_bytesInQueue[i] += packet->GetSize();
		m_bytesInQueueTotal += packet->GetSize();
	}
	//restore buffer
	while (!tmp->IsEmpty())
	{
		buffer->Enqueue(tmp->Dequeue()->Copy());
	}

	/*
	Ptr<DropTailQueue> tmp = CreateObject<DropTailQueue>();
	Ptr<Packet> packet;
	while (!m_queues[i]->IsEmpty())
	{
		packet = m_queues[i]->Dequeue();
		tmp->Enqueue(packet);
	}
	while (!buffer->IsEmpty())
	{
		packet = buffer->Dequeue();
		m_queues[i]->Enqueue(packet);
	}
	while (!tmp->IsEmpty())
	{
		packet = tmp->Dequeue();
		m_queues[i]->Enqueue(packet);
	}
	*/
}


}
