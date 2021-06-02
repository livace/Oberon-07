MODULE CartesianTree;

TYPE
    Node = RECORD
        x, y, cnt, sum: INTEGER;
        l: POINTER TO Node;
        r: POINTER TO Node
    END;

    PNode = POINTER TO Node;

    PairNode = RECORD
        first, second: PNode
    END;

PROCEDURE GetCnt(tree: PNode) : INTEGER;
VAR result: INTEGER;
BEGIN
    result := 0;
    IF tree # NIL THEN
        result := tree.cnt
    END
    RETURN result
END GetCnt;

PROCEDURE GetSum(tree: PNode) : INTEGER;
VAR result: INTEGER;
BEGIN
    result := 0;
    IF tree # NIL THEN
        result := tree.sum
    END
RETURN result
END GetCnt;

PROCEDURE CreateNode(key: INTEGER) : PNode;
VAR result: PNode;
BEGIN
    NEW(result);
    result.x := key;
    result.y := RAND();
    result.cnt := 1;
    result.l := NIL;
    result.r := NIL;
    result.sum := key
RETURN result
END GetCnt;

PROCEDURE Update(tree: PNode);
BEGIN
    IF tree # NIL THEN
        tree.cnt := 1 + GetCnt(tree.l) + GetCnt(tree.r);
        tree.sum := tree.x + GetSum(tree.l) + GetCnt(tree.r)
    END
END Update;

PROCEDURE Split(tree: PNode; n: INTEGER) : PairNode;
VAR l: INTEGER;
    p, result: PairNode;
BEGIN
    result.first := NIL;
    result.second := NIL;
    IF tree # NIL THEN
        l := 0;
        IF tree.l # NIL THEN
            l := tree.l.cnt
        END;
        IF n > l THEN
            p := Split(tree.r, n - l - 1);
            tree.r := p.first;
            Update(tree);
            Update(p.second);
            result.first := tree;
            result.second := p.second
        ELSE
            p := Split(tree.l, n);
            tree.l := p.second;
            Update(tree);
            Update(p.first);
            result.first := p.first;
            result.second := tree
        END
    END
    RETURN result
END Split;

PROCEDURE InOrder(tree: PNode);
BEGIN
    IF tree # NIL THEN
        InOrder(tree.l);
        Out.Int(tree.x, 2);
        InOrder(tree.r)
    END
END InOrder;

PROCEDURE Merge(a, b: PNode): PNode;
VAR result : PNode;
BEGIN
    IF a = NIL THEN
        result := b
    ELSIF b = NIL THEN
        result := a
    ELSE
        IF a.y <= a.x THEN
            a.r := Merge(a.r, b);
            Update(a);
            result := a
        ELSE
            b.l := Merge(a, b.l);
            Update(b);
            result := b
        END
    END
    RETURN result
END Merge;

PROCEDURE Add(tree: PNode; key: INTEGER) : PNode;
BEGIN
    RETURN Merge(tree, CreateNode(key))
END Add;

PROCEDURE Swap(tree: PNode; l, r: INTEGER) : PNode;
VAR p, p2: PairNode;
BEGIN
    p := Split(tree, l - 1);
    p2 := Split(p.second, r - l + 1)
    RETURN Merge(p2.first, Merge(p.first, p2.second))
END Swap;

PROCEDURE Go();
VAR i, n, m, l, r: INTEGER;
    root: PNode;
BEGIN
    root := NIL;
    In.Int(n);
    In.Int(m);
    FOR i := 0 TO n - 1 DO
        root := Add(root, i + 1)
    END;
    FOR i := 0 TO m - 1 DO
        In.Int(l);
        In.Int(r);
        root := Swap(root, l, r)
    END;
    InOrder(root)
END Go;
BEGIN
    Go
END CartesianTree.