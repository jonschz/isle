#include "legoanimationmanager.h"

#include "define.h"
#include "islepathactor.h"
#include "legocharactermanager.h"
#include "legogamestate.h"
#include "legoomni.h"
#include "legoroilist.h"
#include "misc.h"
#include "mxbackgroundaudiomanager.h"
#include "mxmisc.h"
#include "mxticklemanager.h"
#include "mxtimer.h"
#include "mxutilities.h"
#include "roi/legoroi.h"

#include <io.h>

DECOMP_SIZE_ASSERT(LegoAnimationManager, 0x500)
DECOMP_SIZE_ASSERT(Character, 0x18)
DECOMP_SIZE_ASSERT(Vehicle, 0x08)
DECOMP_SIZE_ASSERT(Unknown0x3c, 0x18)
DECOMP_SIZE_ASSERT(LegoTranInfo, 0x78)

// GLOBAL: LEGO1 0x100f6d20
Vehicle g_vehicles[] = {
	{"bikebd", 0, FALSE},
	{"bikepg", 0, FALSE},
	{"bikerd", 0, FALSE},
	{"bikesy", 0, FALSE},
	{"motoni", 0, FALSE},
	{"motola", 0, FALSE},
	{"board", 0, FALSE}
};

// GLOBAL: LEGO1 0x100f7048
Character g_characters[47] = {
	{"pepper", FALSE, 6, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 50, 1},
	{"mama", FALSE, -1, 0, FALSE, FALSE, FALSE, 1500, 20000, FALSE, 0, 2},
	{"papa", FALSE, -1, 0, FALSE, FALSE, FALSE, 1500, 20000, FALSE, 0, 3},
	{"nick", FALSE, 4, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 20, 4},
	{"laura", FALSE, 5, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 20, 5},
	{"brickstr", FALSE, -1, 0, FALSE, FALSE, FALSE, 1000, 20000, FALSE, 0, 6},
	{"studs", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"rhoda", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"valerie", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"snap", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"pt", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"mg", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"bu", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"ml", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"nu", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"na", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"cl", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"en", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"re", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"ro", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"d1", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"d2", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"d3", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"d4", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"l1", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"l2", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"l3", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"l4", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"l5", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"l6", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"b1", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"b2", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"b3", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"b4", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"cm", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"gd", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"rd", FALSE, 2, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 50, 9},
	{"pg", FALSE, 1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 50, 8},
	{"bd", FALSE, 0, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 100, 7},
	{"sy", FALSE, 3, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 100, 10},
	{"gn", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"df", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"bs", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"lt", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"st", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"bm", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0},
	{"jk", FALSE, -1, 0, FALSE, FALSE, TRUE, 1500, 20000, FALSE, 0, 0}
};

// GLOBAL: LEGO1 0x100f74f8
MxS32 g_legoAnimationManagerConfig = 1;

// FUNCTION: LEGO1 0x1005eb50
void LegoAnimationManager::configureLegoAnimationManager(MxS32 p_legoAnimationManagerConfig)
{
	g_legoAnimationManagerConfig = p_legoAnimationManagerConfig;
}

// FUNCTION: LEGO1 0x1005eb60
// FUNCTION: BETA10 0x1003f940
LegoAnimationManager::LegoAnimationManager()
{
	m_unk0x1c = 0;
	m_animState = NULL;
	m_unk0x424 = NULL;

	Init();

	NotificationManager()->Register(this);
	TickleManager()->RegisterClient(this, 10);
}

// FUNCTION: LEGO1 0x1005ed30
// FUNCTION: BETA10 0x1003fa27
LegoAnimationManager::~LegoAnimationManager()
{
	TickleManager()->UnregisterClient(this);

	FUN_10061010(0);

	for (MxS32 i = 0; i < (MxS32) _countof(m_unk0x3c); i++) {
		LegoROI* roi = m_unk0x3c[i].m_roi;

		if (roi != NULL) {
			LegoPathActor* actor = CharacterManager()->GetActor(roi->GetName());

			if (actor != NULL && actor->GetController() != NULL && CurrentWorld() != NULL) {
				CurrentWorld()->FUN_1001fc80((IslePathActor*) actor);
				actor->ClearController();
			}

			CharacterManager()->FUN_10083db0(roi);
		}
	}

	if (m_tranInfoList != NULL) {
		delete m_tranInfoList;
	}

	if (m_tranInfoList2 != NULL) {
		delete m_tranInfoList2;
	}

	DeleteAnimations();

	if (m_unk0x424 != NULL) {
		FUN_10063aa0();
		delete m_unk0x424;
	}

	NotificationManager()->Unregister(this);
}

