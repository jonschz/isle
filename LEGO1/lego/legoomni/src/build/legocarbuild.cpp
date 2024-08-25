#include "legocarbuild.h"

#include "legocarbuildpresenter.h"
#include "legocontrolmanager.h"
#include "legogamestate.h"
#include "legoinputmanager.h"
#include "legoutils.h"
#include "misc.h"
#include "mxbackgroundaudiomanager.h"
#include "mxmisc.h"
#include "mxnotificationmanager.h"
#include "mxticklemanager.h"
#include "scripts.h"

DECOMP_SIZE_ASSERT(LegoCarBuild, 0x34c)
DECOMP_SIZE_ASSERT(LegoVehicleBuildState, 0x50)

// FUNCTION: LEGO1 0x100226d0
// FUNCTION: BETA10 0x1006ac10
LegoCarBuild::LegoCarBuild()
{
	// Not close yet - might be getting there when more of this class is implemented
	m_unk0x100 = 0;
	m_unk0x110 = 0;
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
	m_unk0x32c = NULL;
	m_unk0x33c = 0;
	m_buildState = 0;
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
// FUNCTION: BETA10 0x10070070
MxBool LegoCarBuild::VTable0x5c()
{
	return TRUE;
}

// STUB: LEGO1 0x10022a80
// FUNCTION: BETA10 0x1006aea3
LegoCarBuild::~LegoCarBuild()
{
	// TODO
	// ...
	NotificationManager()->Unregister(this);
}

// FUNCTION: LEGO1 0x10022b70
// FUNCTION: BETA10 0x1006afd9
MxResult LegoCarBuild::Create(MxDSAction& p_dsAction)
{
	MxResult result = LegoWorld::Create(p_dsAction);

	if (!result) {
		// TickleManager()->RegisterClient(this, 100);
		InputManager()->SetWorld(this);
		ControlManager()->Register(this);

		SetIsWorldActive(FALSE);

		InputManager()->Register(this);

		// variable name verified by BETA10 0x1006b1a6
		const char* buildStateClassName = NULL;

		if (m_atomId == *g_copterScript) {
			buildStateClassName = "LegoCopterBuildState";
			GameState()->SetCurrentArea(LegoGameState::Area::e_copterbuild);
			m_unk0x330 = 1;
		}
		else if (m_atomId == *g_dunecarScript) {
			buildStateClassName = "LegoDuneCarBuildState";
			GameState()->SetCurrentArea(LegoGameState::Area::e_dunecarbuild);
			m_unk0x330 = 2;
		}
		else if (m_atomId == *g_jetskiScript) {
			buildStateClassName = "LegoJetskiBuildState";
			GameState()->SetCurrentArea(LegoGameState::Area::e_jetskibuild);
			m_unk0x330 = 3;
		}
		else if (m_atomId == *g_racecarScript) {
			buildStateClassName = "LegoRaceCarBuildState";
			GameState()->SetCurrentArea(LegoGameState::Area::e_racecarbuild);
			m_unk0x330 = 4;
		}

		LegoGameState* gameState = GameState();

		LegoVehicleBuildState* buildState = (LegoVehicleBuildState*) gameState->GetState(buildStateClassName);

		if (!buildState) {
			buildState = (LegoVehicleBuildState*) gameState->CreateState(buildStateClassName);
		}

		m_buildState = buildState;

		m_unk0x174 = m_buildState->m_unk0x4d; // not found in BETA10

		GameState()->StopArea(LegoGameState::Area::e_previousArea);

		m_buildState->m_animationState = 1;
		m_unk0x100 = 0;

		BackgroundAudioManager()->Stop();
		EnableAnimations(FALSE);

		result = SUCCESS;
	}

	return result;
}

// STUB: LEGO1 0x10022f30
// STUB: BETA10 0x1006b835
void LegoCarBuild::FUN_10022f30()
{
	// TODO
}

// FUNCTION: LEGO1 0x10022fc0
// FUNCTION: BETA10 0x1006b90b
void LegoCarBuild::VTable0x6c()
{
	m_unk0x178 = m_unk0x1c0;
	m_unk0x110->WrappedSetLocalTransform(m_unk0x178);
	m_unk0x2a4 = Vector4(m_unk0x110->GetWorldPosition());

	VTable0x70();
}

// FUNCTION: LEGO1 0x10023020
// FUNCTION: BETA10 0x1006b991
void LegoCarBuild::VTable0x70()
{
	float worldPos[3];
	float screenPos[4];

	worldPos[0] = m_unk0x2a4[0];
	worldPos[1] = m_unk0x2a4[1];
	worldPos[2] = m_unk0x2a4[2];

	TransformWorldToScreen(worldPos, screenPos);

	m_unk0x290 = screenPos[0] / screenPos[3];
	m_unk0x294 = screenPos[1] / screenPos[3];

	worldPos[0] = m_unk0x2bc[0];
	worldPos[1] = m_unk0x2bc[1];
	worldPos[2] = m_unk0x2bc[2];

	TransformWorldToScreen(worldPos, screenPos);

	m_unk0x298 = screenPos[0] / screenPos[3];
	m_unk0x29c = screenPos[1] / screenPos[3];

	m_unk0x2a0 = sqrt(
		(float) (m_unk0x298 - m_unk0x290) * (m_unk0x298 - m_unk0x290) +
		(m_unk0x29c - m_unk0x294) * (m_unk0x29c - m_unk0x294)
	);

	m_unk0x25c.Unknown1(m_unk0x178, m_unk0x208);
}

// FUNCTION: LEGO1 0x10023500
// FUNCTION: BETA10 0x1006bdf6
void LegoCarBuild::VTable0x74(float param_1[3], float param_2[3])
{
	float fVar1;
	float local_20[3];
	float local_14[3];

	FUN_1003ded0(param_1, local_14, local_20);

	fVar1 = (m_unk0x2a4[2] - local_20[2]) / local_14[2];
	param_2[0] = (fVar1 * local_14[0] + local_20[0]) - m_unk0x2a4[0];
	param_2[1] = (fVar1 * local_14[1] + local_20[1]) - m_unk0x2a4[1];
	param_2[2] = 0.0;
	return;
}

// FUNCTION: LEGO1 0x10023570
// FUNCTION: BETA10 0x1006be91
void LegoCarBuild::VTable0x78(float param_1[3], float param_2[3])
{
	float fVar1;
	float local_18[3];
	float local_c[3];

	FUN_1003ded0(param_1, local_18, local_c);

	param_2[2] =
		m_unk0x2a4[2] + (m_unk0x2bc[2] - m_unk0x2a4[2]) * ((param_1[1] - m_unk0x294) / (m_unk0x29c - m_unk0x294));
	fVar1 = (param_2[2] - local_c[2]) / local_18[2];
	param_2[0] = fVar1 * local_18[0] - m_unk0x2a4[0] + local_c[0];
	param_2[1] = fVar1 * local_18[1] - m_unk0x2a4[1] + local_c[1];
	param_2[2] = param_2[2] - m_unk0x2a4[2];
}

// FUNCTION: LEGO1 0x10023620
// FUNCTION: BETA10 0x1006be91
void LegoCarBuild::VTable0x7c(float param_1[3], float param_2[3])
{
	float local_18[3];
	float local_c[3];
	FUN_1003ded0(param_1, local_18, local_c);

	float fVar1 = (m_unk0x2bc[1] - local_c[1]) / local_18[1];
	param_2[0] = fVar1 * local_18[0] - m_unk0x2a4[0] + local_c[0];
	param_2[1] = m_unk0x2bc[1] - m_unk0x2a4[1];
	param_2[2] = fVar1 * local_18[2] - m_unk0x2a4[2] + local_c[2];
}

// FUNCTION: LEGO1 0x100236a0
// FUNCTION: BETA10 0x100701f0
void LegoCarBuild::VTable0x80(float param_1[2], float param_2[2], float param_3, float param_4[2])
{
	// The code does the right thing and matches BETA10 perfectly, but mismatches LEGO1.
	// Maybe compiler entropy?
	if (param_1[1] == 0.0f) {
		return;
	}
	param_4[0] = ((param_3 - param_2[1]) / param_1[1]) * param_1[0] + param_2[0];
	param_4[1] = param_3;
}

#define LOOPTEST(start, end, str)                                                                                      \
	if (start < dTime && dTime < end) {                                                                                \
		FUN_10025db0(str, dTime - end);                                                                                \
		return SUCCESS;                                                                                                \
	}

// FUNCTION: LEGO1 0x100238b0
// FUNCTION: BETA10 0x1006c18f
MxResult LegoCarBuild::Tickle()
{
	if (!m_worldStarted) {
		LegoWorld::Tickle();
		return SUCCESS;
	}

	if (m_unk0xf8 == 8) {
		if (m_unk0xfc == 1) {
			FUN_10024f50();
		}

		if (m_unk0x110) {
			if (m_unk0x258->FUN_10079ca0(m_unk0x110->GetName())) {
				FUN_10022f30();
			}
		}
	}

	if (m_unk0x100 == 5 && m_unk0x110) {
		FUN_1003dde0(m_unk0x110, -0.1f);
	}

	if (m_unk0x10a) {
		DWORD time = timeGetTime();
		DWORD dTime = (time - m_unk0x10c) / 100;

		if (m_unk0x330 == 4) {
			switch (m_unk0x10a) {
			// TODO: Work out constants
			case 500:
				LOOPTEST(160, 180, "Exit_Ctrl")
				LOOPTEST(260, 280, "ShelfUp_Ctl")
				LOOPTEST(330, 340, "Yellow_Ctl")
				LOOPTEST(340, 360, "Platform_Ctl")
				LOOPTEST(390, 410, "Exit_Ctrl")
			case 503:
				LOOPTEST(50, 60, "ShelfUp_Ctl")
				LOOPTEST(65, 70, "Yellow_Ctl")
				LOOPTEST(70, 80, "Platform_Ctl")
				LOOPTEST(95, 105, "Exit_Ctrl")
			case 504:
				LOOPTEST(24, 29, "Exit_Ctrl")
				LOOPTEST(35, 40, "ShelfUp_Ctl")
				LOOPTEST(45, 50, "Yellow_Ctl")
				LOOPTEST(58, 63, "Platform_Ctl")
			default:
				return SUCCESS;
			}
		}
		else if (m_unk0x330 == 3) {
			switch (m_unk0x10a) {
			case 500:
				LOOPTEST(291, 311, "Exit_Ctrl")
				LOOPTEST(311, 331, "ShelfUp_Ctl")
				LOOPTEST(412, 432, "Yellow_Ctl")
				LOOPTEST(437, 457, "Platform_Ctl")
				LOOPTEST(485, 505, "Exit_Ctrl")
			case 501:
				LOOPTEST(34, 39, "Exit_Ctrl")
				LOOPTEST(70, 75, "ShelfUp_Ctl")
				LOOPTEST(105, 115, "Yellow_Ctl")
				LOOPTEST(135, 140, "Platform_Ctl")
			case 504:
				LOOPTEST(78, 98, "Exit_Ctrl")
			case 505:
				LOOPTEST(93, 113, "Exit_Ctrl")
				// default: // not sure if present
				// 	return SUCCESS;
			}
		}
		else if (m_unk0x330 == 2) {
			switch (m_unk0x10a) {
			case 500:
				LOOPTEST(155, 175, "Exit_Ctrl")
				LOOPTEST(215, 235, "ShelfUp_Ctl")
				LOOPTEST(285, 305, "Yellow_Ctl")
				LOOPTEST(300, 320, "Platform_Ctl")
				LOOPTEST(340, 360, "Exit_Ctrl")
			case 501:
				LOOPTEST(23, 33, "Exit_Ctrl")
				LOOPTEST(39, 44, "ShelfUp_Ctl")
				LOOPTEST(105, 115, "Yellow_Ctl")
				LOOPTEST(124, 129, "Platform_Ctl")
			default:
				return SUCCESS;
			}
		}
		else if (m_unk0x330 == 1) {
			switch (m_unk0x10a) {
			case 500:
				LOOPTEST(185, 205, "Exit_Ctrl")
				LOOPTEST(235, 255, "ShelfUp_Ctl")
				LOOPTEST(292, 312, "Yellow_Ctl")
				LOOPTEST(315, 335, "Platform_Ctl")
				LOOPTEST(353, 373, "Exit_Ctrl")
			case 501:
				LOOPTEST(45, 50, "Exit_Ctrl")
				LOOPTEST(74, 79, "ShelfUp_Ctl")
				LOOPTEST(116, 121, "Yellow_Ctl")
				LOOPTEST(130, 135, "Platform_Ctl")
			case 505:
				LOOPTEST(30, 40, "ShelfUp_Ctl")
				LOOPTEST(60, 70, "Yellow_Ctl")
				LOOPTEST(48, 58, "Platform_Ctl")
			default:
				return SUCCESS;
			}
		}
	}

	return 0;
}

// STUB: LEGO1 0x10024050
// FUNCTION: BETA10 0x1006c976
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

// FUNCTION: LEGO1 0x10024f50
// FUNCTION: BETA10 0x1006dfce
void LegoCarBuild::FUN_10024f50()
{
	m_unk0x2d4 = FALSE;
	m_unk0x258->FUN_10079920(0.07f);
}

// FUNCTION: LEGO1 0x100256c0
// FUNCTION: BETA10 0x1006e96c
void LegoCarBuild::Enable(MxBool p_enable)
{
	LegoWorld::Enable(p_enable);

	if (p_enable) {
		InputManager()->SetWorld(this);
		SetIsWorldActive(FALSE);
	}
	else {
		BackgroundAudioManager()->Init();
		if (InputManager()->GetWorld() == this) {
			InputManager()->ClearWorld();
		}
	}
}

// STUB: LEGO1 0x10025db0
// STUB: BETA10 0x1006ed18
void LegoCarBuild::FUN_10025db0(const char* param_1, undefined4 param_2)
{
	// TODO
}

// FUNCTION: LEGO1 0x10025e70
MxBool LegoCarBuild::Escape()
{
	BackgroundAudioManager()->Init();
	int p_targetEntityId = FUN_10025ee0(m_unk0x330);
	InvokeAction(Extra::ActionType::e_stop, *g_jukeboxScript, p_targetEntityId, NULL);
	DeleteObjects(&m_atomId, 500, 999);

	m_buildState->m_animationState = 0;
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
