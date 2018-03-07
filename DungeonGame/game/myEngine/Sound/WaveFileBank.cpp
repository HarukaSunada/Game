#include "stdafx.h"
#include "WaveFileBank.h"
#include "WaveFile.h"
#include "myEngine/Util.h"

	CWaveFileBank::CWaveFileBank()
	{
	}
	CWaveFileBank::~CWaveFileBank()
	{
		ReleaseAll();
	}
	void CWaveFileBank::Release(int groupID)
	{
		for (auto waveFile : m_waveFileMap[groupID]) {
			waveFile.second->Release();
		}
		m_waveFileMap[groupID].clear();
	}
	void CWaveFileBank::RegistWaveFile(int groupID, CWaveFilePtr waveFile)
	{
		m_waveFileMap[groupID].insert({ waveFile->GetFilePathHash(), waveFile });
	}
	CWaveFilePtr CWaveFileBank::FindWaveFile(int groupID, const char* filePath)
	{
		auto value = m_waveFileMap[groupID].find(CUtil::MakeHash(filePath));
		if (value != m_waveFileMap[groupID].end()) {
			return value->second;
		}
		return CWaveFilePtr();
	}