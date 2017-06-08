//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2011 EMC Corp.
//
//	@filename:
//		CLogicalConstTableGetBelowCTE.h
//
//	@doc:
//		Constant table accessor
//---------------------------------------------------------------------------
#ifndef GPOPT_CLogicalConstTableGetBelowCTE_H
#define GPOPT_CLogicalConstTableGetBelowCTE_H

#include "gpos/base.h"
#include "gpopt/operators/CLogicalConstTableGet.h"

namespace gpopt
{
	// dynamic array of datum arrays -- array owns elements
	typedef CDynamicPtrArray<DrgPdatum, CleanupRelease> DrgPdrgPdatum;

	//---------------------------------------------------------------------------
	//	@class:
	//		CLogicalConstTableGetBelowCTE
	//
	//	@doc:
	//		Constant table accessor
	//
	//---------------------------------------------------------------------------
	class CLogicalConstTableGetBelowCTE : public CLogicalConstTableGet
	{

		private:
			// private copy ctor
			CLogicalConstTableGetBelowCTE(const CLogicalConstTableGetBelowCTE &);

		public:
		
			// ctors
			explicit
			CLogicalConstTableGetBelowCTE(IMemoryPool *pmp);

			CLogicalConstTableGetBelowCTE
				(
				IMemoryPool *pmp,
				DrgPcoldesc *pdrgpcoldesc,
				DrgPdrgPdatum *pdrgpdrgpdatum
				);

			CLogicalConstTableGetBelowCTE
				(
				IMemoryPool *pmp,
				DrgPcr *pdrgpcrOutput,
				DrgPdrgPdatum *pdrgpdrgpdatum
				);

			// dtor
			virtual 
			~CLogicalConstTableGetBelowCTE();

			// ident accessors
			virtual 
			EOperatorId Eopid() const
			{
				return EopLogicalConstTableGet;
			}
			
			// return a string for operator name
			virtual 
			const CHAR *SzId() const
			{
				return "CLogicalConstTableGetBelowCTE";
			}
		
			//-------------------------------------------------------------------------------------
			// Transformations
			//-------------------------------------------------------------------------------------

			// candidate set of xforms
			virtual
			CXformSet *PxfsCandidates(IMemoryPool *pmp) const;

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------

			// conversion function
			static
			CLogicalConstTableGetBelowCTE *PopConvert
				(
				COperator *pop
				)
			{
				GPOS_ASSERT(NULL != pop);
				GPOS_ASSERT(EopLogicalConstTableGetBelowCTE == pop->Eopid() ||
							EopLogicalConstTableGet == pop->Eopid());
				
				return dynamic_cast<CLogicalConstTableGetBelowCTE*>(pop);
			}

			// return a copy of the operator with remapped columns
			virtual
			COperator *PopCopyWithRemappedColumns(IMemoryPool *pmp, HMUlCr *phmulcr, BOOL fMustExist);

	}; // class CLogicalConstTableGetBelowCTE

}


#endif // !GPOPT_CLogicalConstTableGetBelowCTE_H

// EOF