// FUNCTION: LEGO1 0x1005ee80
// FUNCTION: BETA10 0x1003fbc0
void LegoAnimationManager::Reset(MxBool p_und)
{
	m_unk0x402 = 0;

	if (p_und && m_animState != NULL) {
		m_animState->SetFlag();
	}

	undefined unk0x42b = m_unk0x42b;
	FUN_1005ef10();

	if (m_tranInfoList != NULL) {
		delete m_tranInfoList;
	}

	if (m_tranInfoList2 != NULL) {
		delete m_tranInfoList2;
	}

	DeleteAnimations();
	Init();

	m_unk0x42b = unk0x42b;
	m_unk0x428 = m_unk0x3a;
	m_unk0x429 = m_unk0x400;
	m_unk0x42a = m_unk0x402;
}

// STUB: LEGO1 0x1005ef10
void LegoAnimationManager::FUN_1005ef10()
{
	// TODO
}

// STUB: LEGO1 0x1005f0b0
void LegoAnimationManager::FUN_1005f0b0()
{
	// TODO
}

// FUNCTION: LEGO1 0x1005f130
// FUNCTION: BETA10 0x1003ffb7
void LegoAnimationManager::Init()
{
	m_unk0x402 = 0;
	m_scriptIndex = -1;
	m_animCount = 0;
	m_anims = NULL;
	m_unk0x18 = 0;
	m_unk0x1a = 0;
	m_tranInfoList = NULL;
	m_tranInfoList2 = NULL;
	m_unk0x41c = g_legoAnimationManagerConfig <= 1 ? 10 : 20;

	MxS32 i;
	for (i = 0; i < (MxS32) _countof(m_unk0x28); i++) {
		m_unk0x28[i] = NULL;
		m_unk0x30[i] = 0;
	}

	for (i = 0; i < (MxS32) _countof(m_unk0x3c); i++) {
		m_unk0x3c[i].m_roi = NULL;
		m_unk0x3c[i].m_id = -1;
		m_unk0x3c[i].m_unk0x10 = -1.0f;
		m_unk0x3c[i].m_unk0x14 = 0;
	}

	m_unk0x38 = FALSE;
	m_unk0x39 = FALSE;
	m_unk0x3a = 1;
	m_unk0x3fc = 0;
	m_unk0x400 = 0;
	m_unk0x414 = 0;
	m_unk0x418 = 5;
	m_unk0x0e = 0;
	m_unk0x10 = 0;
	m_unk0x401 = 0;
	m_unk0x42b = 0;
	m_unk0x430 = 0;
	m_unk0x42c = 0;
	m_unk0x408 = m_unk0x40c = m_unk0x404 = Timer()->GetTime();
	m_unk0x410 = 5000;

	for (i = 0; i < (MxS32) _countof(g_characters); i++) {
		g_characters[i].m_active = FALSE;
		g_characters[i].m_unk0x04 = FALSE;
	}

	for (i = 0; i < (MxS32) _countof(g_vehicles); i++) {
		g_vehicles[i].m_unk0x04 = 0;
		g_vehicles[i].m_unk0x05 = FALSE;
	}

	if (m_unk0x424 != NULL) {
		FUN_10063aa0();
		delete m_unk0x424;
	}

	m_unk0x424 = new LegoROIList();
}

// STUB: LEGO1 0x1005f6d0
void LegoAnimationManager::FUN_1005f6d0(MxBool)
{
	// TODO
}

// STUB: LEGO1 0x1005f700
void LegoAnimationManager::FUN_1005f700(MxBool)
{
	// TODO
}

