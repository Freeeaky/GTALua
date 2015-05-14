// =================================================================================
// Mutex
// =================================================================================
class Mutex
{
public:
	Mutex();
	~Mutex();

	bool IsValid() { return m_bValid; };
	bool IsLocked() { return m_bLocked && m_bValid; };

	bool TryLock();
	void Lock();
	void Unlock();

private:
	bool m_bValid;
	bool m_bLocked;
	CRITICAL_SECTION m_csInternalHandle;
};