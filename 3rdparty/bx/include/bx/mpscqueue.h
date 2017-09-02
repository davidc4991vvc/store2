/*
<<<<<<< HEAD
 * Copyright 2010-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
=======
 * Copyright 2010-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bx#license-bsd-2-clause
>>>>>>> upstream/master
 */

#ifndef BX_MPSCQUEUE_H_HEADER_GUARD
#define BX_MPSCQUEUE_H_HEADER_GUARD

<<<<<<< HEAD
=======
#include "mutex.h"
>>>>>>> upstream/master
#include "spscqueue.h"

namespace bx
{
<<<<<<< HEAD
	template <typename Ty>
	class MpScUnboundedQueue
	{
		BX_CLASS(MpScUnboundedQueue
=======
	///
	template <typename Ty>
	class MpScUnboundedQueueT
	{
		BX_CLASS(MpScUnboundedQueueT
>>>>>>> upstream/master
			, NO_COPY
			, NO_ASSIGNMENT
			);

	public:
<<<<<<< HEAD
		MpScUnboundedQueue()
		{
		}

		~MpScUnboundedQueue()
		{
		}

		void push(Ty* _ptr) // producer only
		{
			LwMutexScope $(m_write);
			m_queue.push(_ptr);
		}

		Ty* peek() // consumer only
		{
			return m_queue.peek();
		}

		Ty* pop() // consumer only
		{
			return m_queue.pop();
		}

	private:
		LwMutex m_write;
		SpScUnboundedQueue<Ty> m_queue;
	};

=======
		///
		MpScUnboundedQueueT();

		///
		~MpScUnboundedQueueT();

		///
		void push(Ty* _ptr); // producer only

		///
		Ty* peek(); // consumer only

		///
		Ty* pop(); // consumer only

	private:
		Mutex m_write;
		SpScUnboundedQueueT<Ty> m_queue;
	};

	///
>>>>>>> upstream/master
	template <typename Ty>
	class MpScUnboundedBlockingQueue
	{
		BX_CLASS(MpScUnboundedBlockingQueue
			, NO_COPY
			, NO_ASSIGNMENT
			);

	public:
<<<<<<< HEAD
		MpScUnboundedBlockingQueue()
		{
		}

		~MpScUnboundedBlockingQueue()
		{
		}

		void push(Ty* _ptr) // producer only
		{
			m_queue.push(_ptr);
			m_sem.post();
		}

		Ty* pop() // consumer only
		{
			m_sem.wait();
			return m_queue.pop();
		}

	private:
		MpScUnboundedQueue<Ty> m_queue;
=======
		///
		MpScUnboundedBlockingQueue();

		///
		~MpScUnboundedBlockingQueue();

		///
		void push(Ty* _ptr); // producer only

		///
		Ty* pop(); // consumer only

	private:
		MpScUnboundedQueueT<Ty> m_queue;
>>>>>>> upstream/master
		Semaphore m_sem;
	};

} // namespace bx

<<<<<<< HEAD
=======
#include "inline/mpscqueue.inl"

>>>>>>> upstream/master
#endif // BX_MPSCQUEUE_H_HEADER_GUARD
