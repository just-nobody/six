/**
 * Copyright (c) 2006-2017 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#include "common/config.h"

#include <algorithm>

#include "Sound.h"

#include "VorbisDecoder.h"
#include "WaveDecoder.h"
//#include "FLACDecoder.h"

#ifdef LOVE_SUPPORT_COREAUDIO
#	include "CoreAudioDecoder.h"
#endif

namespace love
{
namespace sound
{
namespace lullaby
{

Sound::Sound()
{
}

Sound::~Sound()
{
}

const char *Sound::getName() const
{
	return "love.sound.lullaby";
}

sound::Decoder *Sound::newDecoder(love::filesystem::FileData *data, int bufferSize)
{
	std::string ext = data->getExtension();
	std::transform(ext.begin(), ext.end(), ext.begin(), tolower);

	sound::Decoder *decoder = nullptr;

	// Find a suitable decoder here, and return it.
	if (false)
		/* nothing */;
	else if (VorbisDecoder::accepts(ext))
		decoder = new VorbisDecoder(data, ext, bufferSize);
#ifdef LOVE_SUPPORT_COREAUDIO
	else if (CoreAudioDecoder::accepts(ext))
		decoder = new CoreAudioDecoder(data, ext, bufferSize);
#endif
	else if (WaveDecoder::accepts(ext))
		decoder = new WaveDecoder(data, ext, bufferSize);
	/*else if (FLACDecoder::accepts(ext))
		decoder = new FLACDecoder(data, ext, bufferSize);*/

	// else if (OtherDecoder::accept(ext))

	return decoder;
}

} // lullaby
} // sound
} // love
