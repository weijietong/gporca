//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2011 EMC Corp
//
//	@filename:
//		CLogicalConstTableGetBelowCTE.cpp
//
//	@doc:
//		Implementation of const table access
//---------------------------------------------------------------------------

#include "gpos/base.h"
#include "gpopt/base/CUtils.h"

#include "gpopt/operators/CExpressionHandle.h"
#include "gpopt/operators/CLogicalConstTableGetBelowCTE.h"
#include "gpopt/operators/CLogicalConstTableGet.h"
#include "gpopt/metadata/CName.h"
#include "gpopt/base/CColRefSet.h"
#include "gpopt/base/CColRefTable.h"

using namespace gpopt;


//---------------------------------------------------------------------------
//	@function:
//		CLogicalConstTableGetBelowCTE::CLogicalConstTableGetBelowCTE
//
//	@doc:
//		ctor - for pattern
//
//---------------------------------------------------------------------------
CLogicalConstTableGetBelowCTE::CLogicalConstTableGetBelowCTE
	(
	IMemoryPool *pmp
	)
	:
	CLogicalConstTableGet(pmp)
{
}


//---------------------------------------------------------------------------
//	@function:
//		CLogicalConstTableGetBelowCTE::CLogicalConstTableGetBelowCTE
//
//	@doc:
//		ctor
//
//---------------------------------------------------------------------------
CLogicalConstTableGetBelowCTE::CLogicalConstTableGetBelowCTE
	(
	IMemoryPool *pmp,
	DrgPcoldesc *pdrgpcoldesc,
	DrgPdrgPdatum *pdrgpdrgpdatum
	)
	:
	CLogicalConstTableGet(pmp, pdrgpcoldesc, pdrgpdrgpdatum)
{
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalConstTableGetBelowCTE::CLogicalConstTableGetBelowCTE
//
//	@doc:
//		ctor
//
//---------------------------------------------------------------------------
CLogicalConstTableGetBelowCTE::CLogicalConstTableGetBelowCTE
	(
	IMemoryPool *pmp,
	DrgPcr *pdrgpcrOutput,
	DrgPdrgPdatum *pdrgpdrgpdatum
	)
	:
	CLogicalConstTableGet(pmp, pdrgpcrOutput, pdrgpdrgpdatum)
{
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalConstTableGetBelowCTE::~CLogicalConstTableGetBelowCTE
//
//	@doc:
//		dtor
//
//---------------------------------------------------------------------------
CLogicalConstTableGetBelowCTE::~CLogicalConstTableGetBelowCTE()
{
//	CRefCount::SafeRelease(m_pdrgpcoldesc);
//	CRefCount::SafeRelease(m_pdrgpdrgpdatum);
//	CRefCount::SafeRelease(m_pdrgpcrOutput);
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalConstTableGetBelowCTE::PxfsCandidates
//
//	@doc:
//		Get candidate xforms
//
//---------------------------------------------------------------------------
CXformSet *
CLogicalConstTableGetBelowCTE::PxfsCandidates
	(
	IMemoryPool *pmp
	) 
	const
{
	CXformSet *pxfs = GPOS_NEW(pmp) CXformSet(pmp);
	(void) pxfs->FExchangeSet(CXform::ExfImplementConstTableGetBelowCTE);
	return pxfs;
}




// EOF

