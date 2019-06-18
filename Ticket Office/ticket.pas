
Program ticket;
Const
	MaxN=100000;
	MaxM=30000;
Var
	N,m:longint;
	L:longint;
	Start,R:Array[0..MaxN] of longint;
	S:Array[0..MaxM] of longint;
	Sch:Array[0..MaxM] of longint;
	i,ii,k,x:longint;
	Lend,fn,gap,free:longint;
	Sol:longint;
	OutF:Text;

procedure ReadIn;
var
	InFile:Text;
	i,x:longint;
begin
	readln(m, L);
	readln(N);

	for i:=1 to N do begin
		read(InFile, x);
		Start[i]:=x;
		R[i]:=i;
	end {for i};

	Start[0]:=0;
	Start[n+1]:=m+1;
end {ReadIn};

procedure Sort;
var
	Nox:array[0..MaxM] of longint;
	i,ii,j,x:longint;
begin
	Nox[0]:=0;

	for x:=1 to m do Nox[x]:=0;
	for i:=1 to n do inc(Nox[Start[i]]);
	for x:=1 to m do Nox[x]:=Nox[x]+Nox[x-1];

	for i:=1 to n do begin
		ii:=Start[i];
		j:=Nox[ii];
		R[j]:=i;
		dec(Nox[ii]);
	end;

	R[0]:=0;
	R[n+1]:=n+1;
end {Sort};

Begin {Prog}
	ReadIn;
	Sort;
	fn:=0;
	Lend:=m+1;
	{1. step: allocate full-price orders}

	for i:=N downto 1 do begin
		ii:=R[i];
		if Start[ii]+L<=Lend then begin
			inc(fn);
			S[fn]:=ii;
			Lend:=Start[ii];
		end;
	end {for i};

	for i:=1 to fn div 2 do begin
		x:=S[i]; S[i]:=S[fn-i+1];
		S[fn-i+1]:=x;
	end;

	{2. step: modify the schedule to minimize the wastage }
	S[fn+1]:=n+1;
	free:=1;
	k:=1;
	gap:=m;
	Sol:=0;
	Lend:=Start[S[1]];

	for i:=1 to n do begin
		if Start[R[i]]>Lend then begin
			Sol:=Sol+(Start[S[k]]-free) div L+1;
			free:=Start[S[k]]+L;
			inc(k);
			Lend:=Start[S[k]];
			gap:=m;
		end;
		if (free<=Start[R[i]])and((Start[R[i]]-free) mod L<gap) then begin
			gap:=(Start[R[i]]-free) mod L;
			S[k]:=R[i];
		end;
	end {for i};

	Sol:=Sol+(Start[S[fn]]-free) div L;
	Sol:=Sol+(m-(Start[S[fn]])+1) div L;

	if Sol>n then Sol:=n;

	writeln(Sol+fn);
	writeln(Sol);
	{3. step: fill in the gaps with half-price orders}

	for i:=1 to m do Sch[i]:=0;
	for i:=1 to fn do
		for k:=Start[S[i]] to Start[S[i]]+L-1 do
			Sch[k]:=S[i];

	free:=1; i:=1;
	while i<=n do begin
		if free+L-1>m then break;
		if Sch[Start[R[i]]]=R[i] then begin
			inc(i); continue;
		end;

		k:=Sch[free+L-1];
			if (Sch[free]=0)and(k=0) then begin
			Sch[free]:=R[i];
			free:=free+L;
			inc(i);
			end else
			free:=Start[k]+L;
	end {while i};

	k:=1;

	while k<=m do begin
		if Sch[k]>0 then begin
			writeln(OutF, Sch[k],' ',k);
			k:=k+L;
		end else begin
			inc(k);
		end;
	end;

	close(OutF);
End.
