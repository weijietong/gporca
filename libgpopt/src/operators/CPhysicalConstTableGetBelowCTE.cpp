//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		CPhysicalConstTableGetBelowCTE.cpp
//
//	@doc:
//		Implementation of physical const table get operator
//---------------------------------------------------------------------------

#include "gpos/base.h"

#include "gpopt/base/CDistributionSpecUniversal.h"
#include "gpopt/base/CUtils.h"
#include "gpopt/base/CCTEMap.h"
#include "gpopt/base/COptCtxt.h"
#include "gpopt/operators/CPhysicalConstTableGetBelowCTE.h"
#include "gpopt/operators/CExpressionHandle.h"


using namespace gpopt;


//---------------------------------------------------------------------------
//	@function:
//		CPhysicalConstTableGetBelowCTE::CPhysicalConstTableGetBelowCTE
//
//	@doc:
//		Ctor
//
//---------------------------------------------------------------------------
CPhysicalConstTableGetBelowCTE::CPhysicalConstTableGetBelowCTE
	(
	IMemoryPool *pmp,
	DrgPcoldesc *pdrgpcoldesc,
	DrgPdrgPdatum *pdrgpdrgpdatum,
	DrgPcr *pdrgpcrOutput
	)
	:
	CPhysicalConstTableGet(pmp, pdrgpcoldesc, pdrgpdrgpdatum, pdrgpcrOutput)
{}


//---------------------------------------------------------------------------
//	@function:
//		CPhysicalConstTableGetBelowCTE::~CPhysicalConstTableGetBelowCTE
//
//	@doc:
//		Dtor
//
//---------------------------------------------------------------------------
CPhysicalConstTableGetBelowCTE::~CPhysicalConstTableGetBelowCTE()
{}


//---------------------------------------------------------------------------
//	@function:
//		CPhysicalConstTableGetBelowCTE::FMatch
//
//	@doc:
//		Match operators
//
//---------------------------------------------------------------------------
BOOL
CPhysicalConstTableGetBelowCTE::FMatch
	(
	COperator *pop
	)
	const
{
	if (Eopid() == pop->Eopid())
	{
		CPhysicalConstTableGetBelowCTE *popCTG = CPhysicalConstTableGetBelowCTE::PopConvert(pop);
		return m_pdrgpcoldesc == popCTG->Pdrgpcoldesc() && 
				m_pdrgpdrgpdatum == popCTG->Pdrgpdrgpdatum() && 
				m_pdrgpcrOutput == popCTG->PdrgpcrOutput();
	}
	
	return false;
}

//---------------------------------------------------------------------------
//	@function:
//		CPhysicalConstTableGetBelowCTE::PdsDerive
//
//	@doc:
//		Derive distribution
//
//---------------------------------------------------------------------------
CDistributionSpec *
CPhysicalConstTableGetBelowCTE::PdsDerive
	(
	IMemoryPool *pmp,
	CExpressionHandle & // exprhdl
	)
	const
{
	return GPOS_NEW(pmp) CDistributionSpecSingleton(CDistributionSpecSingleton::EstMaster);
}


// EOF

