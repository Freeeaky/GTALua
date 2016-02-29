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