program grader;

uses robots;

procedure fail(s: string);
begin
    writeln(stderr, s);
    halt(1);
end;

var
    A, B, T, i: longint;
    X, Y: array[0..99999] of Longint;
    W, S: array[0..999999] of Longint;
    f: text;
    answer: longint;

begin
    assign(f, 'robots.in');
    {$I-} reset(f); {$I+}
    if IOResult <> 0 then
        fail('Failed to open input file.');

    readln(f, A, B, T);

    for i := 0 to A-1 do
        read(f, X[i]);
    for i := 0 to B-1 do
        read(f, Y[i]);
    for i := 0 to T-1 do
        read(f, W[i], S[i]);
    close(f);

    answer := putaway(A, B, T, X, Y, W, S);

    writeln(answer);
end.
