#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "Misc/AES.h"

#include "Misc/Guid.h"
#include "PakFileEntry.h"

class FExtractThreadWorker : public FRunnable
{
public:
	FExtractThreadWorker();
	~FExtractThreadWorker();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	void Shutdown();
	void EnsureCompletion();
	void StartExtract(const FString& InPakFile, int32 InPakVersion, const FAES::FAESKey& InKey, const FString& InOutputPath);
	void InitTaskFiles(TArray<FPakFileEntry>& InFiles);

protected:
	bool BufferedCopyFile(FArchive& Dest, FArchive& Source, const FPakEntry& Entry, void* Buffer, int64 BufferSize, const FAES::FAESKey& InKey);
	bool UncompressCopyFile(FArchive& Dest, FArchive& Source, const FPakEntry& Entry, uint8*& PersistentBuffer, int64& BufferSize, const FAES::FAESKey& InKey, FName InCompressionMethod, bool bHasRelativeCompressedChunkOffsets);


protected:
	class FRunnableThread* Thread;
	FGuid Guid;
	FThreadSafeCounter StopTaskCounter;

	TArray<FPakFileEntry> Files;

	FString PakFilePath;
	int32 PakVersion;
	FAES::FAESKey AESKey;
	FString OutputPath;
};
