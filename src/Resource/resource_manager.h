#ifndef RETRO3D_RESOURCEMANAGER_H
#define RETRO3D_RESOURCEMANAGER_H

#include "res_ptr.h"
#include "resource.h"
#include <functional>
#include <vector>
#include <mutex>
#include "Threading/thread.h"
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

namespace Retro3D
{
	struct QueuedAsyncResourceLoad
	{
		Resource* resource;
		std::function<void()> callback;
		std::string path;
	};

	class ResourceManager
	{
	private:
		std::vector<QueuedAsyncResourceLoad> mQueuedAsyncResourceLoadRequests;
		std::vector<QueuedAsyncResourceLoad> mCompletedAsyncResourceLoadRequests;

		std::mutex mGuard_QueuedAsyncResourceLoadRequests;
		std::mutex mGuard_CompletedAsyncResourceLoadRequests;

		void asyncLoadThread_Tick();

		Thread mAsyncLoadThread;
		std::unordered_map<std::type_index, std::unordered_map<std::string, Resource*>> mCachedResources;

		Resource* getCahcedResource(const std::type_index& arg_type, const std::string& arg_path);

	public:
		ResourceManager();

		void OnStart();
		void ProcessCompletedAsyncLoads();
		
		template <typename T>
		ResPtr<T> LoadResource(const std::string& arg_path)
		{
			const std::type_index& typeIndex = typeid(T);
			T* resObj = (T*)getCahcedResource(typeIndex, arg_path);

			if (resObj == nullptr)
			{
				resObj = new T();

				resObj->LoadResource(arg_path);
			}
			ResPtr<T> resPtr(resObj);

			return resPtr;
		}

		template <typename T>
		ResPtr<T> LoadResourceAsync(const std::string& arg_path, std::function<void()> arg_callback = {})
		{
#ifdef  __EMSCRIPTEN__ // TODO: does emcc support threads yet?
			ResPtr<T> res = LoadResource<T>(arg_path);
			arg_callback();
			return res;
#endif

			const std::type_index& typeIndex = typeid(T);
			T* resObj = getCahcedResource(typeIndex, arg_path);

			if (resObj == nullptr)
			{
				resObj = new T();

				QueuedAsyncResourceLoad queuedAsyncLoad;
				queuedAsyncLoad.resource = resObj;
				queuedAsyncLoad.callback = arg_callback;

				mGuard_QueuedAsyncResourceLoadRequests.lock();
				mQueuedAsyncResourceLoadRequests.push_back(queuedAsyncLoad);
				mGuard_QueuedAsyncResourceLoadRequests.unlock();
			}
			ResPtr<T> resPtr(resObj);

			return resPtr;
		}
		
	};
}

#endif
