#include "../../Runtime/System/Misc.h"
#include "AudioSource.h"

// コンストラクタ
AudioSource::AudioSource(IXAudio2* xaudio, std::shared_ptr<AudioResource>& resource)
	: resource(resource)
{
	HRESULT hr;

	// ソースボイスを生成
	hr = xaudio->CreateSourceVoice(&sourceVoice, &resource->GetWaveFormat());
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
}

// デストラクタ
AudioSource::~AudioSource()
{
	if (sourceVoice != nullptr)
	{
		sourceVoice->DestroyVoice();
		sourceVoice = nullptr;
	}
}

// 再生
void AudioSource::Play(bool loop)
{
	// ソースボイスにデータを送信
	XAUDIO2_BUFFER buffer = { 0 };
	buffer.AudioBytes = resource->GetAudioBytes();
	buffer.pAudioData = resource->GetAudioData();
	buffer.LoopCount = loop ? XAUDIO2_LOOP_INFINITE : 0;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	
	sourceVoice->SubmitSourceBuffer(&buffer);

	HRESULT hr = sourceVoice->Start();
	_ASSERT_EXPR(SUCCEEDED(hr), HRTrace(hr));
	sourceVoice->SetVolume(1.0f);
}

// 停止
void AudioSource::Stop()
{
	sourceVoice->Stop();
}
