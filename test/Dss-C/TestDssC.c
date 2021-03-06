#include <stdio.h>
#include <string.h>

#include "heclib.h"
#include "hecdss7.h"
#include "TestDssC.h"

/*
	To Run:
		Copy sample.dss from HEC-DSSVue/samples to sample6.dss
*/

int writeDoubleArray() {
	long long ifltab[250];

	zStructArray* struct1;
	int nvalues = 1;
	char path1[MAX_PATHNAME_LENGTH];
	double doublevalues[1];
	doublevalues[0] = 0.1;
	char* path = "//wat-test/Total/Simulation//wat-issue/";
	//stringCopy(path1, sizeof(path1), "//wat-test/Total/Simulation//wat-issue/", 50);

	struct1 = zstructArrayNew(path);
	struct1->doubleArray = doublevalues;
	struct1->numberDoubleArray = nvalues;

	deleteFile("C:/temp/testarray.dss");
	int status = zopen(ifltab, "C:/temp/testarray.dss");

	status = zarrayStore(ifltab, struct1);
	if (status != STATUS_OKAY) {
		printf("Write on testArrayWriteRead doubles Failed!\n");
		return status;
	}

}


int multipleWriteDeleteSlowDown() {

	long long ifltab[250], mills1, mills2, diff;
	zStructPairedData* pds1;
	float fordinates[500], fvalues[500];
	int status, i;

	deleteFile("C:/temp/testpd.dss");
	status = zopen(ifltab, "C:/temp/testpd.dss");
	//zsetfi_(ifltab,"reclaim", " ", RECLAIM_NONE,&i,&status,7,1);

	//zsetfi_(ifltab, "FMULT", "ON", &number, &status,
		//5, 2);

	if (status != STATUS_OKAY) return status;

	for (i = 0; i < 500; i++) {
		fordinates[i] = (float)i;
		fvalues[i] = (float)i;
	}

	pds1 = zstructPdNewFloats("/test/paired-data-container/x-y///slowdown-test/", fordinates, fvalues, 500, 1,
		"Feet", "Unt", "cfs", "Unt");

	for (i = 0; i < 10001; i++) {
		mills1 = getCurrentTimeMillis();
		status = zpdStore(ifltab, pds1, 0);
		if (status != STATUS_OKAY) {
			printf("Failed on write, loop %d\n", i);
			return status;
		}
		status = zdelete(ifltab, pds1->pathname);
		mills2 = getCurrentTimeMillis();
		diff = mills2 - mills1;
		printf("Loop %d, time = %lld\n", i, diff);
		if (status != STATUS_OKAY) {
			printf("Failed on delete, loop %d\n", i);
			return status;
		}
	}

	zstructFree(pds1);
	zclose(ifltab);

}




int SolarisTesting()
{
	long long ifltab[250];
	zStructTimeSeries* tss1, * tss2;
	float fvalues[200];

	for (int i = 0; i < 200; i++) {
		fvalues[i] = (float)(i+1);
	}

	int status = zopen(ifltab, "charlong_7.dss");
	if (status) return status;


	//status = zopen6(ifltab6, fileName6);
	//if (status != STATUS_OKAY) return status;

	tss1 = zstructTsNewRegFloats("/Basin/Location/Flow//30Min/TSS-Floats/", fvalues, 200, "21Jan2001", "1200", "cfs", "Inst-Val");
	status = ztsStore(ifltab, tss1, 0);
	if (zcheckStatus(ifltab, status, 1, "Fail in testztsStruct1 Loc 1, store status ")) return status;


	tss2 = zstructTsNew("/Basin/Location/Flow/01Jan2001/30Min/TSS-Floats/");
	status = ztsRetrieve(ifltab, tss2, -1, 1, 0);
	if (zcheckStatus(ifltab, status, 1, "Fail in testztsStruct1 Loc 2, retrieve status ")) return status;

	status = zcompareDataSets(ifltab, tss1, tss2, 1, 0, tss1->pathname, "Fail in testztsStruct1, Location 3");
	if (status) return status;
	

}

