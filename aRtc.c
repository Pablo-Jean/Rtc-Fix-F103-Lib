/*
 * aRtc.c
 *
 *  Created on: Oct 17, 2023
 *      Author: pablo-jean
 */


#include "aRtc.h"

#ifndef			ARTC_INCREASE_40_YEARS
#define			ARTC_INCREASE_40_YEARS		1
#endif

void aRtc_set(RTC_HandleTypeDef *hrtc, struct tm Time){
	time_t utc;

#if (ARTC_INCREASE_40_YEARS == 1)
	Time.tm_year -= 40;
#endif
	utc = mktime(&Time);

	__HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);
	hrtc->Instance->CNTL = (utc & 0xFFFF);
	hrtc->Instance->CNTH = (utc >> 16);
	__HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
}

void aRtc_get(RTC_HandleTypeDef *hrtc, struct tm *Time){
	time_t utc;
	struct tm *local;

	utc =  (hrtc->Instance->CNTH << 16);
	utc |= hrtc->Instance->CNTL;
	// TODO: The time_t is a uint64_t

	local = localtime(&utc);

#if (ARTC_INCREASE_40_YEARS == 1)
	local->tm_year += 40;
#endif

	*Time = *local;
}

