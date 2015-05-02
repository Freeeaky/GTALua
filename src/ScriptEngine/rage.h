// =================================================================================
// rage
// =================================================================================
namespace rage
{
	struct PtrCollection
	{
		DWORD64** m_ppData;
		uint16_t m_iCount;
		uint16_t m_iSize;

		DWORD64** begin() { return m_ppData; }
		DWORD64** end() { return m_ppData + m_iCount; }
		DWORD64* at(uint16_t iIndex) { return m_ppData[iIndex]; }
		uint16_t count() { return m_iCount; }
	};

	struct CVector
	{
		CVector()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		CVector(float x_, float y_, float z_)
		{
			x = x_;
			y = y_;
			z = z_;
		}

		float x;
		BYTE _spacer_1[4];
		float y;
		BYTE _spacer_2[4];
		float z;
		BYTE _spacer_3[4];
	};
}