int UnitPaddingIssue()
{
	long long ifltab[250];
	char* path = "//Dry Creek/Flow/01Feb2014/1Hour/N0H0B0";
	zStructTimeSeries* tss1 = zstructTsNew(path);
	int status = zopen(ifltab, "k7-small.dss");
	if (status) return status;

	status = ztsRetrieve(ifltab, tss1, -1, 1, 0);
	printf("\nunits= '%s'", tss1->units);
	printf("\ntype= '%s'", tss1->type);
	printf("\ntimeZoneName= '%s'", tss1->timeZoneName);
	printf("\n");

	long long ifltab2[250];
	deleteFile("k7-small-updated.dss");
	status = zopen(ifltab2, "k7-small-updated.dss");
	tss1->pathname= "//Dry Creek/Flow/01Feb2014/1Hour/karl";
	ztsStore(ifltab2, tss1, 0);
	zstructFree(tss1);
	zStructTimeSeries* tss2 = zstructTsNew(path);
	

	zcopyFile(ifltab, ifltab2, 0);
	status = ztsRetrieve(ifltab2, tss2, -1, 1, 0);
	printf("\nunits= '%s'", tss2->units);
	printf("\ntype= '%s'", tss2->type);
	printf("\ntimeZoneName= '%s'", tss2->timeZoneName);
	printf("\n");
	zstructFree(tss2);

}

int decodeError(int errorCode)
{
	int highFunction;
	int lowFunction;
	int dssError;
	int status;
	int severity = zerrorDecode(errorCode, &highFunction, &lowFunction, &dssError, &status);
	char message[300];
	int size = 299;
	zerrorMessage(message, size, severity, dssError, lowFunction);
	printf("\n%s\n", message);
	zerrorMessage(message, size, severity, dssError, highFunction);
	printf("\n%s\n", message);

}



