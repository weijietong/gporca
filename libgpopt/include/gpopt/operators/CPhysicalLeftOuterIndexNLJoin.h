//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2017 Pivotal, Inc.
//
//	Left outer index nested-loops join operator
//---------------------------------------------------------------------------
#ifndef GPOPT_CPhysicalLeftOuterIndexNLJoin_H
#define GPOPT_CPhysicalLeftOuterIndexNLJoin_H

#include "gpos/base.h"
#include "gpopt/operators/CPhysicalLeftOuterNLJoin.h"

namespace gpopt
{

	class CPhysicalLeftOuterIndexNLJoin : public CPhysicalLeftOuterNLJoin
	{

		private:

			// columns from outer child used for index lookup in inner child
			DrgPcr *m_pdrgpcrOuterRefs;

			// private copy ctor
			CPhysicalLeftOuterIndexNLJoin(const CPhysicalLeftOuterIndexNLJoin &);

		public:

			// ctor
			CPhysicalLeftOuterIndexNLJoin(IMemoryPool *pmp, DrgPcr *pdrgpcr);

			// dtor
			virtual
			~CPhysicalLeftOuterIndexNLJoin();

			// ident accessors
			virtual
			EOperatorId Eopid() const
			{
				return EopPhysicalLeftOuterIndexNLJoin;
			}

			 // return a string for operator name
			virtual
			const CHAR *SzId() const
			{
				return "CPhysicalLeftOuterIndexNLJoin";
			}

			// match function
			virtual
			BOOL FMatch(COperator *pop) const;

			// outer column references accessor
			DrgPcr *PdrgPcrOuterRefs() const
			{
				return m_pdrgpcrOuterRefs;
			}

			// compute required distribution of the n-th child
			virtual
			CDistributionSpec *PdsRequired
				(
				IMemoryPool *pmp,
				CExpressionHandle &exprhdl,
				CDistributionSpec *pdsRequired,
				ULONG ulChildIndex,
				DrgPdp *pdrgpdpCtxt,
				ULONG ulOptReq
				)
				const;

			// execution order of children
			virtual
			EChildExecOrder Eceo() const
			{
				// we optimize inner (right) child first to be able to match child hashed distributions
				return EceoRightToLeft;
			}

			// conversion function
			static
			CPhysicalLeftOuterIndexNLJoin *PopConvert
				(
				COperator *pop
				)
			{
				GPOS_ASSERT(EopPhysicalLeftOuterIndexNLJoin == pop->Eopid());

				return dynamic_cast<CPhysicalLeftOuterIndexNLJoin*>(pop);
			}

	}; // class CPhysicalLeftOuterIndexNLJoin

}

#endif // !GPOPT_CPhysicalLeftOuterIndexNLJoin_H

// EOF
