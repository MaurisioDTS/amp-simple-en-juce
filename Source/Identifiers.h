#pragma once

namespace IDs {

	#define DECLARE_ID(name) const String name (#name);

	DECLARE_ID(inputVolume)			// Input volume of the effects chain
	DECLARE_ID(outputVolume)		// Output volume of the effects chain
	DECLARE_ID(selector)			// El selector de tipo de distorsin.
	DECLARE_ID(bypass)				// el botón de bypass.

	#undef DECLARE_ID

}