#include "Common/Log.h"
#include "Core/MemMapHelpers.h"
#include "Core/HLE/HLE.h"
#include "Core/HLE/FunctionWrappers.h"
#include "Core/HLE/AtracCtx2.h"
#include "Core/HW/Atrac3Standalone.h"

// Convenient command line:
// Windows\x64\debug\PPSSPPHeadless.exe  --root pspautotests/tests/../ -o --compare --timeout=30 --graphics=software pspautotests/tests/audio/atrac/... --ignore pspautotests/tests/audio/atrac/second/resetting.prx --ignore pspautotests/tests/audio/atrac/second/replay.prx
//
// See the big comment in sceAtrac.cpp for an overview of the different modes of operation.
//
// Test cases
//
// Halfway buffer
//
// * None found yet
//
// All-data-loaded
//
// * MotoGP (menu music with specified loop). Simple repeated calls to sceAtracDecodeData
// * Archer MacLean's Mercury (in-game, not menu)
// * Crisis Core
//
// Streaming
//
// - Good ones (early)
//   * Everybody's Golf 2 (0x2000 buffer size, loop from end)
//   * Burnout Legends (no loop, 0x1800 buffer size)
//   * Suicide Barbie
// - Others
//   * Bleach
//   * God of War: Chains of Olympus
//   * Ape Academy 2 (bufsize 8192)
//   * Half Minute Hero (bufsize 65536)
//   * Flatout (tricky! needs investigation)

Atrac2::Atrac2(int codecType) {
	track_.codecType = codecType;
}

void Atrac2::DoState(PointerWrap &p) {
	_assert_msg_(false, "Savestates not yet support with new Atrac implementation.\n\nTurn it off in Developer settings.\n\n");
}

void Atrac2::WriteContextToPSPMem() {
}

int Atrac2::Analyze(const Track &track, u32 addr, u32 size) {
	return 0;
}

int Atrac2::AnalyzeAA3(const Track &track, u32 addr, u32 size, u32 filesize) {
	return 0;
}

int Atrac2::RemainingFrames() const {
	return 0;
}

u32 Atrac2::SecondBufferSize() const {
	return 0;
}

void Atrac2::GetStreamDataInfo(u32 *writePtr, u32 *writableBytes, u32 *readOffset) {

}

int Atrac2::AddStreamData(u32 bytesToAdd) {
	return 0;
}

u32 Atrac2::AddStreamDataSas(u32 bufPtr, u32 bytesToAdd) {
	return 0;
}

int Atrac2::ResetPlayPosition(int sample, int bytesWrittenFirstBuf, int bytesWrittenSecondBuf, bool *delay) {
	*delay = false;
	return 0;
}

int Atrac2::GetResetBufferInfo(AtracResetBufferInfo *bufferInfo, int sample) {
	return 0;
}

int Atrac2::GetSoundSample(int *endSample, int *loopStartSample, int *loopEndSample) const {
	return 0;
}

int Atrac2::SetData(u32 buffer, u32 readSize, u32 bufferSize, int outputChannels) {
	if (readSize == bufferSize) {
		bufferState_ = ATRAC_STATUS_ALL_DATA_LOADED;
	} else {
		bufferState_ = ATRAC_STATUS_HALFWAY_BUFFER;
	}
	return hleLogDebug(Log::ME, 0);
}

u32 Atrac2::SetSecondBuffer(u32 secondBuffer, u32 secondBufferSize) {
	return 0;
}

u32 Atrac2::DecodeData(u8 *outbuf, u32 outbufPtr, u32 *SamplesNum, u32 *finish, int *remains) {

	return 0;
}

u32 Atrac2::GetNextSamples() {
	return 0;
}

void Atrac2::InitLowLevel(u32 paramsAddr, bool jointStereo) {
	track_.AnalyzeReset();
	track_.channels = Memory::Read_U32(paramsAddr);
	outputChannels_ = Memory::Read_U32(paramsAddr + 4);
	track_.bytesPerFrame = Memory::Read_U32(paramsAddr + 8);
	if (track_.codecType == PSP_MODE_AT_3) {
		track_.bitrate = (track_.bytesPerFrame * 352800) / 1000;
		track_.bitrate = (track_.bitrate + 511) >> 10;
		track_.jointStereo = false;
	} else if (track_.codecType == PSP_MODE_AT_3_PLUS) {
		track_.bitrate = (track_.bytesPerFrame * 352800) / 1000;
		track_.bitrate = ((track_.bitrate >> 11) + 8) & 0xFFFFFFF0;
		track_.jointStereo = false;
	}
	track_.dataByteOffset = 0;
	bufferState_ = ATRAC_STATUS_LOW_LEVEL;
	currentSample_ = 0;
	CreateDecoder();
	WriteContextToPSPMem();
}

int Atrac2::DecodeLowLevel(const u8 *srcData, int *bytesConsumed, s16 *dstData, int *bytesWritten) {
	return 0;
}
