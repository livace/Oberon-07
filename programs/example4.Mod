MODULE Example4;
VAR n, a, b, c, res: INTEGER;
BEGIN
    In.Int(n);

    res := 0;
    FOR i := 0 TO n - 1 DO
        In.Int(a);
        In.Int(b);
        In.Int(c);

        IF a + b + c > 1 THEN 
            res := res + 1
        END
    END;

    Out.Int(res, 0)

END Example4.
