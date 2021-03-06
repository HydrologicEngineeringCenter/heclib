      SUBROUTINE ZSPDI (IFLTAB, CPATH, NORD, NCURVE, IHORIZ,
     * C1UNIT, C1TYPE, C2UNIT, C2TYPE, SVALUES, DVALUES,
     * LDOUBLE, CLABEL, LABEL, IUHEAD, NUHEAD, IPLAN, ISTAT)
C
      implicit none
C
C     Internal Store Paired DATA
C
      INTEGER IFLTAB(*), IUHEAD(*),zdssVersion
      CHARACTER CPATH*(*), CLABEL(*)*(*)
      CHARACTER C1UNIT*(*), C1TYPE*(*), C2UNIT*(*), C2TYPE*(*)
      REAL SVALUES(*)
      DOUBLE PRECISION DVALUES(*)
      LOGICAL LABEL, LDOUBLE
      INTEGER NORD, NCURVE, IHORIZ, IPLAN, NUHEAD, ISTAT
C
C
      IF (zdssVersion(IFLTAB).EQ.6) THEN
          CALL ZSPDI6 (IFLTAB, CPATH, NORD, NCURVE, IHORIZ,
     *    C1UNIT, C1TYPE, C2UNIT, C2TYPE, SVALUES, DVALUES,
     *    LDOUBLE, CLABEL, LABEL, IUHEAD, NUHEAD, IPLAN, ISTAT)
      ELSE
        if (LDOUBLE) then
          CALL ZSPDI7 (IFLTAB, CPATH, NORD, NCURVE, IHORIZ,
     *    C1UNIT, C1TYPE, C2UNIT, C2TYPE, SVALUES, DVALUES,
     *    LDOUBLE, CLABEL, LABEL, IUHEAD, NUHEAD, IPLAN, ISTAT)
        else
          CALL ZSPDI7 (IFLTAB, CPATH, NORD, NCURVE, IHORIZ,
     *    C1UNIT, C1TYPE, C2UNIT, C2TYPE, SVALUES, DVALUES,
     *    LDOUBLE, CLABEL, LABEL, IUHEAD, NUHEAD, IPLAN, ISTAT)
        endif
      ENDIF
C
      RETURN
      END

