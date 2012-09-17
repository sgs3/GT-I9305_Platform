/*
i * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ThaiReshaperWebkit.h"
#include <cutils/log.h>

///////////////////////////////////////////////////////////////////////////////
//[SISO][Saurabh] thai Reshaper - 15-07-11 starts
/**
 * Function to check if uniCode is thai unicode or not
 *//*** checked***/
bool isThai(unsigned short uniCode) {
	if ((uniCode >= KO_KAI) && (uniCode <= KHO_MUT)) {
#ifdef THAIRESHAPERLOGS
		LOGE("ThaiReshaper::isThai, true");
#endif
		return true;
	}
#ifdef THAIRESHAPERLOGS
	LOGE("ThaiReshaper::isThai, false");
#endif
	return false;
}

/*

 * Function to reshape thai character
 **/
///////////////////////////////////////////////////////////////////////////////
//[SISO][Saurabh] thai Reshaper - 15-07-11 starts
/**
 *  Function returns a positive integer or 0 if the c requires certain
 *  tones applied to it to be reshaped. whether tone is required to be reshaped is
 *  determined by using isThaiReshaperTone.
 **//**check***/
int isThaiReshaperCharhw(int32_t c) {

#ifdef THAIRESHAPERLOGS
	LOGE("ThaiReshaper::isThaiReshaperChar, unicode is %x", c);
#endif
	if ((c == YO_YING) || (c == THO_THAN)) {
		return THAIRESHAPEREMOVETAIL;
	} else if ((c == TO_PATAK) || (c == DO_CHADA)) {
		return THAIRESHAPEPULLDOWN;
	} else if ((c == PO_PLA) || (c == FO_FA) || (c == FO_FAN) ||(c == LO_CHULLA)) {
		return THAIRESHAPESHIFTLEFT;
	} else {
		return NOTTHAIRESHAPE;
	}



}

/**
 *  Function to check if reshaping is required on the tone.
 *  it returns integer value corresponding to the integer returned by
 *  isThaiReshaperChar, to check if current tone corresponds to the tones required
 *  to be reshaped for consonant in contention.
 **/
int isThaiReshaperTonehw(int32_t uniCode, int32_t consonantType) {
	if (uniCode == SARA_U || uniCode == SARA_UU || uniCode == PHINTHU) {
		if (consonantType == THAIRESHAPEREMOVETAIL)
			return THAIRESHAPEREMOVETAIL;
		else
			return THAIRESHAPEPULLDOWN;
	} else if (((uniCode >= MAI_EK ) && (uniCode <= NIKHAHIT)) || ((uniCode
			>= SARA_AM) && (uniCode <= SARA_Uee)) || (uniCode == MAI_HAN_AKAT)
			|| (uniCode == MAI_TAI_KHU)) {
		return THAIRESHAPESHIFTLEFT;
	} else {
		return NOTTHAIRESHAPE;
	}

}
