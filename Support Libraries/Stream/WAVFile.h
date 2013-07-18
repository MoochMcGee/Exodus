#include "Stream.h"
#ifndef __WAVFILE_H__
#define __WAVFILE_H__
#include <string>
#include "WindowFunctions/WindowFunctions.pkg"
namespace Stream {

class WAVFile :public Stream<IStreamNonSeekable>
{
public:
	//Enumerations
	enum OpenMode;
	enum CreateMode;

	//Make sure the WAVFile object is non-copyable
	protected: WAVFile(const WAVFile& object) {} public:

	//Constructors
	inline WAVFile();
	virtual ~WAVFile();

	//Data format
	inline bool GetDataFormat(unsigned int& channelCount, unsigned int& bitsPerSample, unsigned int& samplesPerSec) const;
	inline void SetDataFormat(unsigned int channelCount, unsigned int bitsPerSample, unsigned int samplesPerSec);
	inline unsigned int GetSavedSampleCount() const;

	//File binding
	inline bool Open(const std::string& filename, OpenMode openMode, CreateMode createMode, unsigned int abufferSize = 8192);
	inline bool Open(const std::wstring& filename, OpenMode openMode, CreateMode createMode, unsigned int abufferSize = 8192);
	inline void Close();
	inline bool IsOpen() const;

	//File position
	virtual bool IsAtEnd() const;
	virtual bool SkipBytes(SizeType byteCount);

protected:
	using Stream::ReadBinaryNativeByteOrder;
	using Stream::WriteBinaryNativeByteOrder;

	//Native byte order read functions
	virtual bool ReadBinaryNativeByteOrder(char& data);
	virtual bool ReadBinaryNativeByteOrder(signed char& data);
	virtual bool ReadBinaryNativeByteOrder(unsigned char& data);
	virtual bool ReadBinaryNativeByteOrder(wchar_t& data);
	virtual bool ReadBinaryNativeByteOrder(short& data);
	virtual bool ReadBinaryNativeByteOrder(unsigned short& data);
	virtual bool ReadBinaryNativeByteOrder(int& data);
	virtual bool ReadBinaryNativeByteOrder(unsigned int& data);
	virtual bool ReadBinaryNativeByteOrder(long& data);
	virtual bool ReadBinaryNativeByteOrder(unsigned long& data);
	virtual bool ReadBinaryNativeByteOrder(long long& data);
	virtual bool ReadBinaryNativeByteOrder(unsigned long long& data);
	virtual bool ReadBinaryNativeByteOrder(float& data);
	virtual bool ReadBinaryNativeByteOrder(double& data);
	virtual bool ReadBinaryNativeByteOrder(long double& data);

	//Native byte order array read functions
	virtual bool ReadBinaryNativeByteOrder(char* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(signed char* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(unsigned char* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(wchar_t* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(short* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(unsigned short* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(int* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(unsigned int* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(long* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(unsigned long* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(long long* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(unsigned long long* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(float* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(double* data, SizeType length);
	virtual bool ReadBinaryNativeByteOrder(long double* data, SizeType length);

	//Native byte order write functions
	virtual bool WriteBinaryNativeByteOrder(char data);
	virtual bool WriteBinaryNativeByteOrder(signed char data);
	virtual bool WriteBinaryNativeByteOrder(unsigned char data);
	virtual bool WriteBinaryNativeByteOrder(wchar_t data);
	virtual bool WriteBinaryNativeByteOrder(short data);
	virtual bool WriteBinaryNativeByteOrder(unsigned short data);
	virtual bool WriteBinaryNativeByteOrder(int data);
	virtual bool WriteBinaryNativeByteOrder(unsigned int data);
	virtual bool WriteBinaryNativeByteOrder(long data);
	virtual bool WriteBinaryNativeByteOrder(unsigned long data);
	virtual bool WriteBinaryNativeByteOrder(long long data);
	virtual bool WriteBinaryNativeByteOrder(unsigned long long data);
	virtual bool WriteBinaryNativeByteOrder(float data);
	virtual bool WriteBinaryNativeByteOrder(double data);
	virtual bool WriteBinaryNativeByteOrder(long double data);

	//Native byte order array write functions
	virtual bool WriteBinaryNativeByteOrder(const char* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const signed char* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const unsigned char* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const wchar_t* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const short* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const unsigned short* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const int* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const unsigned int* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const long* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const unsigned long* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const long long* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const unsigned long long* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const float* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const double* data, SizeType length);
	virtual bool WriteBinaryNativeByteOrder(const long double* data, SizeType length);

private:
	//String conversion functions
	static std::wstring ConvertStringToWString(const std::string& source);

	//Internal read/write functions
	inline bool ReadBinary(void* rawData, unsigned int bytesToRead);
	inline bool WriteBinary(const void* rawData, unsigned int bytesToWrite);
	inline bool WriteBinaryUnbuffered(const void* rawData, unsigned int bytesToWrite);

	//Data buffer functions
	inline bool EmptyDataBuffer();

private:
	//File handling
	bool fileOpen;
	HMMIO mmioHandle;
	MMCKINFO riffChunk;
	MMCKINFO fmtChunk;
	MMCKINFO dataChunk;
	WAVEFORMATEX waveHeader;
	bool waveHeaderLoaded;
	unsigned int savedSampleCount;

	//Data buffering
	unsigned char* fileBuffer;
	unsigned int bufferSize;
	unsigned int bufferPosOffset;
	unsigned int bytesRemainingInBuffer;
};

} //Close namespace Stream
#include "WAVFile.inl"
#endif
