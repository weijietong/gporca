//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2014 Pivotal, Inc.
//
//	@filename:
//		CXformLeftOuterJoin2BitmapIndexGetApply.h
//
//	@doc:
//		Transform Inner Join to Bitmap IndexGet Apply
//
//	@owner:
//		n
//
//	@test:
//
//---------------------------------------------------------------------------

#ifndef GPOPT_CXformLeftOuterJoin2BitmapIndexGetApply_H
#define GPOPT_CXformLeftOuterJoin2BitmapIndexGetApply_H

#include "gpos/base.h"
#include "gpopt/xforms/CXformInnerJoin2IndexApply.h"

namespace gpopt
{
	using namespace gpos;

	//---------------------------------------------------------------------------
	//	@class:
	//		CXformLeftOuterJoin2BitmapIndexGetApply
	//
	//	@doc:
	//		Transform Inner Join to Bitmap IndexGet Apply
	//
	//---------------------------------------------------------------------------
	class CXformLeftOuterJoin2BitmapIndexGetApply : public CXformInnerJoin2IndexApply
	{
		private:
			// private copy ctor
			CXformLeftOuterJoin2BitmapIndexGetApply(const CXformLeftOuterJoin2BitmapIndexGetApply &);

		public:
			// ctor
			explicit
			CXformLeftOuterJoin2BitmapIndexGetApply(IMemoryPool *pmp);

			// dtor
			virtual
			~CXformLeftOuterJoin2BitmapIndexGetApply()
			{}

			// ident accessors
			virtual
			EXformId Exfid() const
			{
				return ExfLeftOuterJoin2BitmapIndexGetApply;
			}

			virtual
			const CHAR *SzId() const
			{
				return "CXformLeftOuterJoin2BitmapIndexGetApply";
			}

			// actual transform
			virtual
			void Transform(CXformContext *pxfctxt, CXformResult *pxfres, CExpression *pexpr) const;
	}; // class CXformLeftOuterJoin2BitmapIndexGetApply
}

#endif // !GPOPT_CXformLeftOuterJoin2BitmapIndexGetApply_H

// EOF
