MODULE Example5;

VAR 
    res: INTEGER;
    n: INTEGER;
    m: ARRAY 100000 OF INTEGER;

PROCEDURE Gcd(a, b: INTEGER) : INTEGER;
VAR 
    res: INTEGER;
BEGIN
    IF b = 0 THEN
        res := a
    ELSE
        res := Gcd(b, a MOD b)
    END

    RETURN res
END Gcd;

BEGIN
    In.Int(n);

    res := 0;
    FOR i := 1 TO n - 1 DO
        IF Gcd(i, n) = 1 THEN
            m[res] := i; 
            res := res + 1
        END
    END;

    Out.Int(res, 0); Out.Ln;

    FOR i := 0 TO res - 1 DO
        Out.Int(m[i], 0); Out.Ln
    END
END Example5.
