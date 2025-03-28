#pragma once

#include <cstdint>

#include "Core/HLE/AtracCtx.h"

class Atrac2 : public AtracBase {
public:
	Atrac2(int atracID, u32 contextAddr, int codecType);

	void DoState(PointerWrap &p) override;

	int GetID() const override { return 0; }

	int GetNextDecodePosition(int *pos) const { return 0; }
	int RemainingFrames() const override;
	int LoopStatus() const override { return 0; }
	int Bitrate() const override { return 0; }
	int LoopNum() const override { return 0; }
	int SamplesPerFrame() const override { return 0; }
	int Channels() const override { return 2; }
	int BytesPerFrame() const override { return 0; }
	int SetLoopNum(int loopNum) override { return 0; }

	void GetStreamDataInfo(u32 *writePtr, u32 *writableBytes, u32 *readOffset) override;
	int AddStreamData(u32 bytesToAdd) override;
	u32 AddStreamDataSas(u32 bufPtr, u32 bytesToAdd) override;
	int ResetPlayPosition(int sample, int bytesWrittenFirstBuf, int bytesWrittenSecondBuf, bool *delay) override;
	int GetResetBufferInfo(AtracResetBufferInfo *bufferInfo, int sample) override;
	int SetData(const Track &track, u32 buffer, u32 readSize, u32 bufferSize, int outputChannels) override;
	u32 SetSecondBuffer(u32 secondBuffer, u32 secondBufferSize) override;
	u32 SecondBufferSize() const override;

	u32 DecodeData(u8 *outbuf, u32 outbufPtr, u32 *SamplesNum, u32 *finish, int *remains) override;
	int DecodeLowLevel(const u8 *srcData, int *bytesConsumed, s16 *dstData, int *bytesWritten) override;
	u32 GetNextSamples() override;
	void InitLowLevel(u32 paramsAddr, bool jointStereo, int codecType) override;

	int GetSoundSample(int *endSample, int *loopStartSample, int *loopEndSample) const override;

	// These will not be used by the new implementation.
	void UpdateContextFromPSPMem() override {}
	void NotifyGetContextAddress() override {}

private:
	int currentSample_ = 0;
};
