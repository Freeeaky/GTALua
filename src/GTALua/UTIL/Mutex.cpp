// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "UTIL.h"

// =================================================================================
// Mutex 
// =================================================================================
Mutex::Mutex()
{
	m_bValid = true;
	
	InitializeCriticalSection(&m_csInternalHandle);
	Unlock();
}
Mutex::~Mutex()
{
	m_bValid = false;
	m_bLocked = true;

	DeleteCriticalSection(&m_csInternalHandle);
}

// =================================================================================
// Lock 
// =================================================================================
void Mutex::Lock()
{
	if (!m_bValid) return;
	m_bLocked = true;
	EnterCriticalSection(&m_csInternalHandle);
}
void Mutex::Unlock()
{
	if (!m_bValid) return;
	LeaveCriticalSection(&m_csInternalHandle);
	m_bLocked = false;
}
bool Mutex::TryLock()
{
	m_bLocked = TryEnterCriticalSection(&m_csInternalHandle);
	return m_bLocked;
}