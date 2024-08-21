#include "legocarbuild.h"

#include "legoutils.h"
#include "misc.h"
#include "mxbackgroundaudiomanager.h"
#include "mxmisc.h"
#include "mxnotificationmanager.h"
#include "scripts.h"
#include "legoinputmanager.h"

DECOMP_SIZE_ASSERT(LegoCarBuild, 0x34c)
DECOMP_SIZE_ASSERT(LegoVehicleBuildState, 0x50)

// FUNCTION: LEGO1 0x100226d0
LegoCarBuild::LegoCarBuild() : m_unk0x28c(0)
{
	// Not close yet - might be getting there when more of this class is implemented
	m_unk0x110 = 0;
	m_unk0x100 = 0;
	m_unk0xf8 = 0xffffffff;
	m_unk0x2d4 = '\0';
	m_unk0x258 = 0;
	m_unk0x2dc = 0;
	m_unk0x2e0 = 0;
	m_unk0x2e4 = 0;
	m_unk0x2e8 = 0;
	m_unk0x2ec = 0;
	m_unk0x2f0 = 0;
	m_unk0x2f4 = 0;
	m_unk0x2f8 = 0;
	m_unk0x2fc = 0;
	m_unk0x300 = 0;
	m_unk0x304 = 0;
	m_unk0x308 = 0;
	m_unk0x30c = 0;
	m_unk0x310 = 0;
	m_unk0x314 = 0;
	m_unk0x318 = 0;
	m_unk0x31c = 0;
	m_unk0x320 = 0;
	m_unk0x324 = 0;
	m_unk0x328 = 0;
	m_unk0x2d8 = 0;
	m_unk0x33c = 0;
	m_unk0x32c = 0;
	m_unk0x104 = 0;
	m_unk0x109 = '\0';
	m_unk0x108 = '\0';
	m_unk0x338 = 0;
	m_unk0x334 = 0;
	m_unk0x344 = 0xffffffff;
	m_unk0x174 = '\0';
	NotificationManager()->Register(this);
}

// FUNCTION: LEGO1 0x10022930
MxBool LegoCarBuild::VTable0x5c()
{
	return TRUE;
}

// STUB: LEGO1 0x10022a80
LegoCarBuild::~LegoCarBuild()
{
	// TODO
	// ...
	NotificationManager()->Unregister(this);
}

// FUNCTION: LEGO1 0x10022b70
MxResult LegoCarBuild::Create(MxDSAction& p_dsAction)
{
	// TODO
	MxResult result = LegoWorld::Create(p_dsAction);

	return SUCCESS;
}

// STUB: LEGO1 0x10022fc0
void LegoCarBuild::VTable0x6c()
{
	// TODO
}

// STUB: LEGO1 0x10023020
void LegoCarBuild::VTable0x70()
{
	// TODO
	// good candidate for m_unk0x290
}

// STUB: LEGO1 0x10023500
void LegoCarBuild::VTable0x74()
{
	// TODO
}

// STUB: LEGO1 0x10023570
void LegoCarBuild::VTable0x78()
{
	// TODO
}

// STUB: LEGO1 0x10023620
void LegoCarBuild::VTable0x7c()
{
	// TODO
}

// STUB: LEGO1 0x100236a0
void LegoCarBuild::VTable0x80()
{
	// TODO
}

// STUB: LEGO1 0x100238b0
MxResult LegoCarBuild::Tickle()
{
	// TODO
	return 0;
}

// STUB: LEGO1 0x10024050
MxLong LegoCarBuild::Notify(MxParam& p_param)
{
	// TODO
	return 0;
}

// STUB: LEGO1 0x100242c0
void LegoCarBuild::ReadyWorld()
{
	// TODO
}

// FUNCTION: LEGO1 0x100256c0
void LegoCarBuild::Enable(MxBool p_enable)
{
	LegoWorld::Enable(p_enable);

	if (p_enable) {
		InputManager()->SetWorld(this);
		SetIsWorldActive(FALSE);
	} else {
		BackgroundAudioManager()->Init();
		if (InputManager()->GetWorld() == this) {
			InputManager()->ClearWorld();
		}
	}
}

// FUNCTION: LEGO1 0x10025e70
MxBool LegoCarBuild::Escape()
{
	BackgroundAudioManager()->Init();
	int p_targetEntityId = FUN_10025ee0(m_unk0x330);
	InvokeAction(Extra::ActionType::e_stop, *g_jukeboxScript, p_targetEntityId, NULL);
	DeleteObjects(&m_atomId, 500, 999);

	m_unk0x32c->m_animationState = 0;
	m_unk0x334 = 2;
	return TRUE;
}

// FUNCTION: LEGO1 0x10025ee0
int LegoCarBuild::FUN_10025ee0(int param_1)
{
	// TODO: Work out constants
	switch (param_1) {
	case 1:
		return 0x2f;
	case 2:
		return 0x31;
	case 3:
		return 0x33;
	case 4:
		return 0x35;
	default:
		return -1;
	}
}

// FUNCTION: LEGO1 0x10025f30
LegoVehicleBuildState::LegoVehicleBuildState(const char* p_classType)
{
	m_className = p_classType;
	m_unk0x4c = 0;
	m_unk0x4d = FALSE;
	m_unk0x4e = FALSE;
	m_placedPartCount = 0;
}

// FUNCTION: LEGO1 0x10026120
MxResult LegoVehicleBuildState::Serialize(LegoFile* p_file)
{
	LegoState::Serialize(p_file);

	if (p_file->IsReadMode()) {
		Read(p_file, &m_unk0x4c);
		Read(p_file, &m_unk0x4d);
		Read(p_file, &m_unk0x4e);
		Read(p_file, &m_placedPartCount);
	}
	else {
		Write(p_file, m_unk0x4c);
		Write(p_file, m_unk0x4d);
		Write(p_file, m_unk0x4e);
		Write(p_file, m_placedPartCount);
	}

	return SUCCESS;
}
