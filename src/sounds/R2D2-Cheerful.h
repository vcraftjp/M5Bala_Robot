#include <M5Stack.h>

const uint8_t r2d2_cheerful[] PROGMEM = {129,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,127,128,
	129,128,128,129,128,128,128,128,128,128,128,128,128,127,128,129,128,128,128,127,126,132,135,116,119,153,118,114,164,105,105,171,
	109,102,174,113, 97,173,115, 92,174,120, 90,175,123, 86,169,131, 84,168,138, 78,163,146, 75,156,157, 75,148,165, 75,138,168, 78,
	134,172, 80,129,175, 84,123,177, 87,114,181, 94,106,182,101, 98,182,110, 89,179,121, 83,176,130, 77,172,140, 71,168,150, 67,163,
	157, 65,158,164, 65,151,170, 65,139,178, 72,127,186, 78,115,190, 84,106,192, 91, 97,195, 99, 87,193,109, 82,190,117, 77,184,128,
	 74,176,138, 72,169,148, 71,159,157, 70,151,165, 70,144,173, 72,136,179, 75,124,185, 79,115,190, 85,106,191, 91,101,192, 96, 91,
	192,107, 84,190,116, 77,188,124, 72,184,132, 68,178,143, 65,169,154, 64,163,160, 63,155,168, 65,145,175, 68,136,180, 72,128,185,
	 77,116,190, 85,106,191, 92, 97,191,103, 88,188,112, 81,186,123, 76,182,132, 71,176,139, 69,170,148, 68,165,155, 68,158,160, 68,
	151,166, 69,142,173, 74,136,176, 76,128,179, 80,120,182, 85,116,184, 88,112,183, 93,106,183, 98, 99,184,106, 94,182,116, 87,176,
	125, 81,174,133, 77,170,141, 75,163,148, 74,156,158, 73,147,165, 75,137,175, 79,125,179, 84,113,183, 93,105,186,102, 97,184,108,
	 88,182,117, 82,180,126, 78,176,139, 73,167,143, 71,164,151, 71,158,160, 72,147,167, 74,133,177, 77,125,180, 81,120,184, 88,109,
	186, 89,106,186, 94,102,185,105, 92,185,115, 83,180,124, 78,179,136, 69,171,148, 68,165,157, 64,156,162, 65,150,171, 69,142,178,
	 71,127,183, 77,116,188, 85,110,190, 91,103,191, 96, 94,188,101, 92,192,109, 85,189,115, 80,183,125, 76,176,139, 73,165,152, 69,
	158,161, 69,147,168, 72,136,178, 74,131,182, 76,120,186, 87,106,186, 97, 99,187,104, 90,186,113, 85,182,123, 78,175,136, 76,170,
	145, 72,159,152, 70,151,162, 75,144,171, 76,135,175, 78,125,179, 83,115,182, 91,111,187, 96, 94,187,106, 88,186,115, 84,184,119,
	 81,181,124, 78,177,133, 73,173,141, 74,166,149, 73,156,158, 71,149,165, 74,142,169, 79,134,173, 79,127,177, 85,121,178, 87,113,
	183, 95,105,183, 99, 95,181,112, 92,179,123, 85,172,133, 77,164,144, 75,160,154, 75,150,164, 78,139,169, 76,126,181, 86,114,186,
	 93,101,189, 98, 92,190,104, 89,190,112, 82,188,121, 74,186,125, 70,182,137, 66,176,149, 63,169,155, 62,161,163, 61,152,175, 64,
	141,179, 67,133,185, 72,122,187, 77,115,192, 86,107,192, 93, 94,189,104, 87,188,118, 81,182,130, 74,173,142, 70,161,155, 68,154,
	168, 73,141,171, 75,131,176, 79,124,183, 83,117,184, 87,113,182, 94,102,182,103, 98,182,109, 97,174,121, 89,166,131, 87,166,133,
	 85,164,142, 83,152,147, 87,147,153, 88,137,157, 94,134,161, 96,122,158,100,119,162,110,117,162,114,110,155,118,106,152,125,106,
	151,130,109,151,136,100,137,136,108,139,138,112,134,143,112,126,146,109,126,147,110,128,144,118,126,145,116,122,141,118,124,135,
	129,121,137,129,117,142,129,113,137,135,115,135,134,113,134,139,115,131,137,112,127,142,119,128,145,121,120,139,119,117,140,126,
	119,141,130,117,139,132,114,137,132,110,131,140,119,133,135,118,128,136,119,122,140,124,120,143,125,118,142,125,118,137,126,115,
	139,130,118,138,132,121,129,135,118,129,137,114,130,142,117,125,141,116,125,144,117,121,143,119,122,147,122,117,143,121,114,141,
	126,116,145,130,113,141,131,112,136,134,111,134,137,112,135,142,115,128,138,114,129,140,118,126,142,121,121,141,123,117,142,125,
	115,142,127,117,142,130,113,140,132,112,135,133,115,134,139,113,132,141,113,128,143,113,127,145,113,124,146,117,121,147,117,117,
	146,122,115,146,126,116,144,126,112,141,130,111,139,135,113,136,139,112,132,141,113,126,141,116,125,143,118,123,142,122,119,140,
	125,118,139,128,117,138,132,116,134,132,116,134,135,117,130,136,120,129,137,119,127,138,120,124,137,123,124,138,123,122,137,125,
	121,137,126,121,136,128,121,135,130,120,133,129,119,134,132,120,131,134,120,133,136,107,133,154, 88,139,172, 68,145,175, 60,148,
	178, 58,145,181, 60,138,187, 64,129,190, 70,123,192, 74,112,194, 83,104,196, 90, 94,197, 98, 87,196,107, 80,191,117, 75,188,129,
	 68,178,142, 82,143,112,146,169, 93,102,138,140,140,149,113, 91,106,132,160,159,151,112, 94, 99,100,150,176,157,142,101, 74, 93,
	143,168,171,159, 97, 73, 91,117,167,186,169,121, 77, 71, 94,148,184,185,152, 89, 67, 77,125,180,187,171,113, 66, 68, 99,164,190,
	187,143, 71, 59, 84,143,188,194,163, 91, 62, 72,115,173,194,178,121, 73, 58, 90,161,193,192,155, 75, 48, 77,131,185,207,173, 95,
	 62, 65, 98,174,205,177,133, 78, 52, 82,152,191,191,160, 86, 55, 78,121,175,204,174,110, 68, 63, 91,164,203,185,139, 75, 54, 74,
	145,193,194,174, 92, 49, 65,110,178,211,188,111, 57, 59, 85,159,209,195,151, 78, 45, 66,130,193,204,181,102, 48, 60, 98,167,212,
	199,134, 64, 48, 71,145,205,201,166, 90, 48, 66,107,177,209,190,132, 57, 48, 80,139,208,205,168, 92, 37, 61,109,185,214,183,123,
	 60, 50, 88,145,203,209,143,103, 61, 45,112,166,200,207,140, 76, 71, 65,105,177,181,170,162, 99, 70,103,107,130,173,149,134,139,
	111,110,134,115,107,133,137,139,153,146,125,104, 93,101,133,162,165,153,134, 98, 80, 93,125,155,179,176,123, 98, 95, 72,119,164,
	156,170,155,102, 90,109, 96,130,165,144,148,140,112,103,125,116,120,147,129,134,154,129,115,123,103,107,137,142,152,156,132,111,
	102, 97,111,142,160,165,148,119, 96, 85,100,132,158,175,167,128,102, 86, 81,113,149,165,183,159,101, 88, 88, 99,136,163,163,158,
	133, 98, 99,111,107,146,155,135,149,125,112,124,116,103,136,134,139,167,128,126,122, 88, 95,132,149,162,163,133,111, 98, 87,104,
	146,162,171,156,116, 95, 88, 99,130,156,161,160,135,105,105,104,114,141,141,138,147,130,118,126,110,113,137,129,133,153,136,129,
	126, 89,105,132,133,165,164,128,114, 92, 90,111,148,164,168,159,108, 93, 89,102,129,161,159,153,141, 94,100,110,116,145,144,139,
	153,127,105,123,108,118,146,131,136,149,124,122,133,102,107,137,129,148,164,128,117,112, 85,108,145,152,171,161,117,100, 90, 83,
	126,158,164,171,141,102, 99, 97,102,139,152,155,159,127, 99,109,112,125,144,133,143,149,119,110,121,111,121,140,137,153,151,117,
	111,104, 93,126,154,155,166,141,102,103, 99,104,136,143,158,174,132,109, 97, 79,118,150,159,170,130,100, 99, 90,124,164,165,172,
	137, 93, 87, 74,105,169,182,178,151, 88, 68, 79, 92,148,191,187,175,125, 72, 76, 93,113,153,168,171,165,112, 82, 92, 94,119,155,
	160,172,158,117,106, 84, 79,118,152,189,174,136, 96, 61, 77,119,180,210,183,129, 60, 38, 69,135,209,222,187,108, 39, 35, 79,168,
	218,213,161, 70, 39, 58,120,195,209,177,104, 51, 56,109,181,208,192,129, 55, 47, 82,154,207,205,162, 74, 30, 53,127,210,222,184,
	104, 39, 39, 82,174,227,217,150, 55, 29, 56,132,210,222,184, 96, 44, 48, 97,179,210,194,134, 55, 45, 83,158,210,206,150, 64, 42,
	 64,135,211,212,173, 96, 36, 47,105,188,221,201,133, 46, 35, 73,151,222,218,165, 78, 32, 44,106,194,219,198,129, 53, 41, 76,153,
	213,212,152, 67, 45, 69,130,199,208,174, 98, 43, 52,108,186,214,191,123, 53, 47, 85,157,209,201,150, 76, 44, 63,126,197,212,183,
	112, 50, 44, 86,161,212,206,152, 74, 45, 63,130,200,207,175, 98, 48, 56,105,179,207,187,122, 55, 52, 85,159,213,203,154, 74, 45,
	 66,126,197,210,182,105, 40, 45, 96,179,217,197,140, 64, 43, 66,135,206,212,172, 92, 47, 54,105,183,206,187,124, 62, 59, 89,156,
	202,193,144, 74, 54, 72,134,199,205,171, 92, 48, 60,110,187,210,186,119, 52, 48, 83,160,213,204,153, 73, 43, 62,125,199,214,182,
	107, 49, 47, 88,165,205,199,146, 77, 53, 65,130,195,205,169, 96, 59, 67,107,172,199,186,127, 63, 56, 86,154,205,197,153, 79, 49,
	 71,124,194,204,173,110, 51, 55, 95,165,210,198,146, 72, 44, 65,125,199,208,175,105, 51, 55, 98,172,207,193,134, 66, 54, 79,145,
	199,198,156, 84, 54, 66,122,188,202,178,112, 61, 63, 99,165,202,192,138, 66, 50, 78,147,202,198,161, 91, 49, 57,109,186,213,189,
	122, 56, 48, 79,153,208,201,154, 79, 51, 66,123,192,204,177,109, 55, 55, 94,167,207,196,142, 69, 51, 73,137,200,205,167, 94, 49,
	 60,110,183,208,183,121, 58, 51, 86,158,210,203,153, 81, 47, 61,119,186,205,180,117, 60, 50, 86,158,206,200,160, 71, 23,129,121,
	170,200,109,157, 60, 97,110,139,178,143,165, 78,130, 70,160,131,165,135,107,121, 78,160,108,192,112,158, 88,117,111,124,167,118,
	173, 82,152, 78,153,118,153,137,114,139, 85,157, 97,177,110,155, 99,116,116,113,158,115,169, 96,153, 90,143,115,144,146,121,137,
	 94,149,101,166,111,152,112,119,120,117,154,122,161,104,144, 96,139,113,142,134,124,138,103,144,103,158,116,151,117,123,119,111,
	145,116,162,112,146, 99,135,113,134,141,123,149,103,144, 99,150,116,147,126,118,126,105,148,119,163,120,146,107,125,114,123,141,
	129,154,108,132, 96,147,121,149,126,129,125,108,139,116,162,118,146,104,126,113,127,140,128,147,113,137,109,138,120,142,126,133,
	115,122,125,128,146,127,147,107,133, 99,136,125,145,140,123,130,105,136,114,149,121,145,114,131,119,133,136,133,141,107,134, 98,
	141,115,149,133,137,126,111,127,119,149,127,141,110,134,113,132,130,141,137,117,118,109,134,126,154,127,144,110,126,114,127,139,
	124,149,112,136,108,135,128,146,133,127,111,115,126,129,150,123,153,104,134,106,134,130,138,139,117,132,109,138,120,146,121,130,
	113,124,125,136,137,133,140,125,131,106,125,119,149,131,133,113,130,125,128,129,124,141,116,131,114,144,128,141,122,126,115,122,
	131,129,142,121,137,109,144,115,145,121,128,128,115,132,116,146,124,152,113,139,108,130,122,129,141,120,144,106,144,106,143,113,
	142,123,132,131,119,143,122,149,110,137,108,137,115,127,131,128,147,114,137,106,141,121,142,122,134,127,121,132,118,144,119,141,
	112,132,120,129,130,133,141,123,135,110,135,111,136,126,138,132,127,131,118,136,114,143,118,140,117,129,126,127,134,122,140,114,
	141,117,139,118,142,125,130,124,118,137,119,138,114,139,115,139,119,134,129,134,136,120,131,111,144,117,144,114,140,120,125,129,
	123,141,114,147,110,144,110,138,122,132,131,125,137,111,145,106,148,110,145,120,134,128,120,140,111,148,104,150,104,149,118,141,
	123,125,138,111,148,103,151,105,148,111,141,119,129,135,117,147,105,150,106,151,110,143,121,131,130,114,141,109,151,111,147,107,
	143,119,133,129,124,139,113,141,109,149,113,144,116,133,124,124,136,116,144,113,147,112,140,115,136,124,126,136,119,143,111,144,
	113,141,118,136,123,128,131,119,137,116,142,117,141,118,135,124,128,131,123,137,118,139,117,138,117,136,124,131,128,121,135,121,
	142,118,139,119,133,122,128,129,126,136,122,135,118,134,120,134,124,133,127,126,128,124,135,124,136,121,133,122,132,128,127,133,
	122,134,117,134,121,137,124,130,126,124,131,123,140,121,139,116,133,119,131,129,129,136,120,134,113,138,119,141,125,134,124,123,
	127,122,139,123,140,118,132,118,130,128,131,134,124,133,115,135,118,139,125,132,127,125,130,120,138,121,140,119,134,120,130,129,
	127,135,121,136,115,135,120,139,124,133,125,125,130,122,138,121,139,117,135,118,132,126,131,132,124,134,117,135,120,139,122,135,
	124,129,128,124,133,124,136,121,133,119,132,125,131,131,126,132,121,131,122,135,127,131,127,126,128,124,132,125,134,125,130,124,
	127,129,127,133,125,131,124,129,124,130,130,129,131,124,130,123,131,126,132,128,128,127,125,130,126,132,126,133,125,128,126,129,
	130,128,130,124,130,124,131,125,130,128,129,128,125,131,124,134,125,131,125,128,127,128,130,126,131,124,130,124,131,128,130,129,
	127,129,124,131,126,133,126,129,127,127,128,128,131,126,131,124,129,126,131,128,128,130,126,130,123,130,127,131,126,128,128,127,
	129,127,131,125,131,125,128,126,129,129,129,129,126,130,124,130,126,130,127,129,128,128,128,127,129,126,130,126,129,127,129,129,
	128,129,127,129,126,129,126,129,128,129,127,128,128,127,130,127,130,126,130,126,129,128,128,128,128,129,126,129,126,129,127,130,
	127,128,128,127,129,127,129,127,129,127,129,127,129,127,128,128,127,128,127,129,127,129,128,129,127,128,127,128,129,128,128,128,
	129,127,129,127,128,127,129,127,128,129,128,129,128,129,126,131,126,129,129,123,136,118,138,135, 85,186, 95,100,196, 80,112,195,
	 91, 95,198, 97, 86,199,101, 83,195,114, 73,191,125, 68,185,137, 64,174,151, 60,164,163, 64,149,175, 65,134,185, 70,124,190, 78,
	108,195, 89, 95,196,101, 85,191,116, 74,187,130, 69,181,140, 65,172,151, 62,165,160, 63,154,168, 67,142,174, 76,133,173, 83,121,
	178, 92,111,179,100,103,176,112, 93,175,123, 84,171,134, 80,164,148, 74,157,156, 73,147,167, 76,135,176, 78,124,181, 87,110,185,
	 96,100,185,102, 93,185,115, 84,179,127, 78,173,138, 76,166,148, 74,157,155, 76,146,164, 77,138,171, 79,130,176, 85,120,180, 89,
	113,180, 94,106,181,104, 99,180,109, 93,177,116, 87,175,125, 84,170,134, 82,160,147, 78,154,156, 78,144,166, 79,133,175, 80,121,
	180, 86,109,187, 94,101,189,102, 96,186,111, 84,181,122, 83,174,134, 76,165,147, 71,155,158, 78,141,166, 81,131,175, 84,121,177,
	 94,106,182,102, 94,182,116, 87,179,129, 77,172,137, 73,165,149, 73,159,157, 71,151,162, 74,142,169, 75,138,170, 81,128,174, 89,
	113,178, 94,107,178,105,102,180,112, 93,177,118, 88,170,127, 80,169,140, 81,160,144, 82,151,155, 80,143,166, 86,126,172, 92,114,
	176, 92,107,179,104, 98,180,112, 91,179,123, 87,167,133, 80,161,144, 83,153,154, 86,140,161, 86,131,166, 94,120,170, 97,112,174,
	 99,109,173,107,104,171,114,103,168,124, 95,159,130, 87,155,140, 87,148,150, 89,147,160, 84,134,165, 91,128,166, 91,123,172, 91,
	112,174,103,103,172,112, 98,175,122, 89,168,131, 85,161,142, 78,150,153, 83,145,164, 86,131,168, 90,117,174,100,105,175,112, 95,
	173,124, 87,169,134, 83,161,143, 82,154,151, 81,144,156, 84,130,164, 94,122,169,106,111,169,117,101,166,119, 86,165,141, 80,155,
	148, 80,153,153, 77,149,165, 78,136,171, 85,126,175, 85,112,181, 95,102,182,105, 91,188,120, 83,181,125, 74,174,137, 71,169,150,
	 72,158,158, 72,146,167, 74,135,174, 78,125,180, 86,114,182, 90,106,185, 98,101,188,108, 94,184,113, 85,177,123, 80,167,133, 81,
	168,147, 76,153,157, 80,144,163, 78,138,173, 78,125,178, 86,114,179, 94,107,183,103,100,181,111, 92,177,121, 83,168,131, 81,166,
	145, 80,157,154, 75,148,162, 75,140,169, 79,132,173, 83,124,177, 91,113,179,101,103,180,110, 93,175,119, 84,168,129, 82,162,146,
	 81,154,159, 83,147,162, 76,133,172, 84,125,173, 86,120,176, 91,111,180,101,105,174,109,104,171,113, 97,167,120, 95,161,129, 90,
	160,142, 90,155,148, 83,144,155, 82,140,166, 82,133,172, 86,125,174, 91,118,174, 96,110,174,103,103,173,113, 94,167,126, 87,166,
	141, 84,161,151, 78,151,158, 75,142,161, 75,138,174, 81,125,175, 89,120,175, 95,111,181,101, 99,177,114, 93,170,120, 89,166,132,
	 91,158,140, 93,152,147, 88,141,153, 88,131,165, 92,126,173, 92,118,174, 94,112,175, 98,106,176,104,104,174,107,104,171,111,105,
	168,119,105,162,124,101,152,126,100,146,133,103,143,137,112,148,137,105,137,135,116,137,127,116,141,128,113,136,131,121,134,127,
	121,139,132,121,134,128,120,134,130,117,128,129,122,135,137,122,131,136,115,128,136,114,129,141,115,129,143,115,128,145,115,124,
	145,115,123,146,117,119,145,117,115,145,120,114,148,130,115,149,133,110,144,134,101,132,137,111,139,138,103,135,149,105,128,150,
	112,127,147,111,124,153,113,116,148,116,114,149,120,111,151,129,116,149,128,107,141,130,106,141,137,110,139,141,109,135,142,110,
	131,141,111,128,144,113,127,143,116,123,144,118,121,145,123,122,146,126,115,139,124,114,138,126,112,139,136,118,139,131,113,139,
	138,111,132,140,115,130,137,114,130,141,113,125,141,117,126,145,121,122,144,122,118,140,121,115,141,127,117,143,130,114,140,132,
	112,138,133,111,136,138,113,133,140,113,130,140,114,125,143,118,124,144,119,120,143,121,115,141,125,117,143,129,115,143,134,112,
	137,132,111,138,135,110,135,139,112,131,139,115,131,140,113,128,143,119,125,141,120,122,140,121,119,138,126,120,140,128,119,138,
	129,117,136,131,117,135,132,118,133,134,118,130,134,119,128,134,122,128,135,123,126,134,124,124,134,126,124,135,128,125,134,127,
	122,134,128,121,132,128,123,133,129,122,133,131,122,130,130,123,131,131,122,131,133,123,129,131,121,128,133,123,128,134,124,127,
	133,124,126,134,124,126,133,126,125,133,127,125,133,127,123,131,127,124,133,130,124,132,130,123,130,130,123,130,132,123,129,132,
	124,129,132,123,128,134,124,126,134,126,125,135,126,123,133,127,122,133,129,122,133,129,122,132,131,121,130,131,122,130,133,123,
	129,134,124,126,134,124,126,133,125,124,133,127,123,132,129,123,131,129,123,131,131,124,130,132,123,128,132,124,127,132,125,127,
	133,126,125,133,127,124,132,127,125,132,128,123,131,130,124,130,129,123,130,130,124,129,132,125,128,131,125,128,131,125,127,132,
	127,127,131,126,126,131,126,126,131,128,126,131,128,126,131,128,125,130,129,125,130,129,126,129,130,125,129,129,124,128,131,125,
	127,131,126,127,131,126,126,131,127,126,130,128,126,131,128,125,130,129,125,130,129,125,130,131,125,129,131,125,128,130,125,127,
	130,126,126,131,126,126,130,127,126,130,128,126,130,130,126,129,130,125,128,130,125,128,130,126,128,131,127,127,131,127,126,130,
	128,126,131,128,126,131,129,125,129,129,125,130,130,125,129,130,126,128,129,126,128,130,126,127,130,128,128,130,127,127,130,127,
	126,129,128,127,129,129,126,129,129,127,129,130,126,128,130,126,128,130,126,127,130,126,127,130,127,127,131,127,126,131,128,126,
	130,127,125,130,128,126,130,128,126,130,129,126,128,130,126,129,130,125,128,131,126,127,130,127,127,131,127,126,131,128,126,130,
	127,125,130,128,125,130,129,125,130,130,126,129,130,126,128,130,125,128,130,126,127,130,126,127,131,127,127,131,127,127,131,127,
	126,130,127,126,130,128,126,130,128,126,130,129,126,129,129,126,128,130,126,128,130,126,128,130,126,127,130,127,127,130,127,127,
	130,127,127,130,127,126,130,128,126,129,129,126,130,129,126,129,129,126,128,129,126,128,131,126,127,130,127,128,129,127,127,130,
	127,127,130,128,126,129,128,126,129,129,127,129,129,127,129,129,126,128,129,127,128,130,127,128,130,128,128,129,127,127,130,128,
	127,129,128,127,129,128,127,129,128,127,129,129,127,128,129,127,128,129,127,128,129,127,128,129,127,128,129,127,127,129,127,128,
	129,127,127,129,129,127,128,128,127,129,129,127,128,128,127,128,129,127,128,129,127,128,129,127,128,129,127,128,129,128,128,129,
	127,128,129,128,127,129,128,128,128,128,127,129,128,127,128,128,128,128,129,127,128,129,127,128,128,128,128,129,128,128,128,128,
	128,129,128,128,129,128,128,128,128,127,128,129,127,127,129,128,127,128,129,127,128,129,127,128,129,128,127,129,128,127,128,129,
	127,127,129,128,127,128,129,127,128,129,127,127,130,128,127,129,128,127,129,129,127,128,129,127,128,129,127,127,129,128,127,129,
	128,127,128,129,128,128,129,128,127,129,128,127,128,128,127,128,128,128,128,128,128,128,127,129,128,127,129,128,127,128,129,126,
	128,129,127,128,129,127,128,130,128,126,129,129,126,128,130,127,127,130,129,125,129,130,125,128,132,125,126,133,126,124,135,127,
	118,139,133,108,144,142, 89,153,153, 73,153,160, 71,151,165, 70,145,173, 73,128,182, 95, 98,173,135, 81,146,164, 89,114,174,116,
	 89,162,147, 85,134,168,100,104,170,127, 85,154,155, 83,128,176, 97, 98,180,126, 76,162,157, 74,131,180, 92, 98,182,124, 77,163,
	157, 77,129,176,102, 95,171,137, 79,148,165, 85,118,178,104, 94,173,132, 84,151,157, 88,122,170,110, 97,163,138, 87,142,162, 94,
	113,171,118, 91,160,149, 84,131,172,100,101,174,130, 80,155,161, 80,124,179,101, 95,175,134, 77,153,165, 82,116,181,108, 89,173,
	139, 77,147,167, 85,113,180,110, 88,173,138, 79,146,165, 88,114,176,113, 89,164,149, 77,139,173, 89,107,178,118, 86,164,145, 82,
	141,167, 90,111,177,114, 87,168,144, 77,141,171, 89,109,180,118, 81,165,152, 74,136,178, 87,106,185,114, 81,170,148, 76,136,173,
	 91,106,183,120, 78,165,153, 74,136,175, 90,107,177,125, 82,158,158, 77,130,176, 96, 97,181,126, 79,164,154, 79,128,177, 98, 96,
	179,129, 76,160,163, 76,126,181, 95, 96,181,126, 76,160,161, 77,128,181, 97, 95,179,125, 77,163,156, 78,136,174, 93,104,176,122,
	 81,161,153, 78,135,177, 96,102,176,120, 82,162,154, 79,132,178, 93,103,181,115, 84,165,149, 77,137,175, 90,109,180,119, 79,170,
	145, 71,150,170, 83,113,181,113, 86,169,144, 75,142,174, 90,103,179,123, 81,163,155, 77,132,174, 91,103,179,123, 84,164,151, 79,
	133,172, 92,103,177,122, 84,163,153, 81,138,168, 87,110,179,113, 90,170,140, 81,147,161, 90,113,174,114, 88,171,138, 80,151,164,
	 82,123,175, 99,100,169,135, 82,154,159, 79,132,177, 91,100,180,124, 81,163,153, 76,135,177, 93,102,177,121, 81,163,155, 79,135,
	176, 94, 99,176,123, 79,161,155, 79,134,175, 93,106,179,118, 79,163,149, 79,144,170, 89,111,176,116, 84,166,147, 77,145,168, 90,
	113,176,115, 88,168,139, 80,140,172, 88,112,183,109, 87,170,143, 77,145,166, 85,120,181,102, 90,176,135, 76,154,164, 78,120,182,
	103, 94,178,133, 76,154,159, 78,125,178,102, 97,178,131, 78,157,159, 78,125,176, 91,104,185,123, 78,165,153, 73,138,172, 90,112,
	175,121, 88,160,149, 80,140,165, 91,111,175,114, 95,167,137, 90,137,162, 95,112,174,114, 90,167,144, 80,143,163, 88,120,173,110,
	 94,165,138, 85,149,161, 87,119,171,104, 99,167,133, 89,151,158, 88,123,170,104, 98,170,127, 83,156,159, 88,128,167,100,103,166,
	130, 88,150,161, 85,124,175, 98,102,172,126, 85,154,154, 86,132,167,106, 99,167,130, 85,154,152, 90,128,165,106,106,165,126, 90,
	153,152, 90,128,164,102,108,169,126, 89,153,148, 85,130,170,101,106,172,128, 88,151,151, 88,127,166,105,106,164,131, 95,153,148,
	 85,125,170,105,100,170,133, 86,151,157, 88,117,173,110, 90,172,137, 81,150,165, 85,118,175,104, 98,162,141, 88,140,164, 92,116,
	172,112, 91,164,143, 84,142,164, 91,112,175,119, 87,161,146, 80,135,173, 95,108,178,121, 85,159,147, 80,134,170, 97,107,175,124,
	 87,161,153, 80,124,173,103,101,173,132, 83,152,159, 79,126,178, 96,101,175,130, 81,152,166, 80,121,177,105, 88,177,138, 72,160,
	164, 76,120,182,107, 86,173,144, 74,147,171, 84,108,179,118, 86,164,148, 78,136,170, 98,109,171,122, 89,156,146, 85,131,167,106,
	105,166,132, 90,147,157, 91,116,167,112, 99,168,138, 85,144,159, 93,113,168,121, 93,155,152, 86,132,167,102,104,166,127, 86,157,
	151, 91,127,169,104, 99,171,128, 85,154,156, 84,126,174,106, 93,167,140, 83,144,164, 90,115,171,117, 97,162,138, 89,138,156, 97,
	116,164,119,104,156,138, 97,136,152,105,117,152,120,109,153,140,104,128,146,113,117,150,122,113,148,128,116,134,134,121,120,142,
	121,119,137,136,117,132,141,109,135,133,119,127,136,130,116,133,138,119,123,136,124,123,138,129,118,131,133,123,130,136,124,121,
	132,128,120,132,133,126,130,136,125,122,132,127,123,127,132,123,127,136,131,126,129,123,121,133,130,125,132,130,129,129,123,133,
	121,127,135,121,131,129,130,126,135,126,124,129,124,134,119,134,133,121,132,129,124,130,131,122,126,133,129,124,130,130,122,129,
	135,125,123,132,126,123,133,132,124,129,136,123,122,132,127,121,130,135,122,126,137,129,122,133,131,116,125,138,128,121,137,131,
	117,131,134,118,129,133,126,124,132,133,120,132,134,123,121,135,126,120,137,129,123,130,133,124,122,135,130,121,129,135,124,125,
	134,127,121,132,134,121,127,135,123,123,136,130,121,132,133,122,124,135,125,121,135,132,119,130,138,123,123,135,127,119,131,134,
	124,126,134,127,122,131,132,122,128,136,124,124,133,130,123,128,134,124,124,131,130,123,130,133,123,127,132,127,124,130,132,124,
	127,131,128,124,131,130,125,127,132,127,124,131,130,123,129,133,125,125,132,129,123,129,132,125,126,133,127,124,132,131,123,127,
	131,126,125,132,129,124,130,131,124,127,132,126,125,132,129,122,131,131,124,127,133,125,124,133,129,123,130,132,123,126,135,126,
	124,131,131,123,127,133,125,125,133,129,122,130,132,124,126,133,127,123,131,131,123,129,133,125,126,133,127,124,131,131,124,128,
	133,125,126,132,128,123,130,131,124,128,133,126,125,131,129,124,129,130,125,127,132,127,125,131,129,125,129,131,125,127,132,127,
	125,131,130,125,128,131,126,126,131,128,125,130,131,125,127,131,127,126,131,128,125,129,131,126,127,132,128,125,130,129,125,128,
	132,126,126,132,129,124,129,131,125,127,131,127,125,132,129,124,129,131,125,127,132,126,125,131,130,124,129,131,125,127,131,127,
	125,131,130,125,129,131,126,126,130,128,125,130,130,125,128,131,126,126,131,128,125,129,130,125,127,131,127,126,131,129,125,128,
	131,125,126,131,128,125,130,130,125,128,131,126,126,131,128,125,130,130,126,127,131,126,126,130,129,125,129,130,126,127,131,127,
	126,130,129,125,129,131,126,127,131,128,126,130,129,126,128,130,127,126,130,128,126,129,129,127,128,130,127,127,130,128,127,129,
	129,127,128,129,127,127,129,128,127,129,129,127,128,129,127,127,129,128,127,129,129,127,128,129,127,127,129,128,127,128,129,127,
	128,129,127,127,129,128,127,128,129,128,128,129,128,128,128,128,127,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,127,128,128,128,128,128,128,128,128,128,127,128,
	128,128,128,128,128,128,128,128,128,128,129,128,128,128,128,128,128,128,128,128,128,128,128,129,128,128,128,128,127,128,129,127,
	128,128,128,127,129,
};