// FUNCTION: LEGO1 0x1005f720
MxResult LegoAnimationManager::LoadScriptInfo(MxS32 p_scriptIndex)
{
	MxResult result = FAILURE;
	MxS32 i, j, k;

	if (m_scriptIndex != p_scriptIndex) {
		if (m_tranInfoList != NULL) {
			delete m_tranInfoList;
			m_tranInfoList = NULL;
		}

		if (m_tranInfoList2 != NULL) {
			delete m_tranInfoList2;
			m_tranInfoList2 = NULL;
		}

		for (i = 0; i < (MxS32) _countof(m_unk0x28); i++) {
			m_unk0x28[i] = NULL;
			m_unk0x30[i] = 0;
		}

		m_unk0x38 = FALSE;
		m_unk0x39 = FALSE;
		m_unk0x430 = 0;
		m_unk0x42c = 0;

		for (j = 0; j < (MxS32) _countof(g_characters); j++) {
			g_characters[j].m_active = FALSE;
		}

		m_animState = (AnimState*) GameState()->GetState("AnimState");
		if (m_animState == NULL) {
			m_animState = (AnimState*) GameState()->CreateState("AnimState");
		}

		if (m_scriptIndex == 0) {
			m_animState->FUN_10065240(m_animCount, m_anims, m_unk0x3fc);
		}

		DeleteAnimations();

		LegoFile file;

		if (p_scriptIndex == -1) {
			result = SUCCESS;
			goto done;
		}

		char filename[128];
		char path[1024];
		sprintf(filename, "lego\\data\\%sinf.dta", Lego()->GetScriptName(p_scriptIndex));
		sprintf(path, "%s", MxOmni::GetHD());

		if (path[strlen(path) - 1] != '\\') {
			strcat(path, "\\");
		}

		strcat(path, filename);

		if (_access(path, 4)) {
			sprintf(path, "%s", MxOmni::GetCD());

			if (path[strlen(path) - 1] != '\\') {
				strcat(path, "\\");
			}

			strcat(path, filename);

			if (_access(path, 4)) {
				goto done;
			}
		}

		if (file.Open(path, LegoFile::c_read) == FAILURE) {
			goto done;
		}

		MxU32 version;
		if (file.Read(&version, sizeof(version)) == FAILURE) {
			goto done;
		}

		if (version != 3) {
			OmniError("World animation version mismatch", 0);
			goto done;
		}

		if (file.Read(&m_animCount, sizeof(m_animCount)) == FAILURE) {
			goto done;
		}

		m_anims = new AnimInfo[m_animCount];
		memset(m_anims, 0, m_animCount * sizeof(*m_anims));

		for (j = 0; j < m_animCount; j++) {
			if (ReadAnimInfo(&file, &m_anims[j]) == FAILURE) {
				goto done;
			}

			m_anims[j].m_unk0x28 = GetCharacterIndex(m_anims[j].m_animName + strlen(m_anims[j].m_animName) - 2);
			m_anims[j].m_unk0x29 = 0;

			for (k = 0; k < 3; k++) {
				m_anims[j].m_unk0x2a[k] = -1;
			}

			if (m_anims[j].m_unk0x08 == -1) {
				for (MxS32 l = 0; l < m_anims[j].m_modelCount; l++) {
					MxS32 index = GetCharacterIndex(m_anims[j].m_models[l].m_modelName);

					if (index >= 0) {
						g_characters[index].m_active = TRUE;
					}
				}
			}

			MxS32 count = 0;
			for (MxS32 m = 0; m < m_anims[j].m_modelCount; m++) {
				MxU32 n;

				if (FindVehicle(m_anims[j].m_models[m].m_modelName, n) && m_anims[j].m_models[m].m_unk0x2c) {
					m_anims[j].m_unk0x2a[count++] = n;
					if (count > 3) {
						break;
					}
				}
			}
		}

		m_scriptIndex = p_scriptIndex;
		m_tranInfoList = new LegoTranInfoList();
		m_tranInfoList2 = new LegoTranInfoList();

		FUN_100617c0(-1, m_unk0x0e, m_unk0x10);

		result = SUCCESS;
		m_unk0x402 = 1;

		if (m_unk0x42b) {
			m_unk0x428 = m_unk0x3a;
			m_unk0x429 = m_unk0x400;
			m_unk0x42a = 1;
			m_unk0x3a = 0;
			m_unk0x400 = 0;
			m_unk0x402 = 0;
		}

		if (p_scriptIndex == 0) {
			m_animState->FUN_100651d0(m_animCount, m_anims, m_unk0x3fc);
		}
	}

done:
	if (result == FAILURE) {
		DeleteAnimations();
	}

	return result;
}

