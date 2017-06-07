//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2008 Greenplum, Inc.
//
//	@filename:
//		CSpinlock.inl
//
//	@doc:
//		Implementation of inlined functions;
//---------------------------------------------------------------------------
#ifndef GPOS_CSpinlock_INL
#define GPOS_CSpinlock_INL

#include "gpos/sync/atomic.h"

namespace gpos
{

	//---------------------------------------------------------------------------
	//	@function:
	//		CSpinlockRanked::Lock
	//
	//	@doc:
	//		Dtor
	//
	//---------------------------------------------------------------------------
	template<ULONG ulRank>
	CSpinlockRanked<ulRank>::~CSpinlockRanked()
	{}

	//---------------------------------------------------------------------------
	//	@function:
	//		CSpinlockRanked::Lock
	//
	//	@doc:
	//		Acquisition of lock; implements TTAS spinlock
	//
	//---------------------------------------------------------------------------
	template<ULONG ulRank>
	void
	CSpinlockRanked<ulRank>::Lock()
	{}


	//---------------------------------------------------------------------------
	//	@function:
	//		CSpinlockRanked::Unlock
	//
	//	@doc:
	//		Release lock;
	//
	//---------------------------------------------------------------------------
	template<ULONG ulRank>
	void
	CSpinlockRanked<ulRank>::Unlock()
	{}
		

#ifdef GPOS_DEBUG
	//---------------------------------------------------------------------------
	//	@function:
	//		CSpinlockRanked::FOwned
	//
	//	@doc:
	//		Check if we hold the lock; only to be used for asserts;
	//
	//---------------------------------------------------------------------------
	template<ULONG ulRank>
	BOOL
	CSpinlockRanked<ulRank>::FOwned()
	const
	{
        return true;
	}
#endif // GPOS_ASSERT
}

#endif // !GPOS_CSpinlock_INL

// EOF
