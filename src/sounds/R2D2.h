//
// https://www.soundboard.com/sb/r2d2_r2_d2_sounds
//

#define SAMPLE_RATE 8000

#include "R2D2-Cheerful.h"
#include "R2D2-Concerned.h"
#include "R2D2-Determined.h"
#include "R2D2-Eureka.h"
#include "R2D2-Look.h"
#include "R2D2-Playful.h"
#include "R2D2-Processing.h"
#include "R2D2-Sad.h"
#include "R2D2-Snappy.h"
#include "R2D2-Surprised.h"
#include "R2D2-Unbelievable.h"
#include "R2D2-Very-Excited.h"
#include "R2D2-Whistle.h"

#define R2D2_CHEERFUL 0
#define R2D2_CONCERNED 1
#define R2D2_DETERMINED 2
#define R2D2_EUREKA 3
#define R2D2_LOOK 4
#define R2D2_PLAYFUL 5
#define R2D2_PROCESSING 6
#define R2D2_SAD 7
#define R2D2_SNAPPY 8
#define R2D2_SURPRISED 9
#define R2D2_UNBELIEVABLE 10
#define R2D2_VERY_EXCITED 11
#define R2D2_WHISTLE 12

#define R2D2_COUNT 13

const uint8_t *waveDataArray[] = {
	r2d2_cheerful,
	r2d2_concerned,
	r2d2_determined,
	r2d2_eureka,
	r2d2_look,
	r2d2_playful,
	r2d2_processing,
	r2d2_sad,
	r2d2_snappy,
	r2d2_surprised,
	r2d2_unbelievable,
	r2d2_very_excited,
	r2d2_whistle,
};

const uint16_t waveDataSizeArray[] = {
	sizeof(r2d2_cheerful),
	sizeof(r2d2_concerned),
	sizeof(r2d2_determined),
	sizeof(r2d2_eureka),
	sizeof(r2d2_look),
	sizeof(r2d2_playful),
	sizeof(r2d2_processing),
	sizeof(r2d2_sad),
	sizeof(r2d2_snappy),
	sizeof(r2d2_surprised),
	sizeof(r2d2_unbelievable),
	sizeof(r2d2_very_excited),
	sizeof(r2d2_whistle),
};
