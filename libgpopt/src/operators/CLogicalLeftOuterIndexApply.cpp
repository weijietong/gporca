//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2013 Pivotal, Inc.
//
//	@filename:
//		CLogicalLeftOuterIndexApply.cpp
//
//	@doc:
//		Implementation of index apply operator
//---------------------------------------------------------------------------

#include "gpos/base.h"

#include "gpopt/operators/CLogicalLeftOuterIndexApply.h"

#include "naucrates/statistics/CStatisticsUtils.h"

using namespace gpopt;

//---------------------------------------------------------------------------
//	@function:
//		CLogicalLeftOuterIndexApply::CLogicalLeftOuterIndexApply
//
//	@doc:
//		Ctor - for patterns
//
//---------------------------------------------------------------------------
CLogicalLeftOuterIndexApply::CLogicalLeftOuterIndexApply
	(
	IMemoryPool *pmp
	)
	:
	CLogicalApply(pmp),
	m_pdrgpcrOuterRefs(NULL)
{
	m_fPattern = true;
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalLeftOuterIndexApply::CLogicalLeftOuterIndexApply
//
//	@doc:
//		Ctor
//
//---------------------------------------------------------------------------
CLogicalLeftOuterIndexApply::CLogicalLeftOuterIndexApply
	(
	IMemoryPool *pmp,
	DrgPcr *pdrgpcrOuterRefs
	)
	:
	CLogicalApply(pmp),
	m_pdrgpcrOuterRefs(pdrgpcrOuterRefs)
{
	GPOS_ASSERT(NULL != pdrgpcrOuterRefs);
}


//---------------------------------------------------------------------------
//	@function:
//		CLogicalLeftOuterIndexApply::~CLogicalLeftOuterIndexApply
//
//	@doc:
//		Dtor
//
//---------------------------------------------------------------------------
CLogicalLeftOuterIndexApply::~CLogicalLeftOuterIndexApply()
{
	CRefCount::SafeRelease(m_pdrgpcrOuterRefs);
}


//---------------------------------------------------------------------------
//	@function:
//		CLogicalLeftOuterIndexApply::Maxcard
//
//	@doc:
//		Derive max card
//
//---------------------------------------------------------------------------
CMaxCard
CLogicalLeftOuterIndexApply::Maxcard
	(
	IMemoryPool *, // pmp
	CExpressionHandle &exprhdl
	)
	const
{
	return CLogical::Maxcard(exprhdl, 2 /*ulScalarIndex*/, MaxcardDef(exprhdl));
}


//---------------------------------------------------------------------------
//	@function:
//		CLogicalLeftOuterIndexApply::PxfsCandidates
//
//	@doc:
//		Get candidate xforms
//
//---------------------------------------------------------------------------
CXformSet *
CLogicalLeftOuterIndexApply::PxfsCandidates
	(
	IMemoryPool *pmp
	)
	const
{
	CXformSet *pxfs = GPOS_NEW(pmp) CXformSet(pmp);
	(void) pxfs->FExchangeSet(CXform::ExfImplementLeftOuterIndexApply);

	return pxfs;
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalLeftOuterIndexApply::FMatch
//
//	@doc:
//		Match function
//
//---------------------------------------------------------------------------
BOOL
CLogicalLeftOuterIndexApply::FMatch
	(
	COperator *pop
	)
	const
{
	GPOS_ASSERT(NULL != pop);

	if (pop->Eopid() == Eopid())
	{
		return m_pdrgpcrOuterRefs->FEqual(CLogicalLeftOuterIndexApply::PopConvert(pop)->PdrgPcrOuterRefs());
	}

	return false;
}


//---------------------------------------------------------------------------
//	@function:
//		CLogicalLeftOuterIndexApply::PopCopyWithRemappedColumns
//
//	@doc:
//		Return a copy of the operator with remapped columns
//
//---------------------------------------------------------------------------
COperator *
CLogicalLeftOuterIndexApply::PopCopyWithRemappedColumns
	(
	IMemoryPool *pmp,
	HMUlCr *phmulcr,
	BOOL fMustExist
	)
{
	DrgPcr *pdrgpcr = CUtils::PdrgpcrRemap(pmp, m_pdrgpcrOuterRefs, phmulcr, fMustExist);

	return GPOS_NEW(pmp) CLogicalLeftOuterIndexApply(pmp, pdrgpcr);
}


//---------------------------------------------------------------------------
//	@function:
//		CLogicalLeftOuterIndexApply::PstatsDerive
//
//	@doc:
//		Derive statistics
//
//---------------------------------------------------------------------------
IStatistics *
CLogicalLeftOuterIndexApply::PstatsDerive
	(
	IMemoryPool *pmp,
	CExpressionHandle &exprhdl,
	DrgPstat* // pdrgpstatCtxt
	)
	const
{
	GPOS_ASSERT(EspNone < Esp(exprhdl));

	IStatistics *pstatsOuter = exprhdl.Pstats(0);
	IStatistics *pstatsInner = exprhdl.Pstats(1);
	CExpression *pexprScalar = exprhdl.PexprScalarChild(2 /*ulChildIndex*/);

	// join stats of the children
	DrgPstat *pdrgpstat = GPOS_NEW(pmp) DrgPstat(pmp);
	pstatsOuter->AddRef();
	pdrgpstat->Append(pstatsOuter);
	pstatsInner->AddRef();
	pdrgpstat->Append(pstatsInner);
	IStatistics *pstats = CStatisticsUtils::PstatsJoinArray(pmp, true /*fOuterJoin*/, pdrgpstat, pexprScalar);
	pdrgpstat->Release();

	return pstats;
}

// EOF

