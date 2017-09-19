#include "objectrefhandle.h"

namespace Retro3D
{
	ObjectRefHandle::ObjectRefHandle(Object* arg_object)
		: mObject(arg_object), mStrongRefCount(0), mWeakRefCount(0)
	{
		maybeDelete();
	}

	void ObjectRefHandle::SetObject(Object* arg_object)
	{
		mObject = arg_object; 
		if (mObject == nullptr)
		{
			maybeDelete();
		}
	}

	void ObjectRefHandle::AddStrongRef()
	{
		mStrongRefCount++;
	}

	void ObjectRefHandle::RemoveStrongRef()
	{
		mStrongRefCount--;

		if (mStrongRefCount == 0 && mObject != nullptr)
		{
			delete(mObject);
			mObject = nullptr;
		}

		maybeDelete();
	}

	void ObjectRefHandle::AddWeakRef()
	{
		mWeakRefCount++;
	}

	void ObjectRefHandle::RemoveWeakRef()
	{
		mWeakRefCount--;

		maybeDelete();
	}

	void ObjectRefHandle::maybeDelete()
	{
		if (mObject == nullptr && mStrongRefCount == 0 && mWeakRefCount == 0)
		{
			delete(this);
		}
	}
}
