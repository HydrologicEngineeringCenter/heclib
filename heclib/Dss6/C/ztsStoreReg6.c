#include <string.h>

#include "heclib7.h"
#include "zdssMessages.h"
#include "hecdssInternal.h"

#include "zStructTimeSeries.h"

/*
	Internal.  Do not use, call ztsStore
	
*/



int ztsStoreReg6(long long *ifltab, zStructTimeSeries *tss, int storageFlag)
{
	int status;
	void *values;
	int valueSize;
	char startDate[20];
	char startTime[9];
	double coordinates[3];
	int coordinateDescription[6];
	int boolCoordinatesUsed;


	//  Messages and debug
	if (zmessageLevel(ifltab, MESS_METHOD_TS_WRITE_ID, MESS_LEVEL_INTERNAL_DIAG_1)) {
		zmessageDebugInt(ifltab, DSS_FUNCTION_ztsStoreReg_ID, "Enter;  Handle: ",  zhandle(ifltab));
		zmessageDebug(ifltab, DSS_FUNCTION_ztsStoreReg_ID, " Pathname: ", tss->pathname);	
	}


	getDateTimeString(tss->startJulianDate, startDate, sizeof(startDate), 104, tss->startTimeSeconds, startTime, sizeof(startTime), 0);

	if (tss->floatValues) {
		values = tss->floatValues;
		valueSize = 1;
	}
	else if (tss->doubleValues) {
		values = tss->doubleValues;
		valueSize = 2;
	}
	else {
		//  errror out
		return -1;
	}

	if (tss->locationStruct) {
		boolCoordinatesUsed = 1;
		coordinates[0] = tss->locationStruct->xOrdinate;
		coordinates[1] = tss->locationStruct->yOrdinate;
		coordinates[2] = tss->locationStruct->zOrdinate;
		coordinateDescription[0] = tss->locationStruct->coordinateSystem;
		coordinateDescription[1] = tss->locationStruct->coordinateID;
		coordinateDescription[2] = tss->locationStruct->horizontalUnits; 
		coordinateDescription[3] = tss->locationStruct->horizontalDatum;
		coordinateDescription[4] = tss->locationStruct->verticalUnits;
		coordinateDescription[5] = tss->locationStruct->verticalDatum;
	}
	else {
		boolCoordinatesUsed = 0;
	}

	status = ztsStoreRegArgs(ifltab, tss->pathname,
							startDate, startTime, tss->numberValues,
							(int *)values, valueSize,
							tss->quality, tss->qualityElementSize,
							tss->inotes, tss->inoteElementSize,
							tss->cnotes, tss->cnotesLengthTotal,
							tss->userHeader, tss->userHeaderNumber,
							tss->units, tss->type, 
							tss->precision,	tss->timeZoneName, 
							coordinates, coordinateDescription, boolCoordinatesUsed,
							storageFlag);

	if (zmessageLevel(ifltab, MESS_METHOD_TS_WRITE_ID, MESS_LEVEL_INTERNAL_DIAG_1)) {
		zmessageDebug(ifltab, DSS_FUNCTION_ztsStoreReg_ID, "Exit. Pathname: ", tss->pathname);	
	}

	return status;
}

