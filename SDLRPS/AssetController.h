#ifndef ASSET_CONTROLLER_H
#define ASSET_CONTROLLER_H

#include "StandardIncludes.h"
#include "StackAllocator.h"
#include "Asset.h"

class AssetController : public Singleton<AssetController>
{
public:
	AssetController();
	virtual ~AssetController();

	void Initialize(int _stackSize);
	Asset* GetAsset(string _guid);
	void Clear();

	static StackAllocator* Stack;

private:
	map<string, Asset*> m_assets;
};

#endif ASSET_CONTROLLER_H
