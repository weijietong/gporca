//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2015 Pivotal, Inc.
//
//	@filename:
//		CXformLeftOuterJoinWithInnerSelect2BitmapIndexGetApply.h
//
//	@doc:
//		Transform Left Outer Join with a Select on the inner branch to
//		Bitmap IndexGet Apply
//
//	@owner:
//		n
//
//	@test:
//
//---------------------------------------------------------------------------

#ifndef GPOPT_CXformLeftOuterJoinWithInnerSelect2BitmapIndexGetApply_H
#define GPOPT_CXformLeftOuterJoinWithInnerSelect2BitmapIndexGetApply_H

#include "gpos/base.h"
#include "gpopt/xforms/CXformInnerJoin2IndexApply.h"

namespace gpopt
{
	using namespace gpos;

	//---------------------------------------------------------------------------
	//	@class:
	//		CXformLeftOuterJoinWithInnerSelect2BitmapIndexGetApply
	//
	//	@doc:
	//		Transform Inner Join with a Select on the inner branch to
	//		Bitmap IndexGet Apply
	//
	//---------------------------------------------------------------------------
	class CXformLeftOuterJoinWithInnerSelect2BitmapIndexGetApply : public CXformInnerJoin2IndexApply
	{
		private:
			// private copy ctor
			CXformLeftOuterJoinWithInnerSelect2BitmapIndexGetApply
				(
				const CXformLeftOuterJoinWithInnerSelect2BitmapIndexGetApply &
				);

		public:
			// ctor
			explicit
			CXformLeftOuterJoinWithInnerSelect2BitmapIndexGetApply(IMemoryPool *pmp);

			// dtor
			virtual
			~CXformLeftOuterJoinWithInnerSelect2BitmapIndexGetApply()
			{}

			// ident accessors
			virtual
			EXformId Exfid() const
			{
				return ExfLeftOuterJoinWithInnerSelect2BitmapIndexGetApply;
			}

			virtual
			const CHAR *SzId() const
			{
				return "CXformLeftOuterJoinWithInnerSelect2BitmapIndexGetApply";
			}

			// actual transform
			virtual
			void Transform(CXformContext *pxfctxt, CXformResult *pxfres, CExpression *pexpr) const;

	}; // class CXformLeftOuterJoinWithInnerSelect2BitmapIndexGetApply
}

#endif // !GPOPT_CXformLeftOuterJoinWithInnerSelect2BitmapIndexGetApply_H

// EOF