int main(int argc, int* argv[])
{
	long long ifltab7[250];
	long long ifltab6[250];
	char fileName7[80];
	char fileName7a[80];
	char fileName6[80];
//	int catalogHandle;
	int status;
//	int jul;
	//int jul2;
	int i;

	//multipleWriteDeleteSlowDown();
	//SolarisTesting();
	//UnitPaddingIssue();
	//decodeError(-200384707);
	//writeDoubleArray();
	//return 0;

	printf("\ntest Bulletin_17C_Examples.dss for reading full record\n");
	status = Bulletin_17C_SSP_Issue();
	if (status != STATUS_OKAY)
	  return status;



	printf("\ntestDateFunctions\n");
	status = testDateFunctions();
	if (status != STATUS_OKAY) return status;

	remove("testmultiuser7.dss");
	status = testMultiUser("testmultiuser7.dss", 7, 333, 2);
	if (status != STATUS_OKAY) return status; 

	remove("testmultiuser6.dss");
	status = testMultiUser("testmultiuser6.dss", 6, 444, 2);
	if (status != STATUS_OKAY) return status;




	//findInFile();
	//mainx(argc, argv);
	//return 0;

	//catStruct = zstructCatalogNew();
	//testMultiUser();
	//return 0;

	//catStruct = zstructCatalogNew(); 
	
	//status = zopen(ifltab7, "C:\\Users\\q0hecwjc\\Desktop\\funny.dss");
	//status = zopen(ifltab7, "C:\\Users\\q0hecwjc\\Desktop\\db7.dss");
	//status = zcatalog((long long*)ifltab7, catStruct->pathWithWildChars, catStruct, 0);
	
	//testCatalog();
	//testConversion();
	//zset("MLVL", "", 15);
	//stringCopy(fileName7, sizeof(fileName7), "C:/Users/q0hecwjc/Desktop/snow.2016.01.dss", sizeof(fileName7));	
	//stringCopy(fileName7, sizeof(fileName7), "C:/Users/q0hecwjc/Desktop/airtemp.2016.04.dss", sizeof(fileName7));	
	//stringCopy(fileName7, sizeof(fileName7), "C:/Users/q0hecwjc/Documents/test.dss", sizeof(fileName7));
	//status = zopen(ifltab7, fileName7);
	//if (status) return status;
	//status =spatialDateTime ("01DEC2016:2400", &jul, &jul2);
	//status = testAdHoc2();
//	filesToUnix();
//	return;
	//testConversion();
	//status = testAdHoc2();
	//bc1();
	//ExampleOpenx();
	//return;
	//if (status != STATUS_OKAY) return status;

	status = testMisc();
	if (status != STATUS_OKAY) return status;

	status = testDateTime();
	if (status != STATUS_OKAY) return status;

	status = testDelete("testUtilities7.dss", "testUtilities6.dss");
	if (status != STATUS_OKAY) return status;

	stringCopy(fileName7, sizeof(fileName7), "testDss7.dss", sizeof(fileName7));	
	remove(fileName7);

	status = zopen(ifltab7, fileName7);
	if (status) return status;

	//status = testztsStruct1(ifltab7);
	//zclose(ifltab7);
	//printf("Done\n");
	//if (status != STATUS_OKAY) return status;
	//return status;

	printf("\n\n\n\n###################################################################\n\n");
	printf("     Test 1 - Normal\n");
	printf("\n###################################################################\n\n");
	
	status = runTests(ifltab7);
	if (status != STATUS_OKAY) return status;
	zclose(ifltab7);

	
	status = testCatalog();
	if (status != STATUS_OKAY) return status;


	status = testConversion();
	if (status != STATUS_OKAY) return status;

	//printf("\n\n\n#####################  Completion\n\n\n");
	//if (status == STATUS_OKAY) return status;

	//  Test reclamation
	stringCopy(fileName7a, sizeof(fileName7a), "testReclaim7.dss", sizeof(fileName7));
	remove(fileName7a);
	status = testReclaim(fileName7a);
	if (status != STATUS_OKAY) return status;

	stringCopy(fileName6, sizeof(fileName6), "testDss6.dss", sizeof(fileName6));
	remove(fileName6);
	status = zopen6(ifltab6, fileName6);
	if (status != STATUS_OKAY) return status;
	status = zopen(ifltab7, fileName7);
	if (status) return status;
	status = testIO_Interface(ifltab7, ifltab6);
	if (status != STATUS_OKAY) return status;

	printf("\n\n\n\n###################################################################\n\n");
	printf("     Test 2 - DSS-6\n");
	printf("\n###################################################################\n\n");
	status = runTests(ifltab6);
	if (status != STATUS_OKAY) return status;
	printf("\n\n\n#####################  Completion\n\n\n");

	status = zcatalogFile(ifltab7, "dss7.txt", 0, (const char *)0);
	if (status <1) {
		printf("\n\nCatalog FAILED, status = %d\n", status);
		return status;
	}

	zclose(ifltab7);

	status = testSqueeze(fileName7);
	if (status != STATUS_OKAY) return status;

	printf("\n\nNormal tests passed....\n");
//return 0;

	printf("\n\nNow detune (should run really slow!)\n\n\n");

	//  Try the tests with the file detuned
	remove(fileName7);
	status = zopen(ifltab7, fileName7);
	if (status != STATUS_OKAY) return status;
	zsetFile(ifltab7, "detune", "", 1);

	printf("\n\n\n\n###################################################################\n\n");
	printf("     Test 3 - Detuned file\n");
	printf("\n###################################################################\n\n");
	
	status = runTests(ifltab7);
	if (status != STATUS_OKAY) return status;
	printf("\n\n\n#####################  Completion\n\n\n");

	//  Try the tests with the space reclamation off
	printf("\n\nDetuned tests passed....\nNow turn off space reclamation\n\n\n");
	remove(fileName7);
	status = zopen(ifltab7, fileName7);
	if (status != STATUS_OKAY) return status;
	zsetFile(ifltab7, "reclaim", "", 0);

	printf("\n\n\n\n###################################################################\n\n");
	printf("     Test 4 - No space reclamation\n");
	printf("\n###################################################################\n\n");
	
	status = runTests(ifltab7);
	if (status != STATUS_OKAY) return status;
	zclose(ifltab7);
	printf("\n\n\n#####################  Completion\n\n\n");

	//  Try the tests with the file detuned and space reclamation off
	printf("\n\nTests passed....\nNow detune and turn off space reclamation\n\n\n");
	remove(fileName7);
	status = zopen(ifltab7, fileName7);
	if (status != STATUS_OKAY) return status;
	zsetFile(ifltab7, "detune", "", 1);
	zsetFile(ifltab7, "reclaim", "", 0);

	printf("\n\n\n\n###################################################################\n\n");
	printf("     Test 5 - Detuned file and No space reclamation\n");
	printf("\n###################################################################\n\n");
	
	status = runTests(ifltab7);
	if (status != STATUS_OKAY) return status;
	zclose(ifltab7);
	printf("\n\n\n#####################  Completion\n\n\n");
//	zsetMessageLevel(zmessaging_global_id, MESS_INTERNAL_DIAG_1);



	printf("\n\nAll tests passed!\n\nGoodbye DSS-7\n");
	return 0;
}

