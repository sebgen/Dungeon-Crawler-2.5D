#ifndef RETRO3D_OBJECTPTRBASE_H
#define RETRO3D_OBJECTPTRBASE_H

/*=============================================================================================
Base class for object pointers.

==============================================================================================*/
#include "objectrefhandle.h"

namespace Retro3D
{
	class Object;

	template <class T>
	class ObjectPtrBase
	{
	protected:
		ObjectRefHandle* mRefHandle;

	public:
		inline Object* GetObjectSafe() const { return (mRefHandle != nullptr ? mRefHandle->GetObject() : nullptr); }

	public:
		T* Get() const;
		T* operator->() const;
		bool operator==(const ObjectPtrBase<T>& arg_other) const;
		bool operator!=(const ObjectPtrBase<T>& arg_other) const;
		bool operator==(const T* arg_other) const;
		bool operator!=(const T* arg_other) const;

		virtual bool IsValid() const;

	};
}

#include "objectptr_base.cpp"

#endif
