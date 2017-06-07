//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		CXformImplementConstTableGetBelowCTE.h
//
//	@doc:
//		Implement logical const table with a physical const table get
//---------------------------------------------------------------------------
#ifndef GPOPT_CXformImplementConstTableGetBelowCTE_H
#define GPOPT_CXformImplementConstTableGetBelowCTE_H

#include "gpos/base.h"
#include "gpopt/xforms/CXformImplementation.h"

namespace gpopt
{
	using namespace gpos;
	
	//---------------------------------------------------------------------------
	//	@class:
	//		CXformImplementConstTableGetBelowCTE
	//
	//	@doc:
	//		Implement const table get
	//
	//---------------------------------------------------------------------------
	class CXformImplementConstTableGetBelowCTE : public CXformImplementation
	{

		private:

			// private copy ctor
			CXformImplementConstTableGetBelowCTE(const CXformImplementConstTableGetBelowCTE &);

		public:
		
			// ctor
			explicit
			CXformImplementConstTableGetBelowCTE(IMemoryPool *);

			// dtor
			virtual 
			~CXformImplementConstTableGetBelowCTE() {}

			// ident accessors
			virtual
			EXformId Exfid() const
			{
				return ExfImplementConstTableGetBelowCTE;
			}
			
			// return a string for xform name
			virtual 
			const CHAR *SzId() const
			{
				return "CXformImplementConstTableGetBelowCTE";
			}
			
			// compute xform promise for a given expression handle
			virtual
			EXformPromise Exfp
				(
				CExpressionHandle & // exprhdl
				)
				const
			{
				return CXform::ExfpHigh;
			}

			// actual transform
			void Transform
				(
				CXformContext *pxfctxt,
				CXformResult *pxfres,
				CExpression *pexpr
				) 
				const;
		
	}; // class CXformImplementConstTableGetBelowCTE

}


#endif // !GPOPT_CXformImplementConstTableGetBelowCTE_H

// EOF
