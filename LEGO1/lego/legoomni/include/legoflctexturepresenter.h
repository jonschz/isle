#ifndef LEGOFLCTEXTUREPRESENTER_H
#define LEGOFLCTEXTUREPRESENTER_H

#include "decomp.h"
#include "mxflcpresenter.h"

class LegoTextureInfo;

// VTABLE: LEGO1 0x100d89e0
// VTABLE: BETA10 0x101bc3c8
// SIZE 0x70
class LegoFlcTexturePresenter : public MxFlcPresenter {
public:
	LegoFlcTexturePresenter();

	// FUNCTION: BETA10 0x100837e0
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f0634
		return "LegoFlcTexturePresenter";
	}

	// FUNCTION: LEGO1 0x1005def0
	// FUNCTION: BETA10 0x100837b0
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	void StartingTickle() override;                  // vtable+0x1c
	void LoadFrame(MxStreamChunk* p_chunk) override; // vtable+0x68
	void PutFrame() override;                        // vtable+0x6c

	// SYNTHETIC: LEGO1 0x1005df00
	// SYNTHETIC: BETA10 0x10083800
	// LegoFlcTexturePresenter::`scalar deleting destructor'

private:
	void Init();

	MxS32 m_rectCount;          // 0x68
	LegoTextureInfo* m_texture; // 0x6c
};

#endif // LEGOFLCTEXTUREPRESENTER_H
