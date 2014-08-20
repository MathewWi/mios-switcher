#include <ogc/conf.h>
#include "getWiiSystemSramLanguage.h"
enum SRAM_GC_LANGUAGES getWiiSystemSramLanguage() {
    switch (CONF_GetLanguage()) {
		case CONF_LANG_GERMAN:
			return SRAM_GC_GERMAN_LANGUAGE;
		case CONF_LANG_FRENCH:
			return SRAM_GC_FRENCH_LANGUAGE;
		case CONF_LANG_SPANISH:
			return SRAM_GC_SPANISH_LANGUAGE;
		case CONF_LANG_ITALIAN:
			return SRAM_GC_ITALIAN_LANGUAGE;
		case CONF_LANG_DUTCH:
			return SRAM_GC_DUTCH_LANGUAGE;
		default:
			return SRAM_GC_ENGLISH_LANGUAGE;
	}
}
