      SUBROUTINE zsrtsi (IFLTAB, CPATH, CDATE, CTIME, NVALS,
     * LDOUBLE, SVALUES, DVALUES, JQUAL, LQUAL, CUNITS, CTYPE,
     * IUHEAD, NUHEAD, COORDS, NCOORDS, ICDESC, NCDESC,
     * IPLAN, JCOMP, BASEV, LBASEV, LDHIGH, NPREC, ISTAT)
C
      implicit none
C
C
C     Z-Store Regular interval Time-Series data Interface routine
C
C
C     Argument Dimensions
      CHARACTER CPATH*(*), CTYPE*(*), CUNITS*(*), CDATE*(*), CTIME*(*)
      INTEGER IFLTAB(*), IUHEAD(*), JQUAL(*),zdssVersion
      INTEGER IPLAN, ISTAT, NVALS
      LOGICAL LQUAL
      LOGICAL LDOUBLE
      logical LBASEV,LDHIGH
      
      REAL SVALUES(*)
      DOUBLE PRECISION DVALUES(*), COORDS(*)
C
      INTEGER NCDESC, NCOORDS, ICDESC(*)
      integer NUHEAD,JCOMP,BASEV,NPREC
      

C
      IF (zdssVersion(IFLTAB).EQ.6) THEN
         CALL zsrtsi6(IFLTAB, CPATH, CDATE, CTIME, NVALS,
     *    LDOUBLE, SVALUES, DVALUES, JQUAL, LQUAL, CUNITS, CTYPE,
     *    IUHEAD, NUHEAD, COORDS, NCOORDS, ICDESC, NCDESC,
     *    IPLAN, JCOMP, BASEV, LBASEV, LDHIGH, NPREC, ISTAT)
      ELSE
          CALL zsrtsi7(IFLTAB, CPATH, CDATE, CTIME, NVALS,
     *    LDOUBLE, SVALUES, DVALUES, JQUAL, LQUAL, CUNITS, CTYPE,
     *    IUHEAD, NUHEAD, COORDS, NCOORDS, ICDESC, NCDESC,
     *    IPLAN, JCOMP, BASEV, LBASEV, LDHIGH, NPREC, ISTAT)
      ENDIF
C
      RETURN
      END