// FUNCTION: LEGO1 0x10060140
MxBool LegoAnimationManager::FindVehicle(const char* p_name, MxU32& p_index)
{
	for (MxS32 i = 0; i < _countof(g_vehicles); i++) {
		if (!strcmpi(p_name, g_vehicles[i].m_name)) {
			p_index = i;
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGO1 0x10060180
MxResult LegoAnimationManager::ReadAnimInfo(LegoFile* p_file, AnimInfo* p_info)
{
	MxResult result = FAILURE;
	MxU8 length;
	MxS32 i, j;

	if (p_file->Read(&length, sizeof(length)) == FAILURE) {
		goto done;
	}

	p_info->m_animName = new char[length + 1];
	if (p_file->Read(p_info->m_animName, length) == FAILURE) {
		goto done;
	}

	p_info->m_animName[length] = 0;
	if (p_file->Read(&p_info->m_objectId, sizeof(p_info->m_objectId)) == FAILURE) {
		goto done;
	}

	if (p_file->Read(&p_info->m_unk0x08, sizeof(p_info->m_unk0x08)) == FAILURE) {
		goto done;
	}
	if (p_file->Read(&p_info->m_unk0x0a, sizeof(p_info->m_unk0x0a)) == FAILURE) {
		goto done;
	}
	if (p_file->Read(&p_info->m_unk0x0b, sizeof(p_info->m_unk0x0b)) == FAILURE) {
		goto done;
	}
	if (p_file->Read(&p_info->m_unk0x0c, sizeof(p_info->m_unk0x0c)) == FAILURE) {
		goto done;
	}
	if (p_file->Read(&p_info->m_unk0x0d, sizeof(p_info->m_unk0x0d)) == FAILURE) {
		goto done;
	}

	for (i = 0; i < (MxS32) _countof(p_info->m_unk0x10); i++) {
		if (p_file->Read(&p_info->m_unk0x10[i], sizeof(*p_info->m_unk0x10)) != SUCCESS) {
			goto done;
		}
	}

	if (p_file->Read(&p_info->m_modelCount, sizeof(p_info->m_modelCount)) == FAILURE) {
		goto done;
	}

	p_info->m_models = new ModelInfo[p_info->m_modelCount];
	memset(p_info->m_models, 0, p_info->m_modelCount * sizeof(*p_info->m_models));

	for (j = 0; j < p_info->m_modelCount; j++) {
		if (ReadModelInfo(p_file, &p_info->m_models[j]) == FAILURE) {
			goto done;
		}
	}

	result = SUCCESS;

done:
	return result;
}

// FUNCTION: LEGO1 0x10060310
MxResult LegoAnimationManager::ReadModelInfo(LegoFile* p_file, ModelInfo* p_info)
{
	MxResult result = FAILURE;
	MxU8 length;

	if (p_file->Read(&length, 1) == FAILURE) {
		goto done;
	}

	p_info->m_modelName = new char[length + 1];
	if (p_file->Read(p_info->m_modelName, length) == FAILURE) {
		goto done;
	}

	p_info->m_modelName[length] = 0;
	if (p_file->Read(&p_info->m_unk0x04, sizeof(p_info->m_unk0x04)) == FAILURE) {
		goto done;
	}

	if (p_file->Read(p_info->m_location, sizeof(p_info->m_location)) != SUCCESS) {
		goto done;
	}
	if (p_file->Read(p_info->m_direction, sizeof(p_info->m_direction)) != SUCCESS) {
		goto done;
	}
	if (p_file->Read(p_info->m_up, sizeof(p_info->m_up)) != SUCCESS) {
		goto done;
	}
	if (p_file->Read(&p_info->m_unk0x2c, sizeof(p_info->m_unk0x2c)) == FAILURE) {
		goto done;
	}

	result = SUCCESS;

done:
	return result;
}

// FUNCTION: LEGO1 0x100603c0
void LegoAnimationManager::DeleteAnimations()
{
	undefined unk0x42b = m_unk0x42b;

	if (m_anims != NULL) {
		for (MxS32 i = 0; i < m_animCount; i++) {
			delete m_anims[i].m_animName;

			if (m_anims[i].m_models != NULL) {
				for (MxS32 j = 0; j < m_anims[i].m_modelCount; j++) {
					delete m_anims[i].m_models[j].m_modelName;
				}

				delete m_anims[i].m_models;
			}
		}

		delete m_anims;
	}

	Init();
	m_unk0x42b = unk0x42b;
}

// STUB: LEGO1 0x10060570
void LegoAnimationManager::FUN_10060570(MxBool)
{
	// TODO
}

// STUB: LEGO1 0x100605e0
// FUNCTION: BETA10 0x1004152b
MxResult LegoAnimationManager::FUN_100605e0(
	MxU32 p_index,
	MxU8 p_unk0x0a,
	MxMatrix* p_matrix,
	undefined,
	undefined4,
	undefined,
	MxBool,
	MxBool,
	undefined
)
{
	// TODO
	return FAILURE;
}

// FUNCTION: LEGO1 0x100609f0
// FUNCTION: BETA10 0x10041a38
MxResult LegoAnimationManager::FUN_100609f0(MxU32 p_objectId, MxMatrix* p_matrix, MxBool p_und1, MxBool p_und2)
{
	MxResult result = FAILURE;
	MxDSAction action;

	FUN_100627d0(FALSE);

	LegoTranInfo* info = new LegoTranInfo();
	info->m_unk0x00 = 0;
	info->m_index = ++m_unk0x1c;
	info->m_unk0x10 = 0;
	info->m_unk0x08 = NULL;
	info->m_unk0x12 = -1;
	info->m_unk0x14 = 0;
	info->m_objectId = p_objectId;

	if (p_matrix != NULL) {
		info->m_unk0x0c = new MxMatrix(*p_matrix);
	}

	FUN_10062770();

	info->m_unk0x1c = m_unk0x28;
	info->m_unk0x20 = m_unk0x30;
	info->m_unk0x28 = p_und1;
	info->m_unk0x29 = p_und2;

	if (m_tranInfoList != NULL) {
		m_tranInfoList->Append(info);
	}

	char buf[256];
	sprintf(buf, "%s:%d", g_strANIMMAN_ID, info->m_index);

	action.SetAtomId(*Lego()->GetScriptAtom(m_scriptIndex));
	action.SetObjectId(p_objectId);
	action.SetUnknown24(-1);
	action.AppendExtra(strlen(buf) + 1, buf);

	if (StartActionIfUnknown0x13c(action) == SUCCESS) {
		BackgroundAudioManager()->LowerVolume();
		info->m_flags |= LegoTranInfo::c_bit2;
		m_unk0x39 = TRUE;
		m_unk0x404 = Timer()->GetTime();
		result = SUCCESS;
	}

	return result;
}

// FUNCTION: LEGO1 0x10060d00
MxResult LegoAnimationManager::StartEntityAction(MxDSAction& p_dsAction, LegoEntity* p_entity)
{
	MxResult result = FAILURE;
	LegoROI* roi = p_entity->GetROI();

	if (p_entity->GetType() == LegoEntity::e_character) {
		LegoPathActor* actor = CharacterManager()->GetActor(roi->GetName());

		if (actor) {
			LegoPathController* controller = actor->GetController();

			if (controller) {
				controller->FUN_10046770(actor);
				actor->ClearController();

				for (MxS32 i = 0; i < (MxS32) _countof(m_unk0x3c); i++) {
					if (m_unk0x3c[i].m_roi == roi) {
						MxU32 characterId = m_unk0x3c[i].m_id;
						g_characters[characterId].m_unk0x07 = TRUE;
						MxS32 vehicleId = g_characters[characterId].m_vehicleId;

						if (vehicleId >= 0) {
							g_vehicles[vehicleId].m_unk0x05 = FALSE;
						}
						break;
					}
				}
			}
		}
	}

	if (StartActionIfUnknown0x13c(p_dsAction) == SUCCESS) {
		result = SUCCESS;
	}

	return result;
}

// FUNCTION: LEGO1 0x10060dc0
// FUNCTION: BETA10 0x10041f2c
MxResult LegoAnimationManager::FUN_10060dc0(
	IsleScript::Script p_objectId,
	MxMatrix* p_matrix,
	undefined p_param3,
	undefined p_param4,
	undefined4 p_param5,
	undefined p_param6,
	MxBool p_param7,
	MxBool p_param8,
	undefined p_param9
)
{
	MxResult result = FAILURE;
	MxBool found = FALSE;

	if (!Lego()->m_unk0x13c) {
		return SUCCESS;
	}

	for (MxS32 i = 0; i < m_animCount; i++) {
		if (m_anims[i].m_objectId == p_objectId) {
			found = TRUE;
			undefined unk0x0a;

			switch (p_param4) {
			case 0:
				unk0x0a = m_anims[i].m_unk0x0a;
				break;
			case 1:
				unk0x0a = 1;
				break;
			default:
				unk0x0a = 0;
				break;
			}

			result = FUN_100605e0(i, unk0x0a, p_matrix, p_param3, p_param5, p_param6, p_param7, p_param8, p_param9);
			break;
		}
	}

	if (!found && p_param3 != 0) {
		result = FUN_100609f0(p_objectId, p_matrix, p_param7, p_param8);
	}

	return result;
}

// STUB: LEGO1 0x10061010
void LegoAnimationManager::FUN_10061010(undefined4)
{
	// TODO
}

// STUB: LEGO1 0x100617c0
void LegoAnimationManager::FUN_100617c0(MxS32, MxU16&, MxU16&)
{
	// TODO
}

// FUNCTION: LEGO1 0x100618f0
// FUNCTION: BETA10 0x100425f0
LegoTranInfo* LegoAnimationManager::GetTranInfo(MxU32 p_index)
{
	if (m_tranInfoList != NULL) {
		LegoTranInfoListCursor cursor(m_tranInfoList);
		LegoTranInfo* tranInfo;

		while (cursor.Next(tranInfo)) {
			if (tranInfo->m_index == p_index) {
				return tranInfo;
			}
		}
	}

	return NULL;
}

// STUB: LEGO1 0x100619f0
MxLong LegoAnimationManager::Notify(MxParam& p_param)
{
	// TODO
	return 0;
}

// STUB: LEGO1 0x10061cc0
MxResult LegoAnimationManager::Tickle()
{
	// TODO
	return SUCCESS;
}

// FUNCTION: LEGO1 0x10062360
// FUNCTION: BETA10 0x100432dd
MxS8 LegoAnimationManager::GetCharacterIndex(const char* p_name)
{
	MxS8 i;

	for (i = 0; i < _countof(g_characters); i++) {
		if (!strnicmp(p_name, g_characters[i].m_name, 2)) {
			return i;
		}
	}

	return -1;
}

// FUNCTION: LEGO1 0x10062770
// FUNCTION: BETA10 0x1004381a
void LegoAnimationManager::FUN_10062770()
{
	if (!m_unk0x38) {
		LegoWorld* world = CurrentWorld();

		if (world != NULL) {
			m_unk0x28[1] = (MxPresenter*) world->Find("MxSoundPresenter", "TransitionSound1");
			m_unk0x28[0] = (MxPresenter*) world->Find("MxSoundPresenter", "TransitionSound2");
			m_unk0x30[1] = 200;
			m_unk0x30[0] = 750;
			m_unk0x38 = TRUE;
		}
	}
}

// STUB: LEGO1 0x100627d0
void LegoAnimationManager::FUN_100627d0(MxBool)
{
	// TODO
}

// STUB: LEGO1 0x100629b0
void LegoAnimationManager::FUN_100629b0(MxU32, MxBool)
{
	// TODO
}

// STUB: LEGO1 0x10063270
void LegoAnimationManager::FUN_10063270(LegoROIList*, LegoAnimPresenter*)
{
	// TODO
}

// FUNCTION: LEGO1 0x10063780
void LegoAnimationManager::FUN_10063780(LegoROIList* p_list)
{
	if (p_list != NULL && m_unk0x424 != NULL) {
		LegoROIListCursor cursor(p_list);
		LegoROI* roi;

		while (cursor.Next(roi)) {
			const char* name = roi->GetName();

			if (CharacterManager()->Exists(name)) {
				m_unk0x424->Append(roi);
				cursor.Detach();
			}
		}
	}
}

// FUNCTION: LEGO1 0x10063aa0
void LegoAnimationManager::FUN_10063aa0()
{
	LegoROIListCursor cursor(m_unk0x424);
	LegoROI* roi;

	while (cursor.Next(roi)) {
		CharacterManager()->FUN_10083db0(roi);
	}
}

// STUB: LEGO1 0x10064670
void LegoAnimationManager::FUN_10064670(MxBool)
{
	// TODO
}

// STUB: LEGO1 0x10064740
void LegoAnimationManager::FUN_10064740(MxBool)
{
	// TODO
}
