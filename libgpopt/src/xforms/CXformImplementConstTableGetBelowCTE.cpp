//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		CXformImplementConstTableGetBelowCTE.cpp
//
//	@doc:
//		Implementation of transform
//---------------------------------------------------------------------------

#include "gpos/base.h"
#include "gpopt/xforms/CXformImplementConstTableGetBelowCTE.h"

#include "gpopt/operators/ops.h"

using namespace gpopt;


//---------------------------------------------------------------------------
//	@function:
//		CXformImplementConstTableGetBelowCTE::CXformImplementConstTableGetBelowCTE
//
//	@doc:
//		Ctor
//
//---------------------------------------------------------------------------
CXformImplementConstTableGetBelowCTE::CXformImplementConstTableGetBelowCTE
	(
	IMemoryPool *pmp
	)
	:
	CXformImplementation
		(
		 // pattern
		GPOS_NEW(pmp) CExpression
				(
				pmp,
				GPOS_NEW(pmp) CLogicalConstTableGetBelowCTE(pmp)
				)
		)
{}


//---------------------------------------------------------------------------
//	@function:
//		CXformImplementConstTableGetBelowCTE::Transform
//
//	@doc:
//		Actual transformation
//
//---------------------------------------------------------------------------
void
CXformImplementConstTableGetBelowCTE::Transform
	(
	CXformContext *pxfctxt,
	CXformResult *pxfres,
	CExpression *pexpr
	)
	const
{
	GPOS_ASSERT(NULL != pxfctxt);
	GPOS_ASSERT(FPromising(pxfctxt->Pmp(), this, pexpr));
	GPOS_ASSERT(FCheckPattern(pexpr));

	CLogicalConstTableGetBelowCTE *popConstTableGetBelowCTE = CLogicalConstTableGetBelowCTE::PopConvert(pexpr->Pop());
	IMemoryPool *pmp = pxfctxt->Pmp();

	// create/extract components for alternative
	DrgPcoldesc *pdrgpcoldesc = popConstTableGetBelowCTE->Pdrgpcoldesc();
	pdrgpcoldesc->AddRef();
	
	DrgPdrgPdatum *pdrgpdrgpdatum = popConstTableGetBelowCTE->Pdrgpdrgpdatum();
	pdrgpdrgpdatum->AddRef();
	
	DrgPcr *pdrgpcrOutput = popConstTableGetBelowCTE->PdrgpcrOutput();
	pdrgpcrOutput->AddRef();
		
	// create alternative expression
	CExpression *pexprAlt = 
		GPOS_NEW(pmp) CExpression
			(
			pmp,
			GPOS_NEW(pmp) CPhysicalConstTableGetBelowCTE(pmp, pdrgpcoldesc, pdrgpdrgpdatum, pdrgpcrOutput)
			);
	
	// add alternative to transformation result
	pxfres->Add(pexprAlt);
}


// EOF

