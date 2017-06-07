//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		CPhysicalConstTableGetBelowCTE.h
//
//	@doc:
//		Physical const table get
//---------------------------------------------------------------------------
#ifndef GPOPT_CPhysicalConstTableGetBelowCTE_H
#define GPOPT_CPhysicalConstTableGetBelowCTE_H

#include "gpos/base.h"
#include "gpopt/operators/CPhysical.h"
#include "gpopt/operators/CPhysicalConstTableGet.h"


namespace gpopt
{
	
	//---------------------------------------------------------------------------
	//	@class:
	//		CPhysicalConstTableGetBelowCTE
	//
	//	@doc:
	//		Physical const table get operator
	//
	//---------------------------------------------------------------------------
	class CPhysicalConstTableGetBelowCTE : public CPhysicalConstTableGet
	{

		private:
			// private copy ctor
			CPhysicalConstTableGetBelowCTE(const CPhysicalConstTableGetBelowCTE &);

		public:
		
			// ctor
			CPhysicalConstTableGetBelowCTE
				(
				IMemoryPool *pmp,
				DrgPcoldesc *pdrgpcoldesc,
				DrgPdrgPdatum *pdrgpdrgpconst,
				DrgPcr *pdrgpcrOutput
				);

			// dtor
			virtual 
			~CPhysicalConstTableGetBelowCTE();

			// ident accessors
			virtual 
			EOperatorId Eopid() const
			{
				return EopPhysicalConstTableGet;
			}
			
			virtual 
			const CHAR *SzId() const
			{
				return "CPhysicalConstTableGetBelowCTE";
			}
		
			// match function
			BOOL FMatch(COperator *) const;

			// derive distribution
			virtual
			CDistributionSpec *PdsDerive(IMemoryPool *pmp, CExpressionHandle &exprhdl) const;

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------

			// conversion function
			static
			CPhysicalConstTableGetBelowCTE *PopConvert
				(
				COperator *pop
				)
			{
				GPOS_ASSERT(NULL != pop);
				GPOS_ASSERT(EopPhysicalConstTableGet == pop->Eopid() ||
							EopPhysicalConstTableGetBelowCTE == pop->Eopid());

				return dynamic_cast<CPhysicalConstTableGetBelowCTE*>(pop);
			}
		
	}; // class CPhysicalConstTableGetBelowCTE

}

#endif // !GPOPT_CPhysicalConstTableGetBelowCTE_H

// EOF
